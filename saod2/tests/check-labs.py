import os
from pathlib import Path
import subprocess
import tempfile
import xml.etree.ElementTree as ET

root = Path(__file__).resolve().parents[1]
env = dict(os.environ, SAOD_NO_BROWSER="1")
programs = ["3.5-avl", "3.6-avl-delete", "3.7-dbd", "3.8-dop", "3.9-a1-a2"]

def run(name, *args, env_override=None):
    return subprocess.run([str(root / "build" / name), *args],
                          cwd=tempfile.gettempdir(), input="0\n", text=True,
                          capture_output=True, timeout=30, env=env_override or env)

for name in programs:
    result = run(name)
    assert result.returncode == 0, (name, result.stderr)
    assert "Страница дерева:" in result.stdout, (name, result.stdout)
for path in root.glob("3.*.svg"):
    ET.parse(path)

def nodes(name):
    svg = ET.parse(root / name).getroot()
    return len(svg.findall(".//{http://www.w3.org/2000/svg}rect")) - 1

assert run("3.8-dop", "7").returncode == 0
assert nodes("3.8-example.svg") == 7
assert run("3.8-dop", "100").returncode == 0
assert nodes("3.8-example.svg") == 100
assert nodes("3.8-dop.svg") == 100
for name in ["3.9-dop.svg", "3.9-a1.svg", "3.9-a2.svg"]:
    assert nodes(name) == 100
assert run("3.8-dop", "wrong").returncode != 0

# A failed SVG write must be visible and must not open an old preview.
blocked = root / "3.8-example.svg"
blocked.unlink()
blocked.mkdir()
result = run("3.8-dop", "7")
assert result.returncode != 0
assert "Не удалось сохранить" in result.stderr
assert "Страница дерева:" not in result.stdout
blocked.rmdir()
assert run("3.8-dop").returncode == 0

# Check both successful and failed desktop opener statuses.
with tempfile.TemporaryDirectory() as directory:
    opener = Path(directory) / "xdg-open"
    marker = Path(directory) / "opened"
    opener.write_text('#!/bin/sh\nprintf "%s" "$1" > "$OPEN_MARKER"\nexit 0\n')
    opener.chmod(0o755)
    desktop = dict(os.environ, PATH=directory + os.pathsep + os.environ["PATH"],
                   OPEN_MARKER=str(marker))
    desktop.pop("SAOD_NO_BROWSER", None)
    for name in programs:
        result = run(name, env_override=desktop)
        assert result.returncode == 0, (name, result.stderr)
        target = Path(marker.read_text())
        assert target.is_absolute() and target.is_file(), target
    opener.write_text("#!/bin/sh\nexit 3\n")
    result = run("3.7-dbd", env_override=desktop)
    assert "Не удалось открыть браузер" in result.stderr

# Exercise local-file previews, zoom controls, and deletion step navigation.
from playwright.sync_api import sync_playwright
with sync_playwright() as p:
    browser = p.chromium.launch()
    for name in programs:
        folder = root / "labs" / name
        page = browser.new_page(viewport={"width": 1280, "height": 800})
        errors = []
        page.on("pageerror", lambda error: errors.append(str(error)))
        page.goto((folder / (name[:3] + "-view.html")).as_uri())
        page.wait_for_function("""() => [...document.querySelectorAll('.viewport img')]
            .every(img => img.complete && img.naturalWidth > 0)""")
        assert not errors, (name, errors)
        label = page.locator(".tree-view").first.locator(".status")
        old = label.inner_text()
        page.get_by_role("button", name="+", exact=True).first.click()
        assert label.inner_text() != old
        page.get_by_role("button", name="100%", exact=True).first.click()
        assert label.inner_text() == "100%"
        page.get_by_role("button", name="Вписать", exact=True).first.click()
        if name == "3.6-avl-delete":
            steps = root / "3.6-avl-delete-steps.js"
            (root / "3.6-avl-delete-1.svg").write_bytes((root / "3.6-avl-delete-0.svg").read_bytes())
            steps.write_text("window.treeSession='test'; window.deletedKeys=[123];")
            page.wait_for_function("() => document.getElementById('caption').textContent.includes('123')")
            page.get_by_role("button", name="← Назад").click()
            assert "Исходное" in page.locator("#caption").inner_text()
            steps.write_text("window.treeSession='next'; window.deletedKeys=[];")
            page.wait_for_function("() => document.getElementById('caption').textContent.includes('0 из 0')")
        page.close()
    browser.close()
print("All five labs: build, SVG, paths, browser controls and algorithms passed.")
