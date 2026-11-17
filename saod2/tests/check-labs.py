import os
import re
from pathlib import Path
import subprocess
import tempfile
import xml.etree.ElementTree as ET

root = Path(__file__).resolve().parents[1]
env = dict(os.environ, SAOD_NO_BROWSER="1")
early = ["3.1-trees","3.1-trees-100","3.2-isdp","3.2-isdp-iterative","3.3-sdp","3.3-sdp-iterative","3.3-sdp-repeat","3.3-sdp-repeat-iterative","3.4-sdp-delete"]
programs = early + ["3.5-avl", "3.6-avl-delete", "3.7-dbd", "3.8-dop", "3.9-a1-a2"]

make_targets = {"3.1-trees":["labs/3.1-trees","run"],"3.1-trees-100":["labs/3.1-trees","run-100"],"3.2-isdp":["labs/3.2-isdp","run"],"3.2-isdp-iterative":["labs/3.2-isdp","run-iterative"],"3.3-sdp":["labs/3.3-sdp","run"],"3.3-sdp-iterative":["labs/3.3-sdp","run-iterative"],"3.3-sdp-repeat":["labs/3.3-sdp","run-repeat"],"3.3-sdp-repeat-iterative":["labs/3.3-sdp","run-repeat-iterative"],"3.4-sdp-delete":["labs/3.4-sdp-delete","run"],"3.5-avl":["labs/3.5-avl","run"],"3.6-avl-delete":["labs/3.6-avl-delete","run"],"3.7-dbd":["labs/3.7-dbd","run"],"3.8-dop":["labs/3.8-dop","run"],"3.9-a1-a2":["labs/3.9-a1-a2","run"]}

def run(name, *args, env_override=None, input_text=None, via_make=False):
    if via_make:
        folder, target = make_targets[name]
        command = ["make", "-C", str(root / folder), target]
    else:
        command = [str(root / "build" / name), *args]
    return subprocess.run(command,
                          cwd=tempfile.gettempdir(),
                          input=input_text if input_text is not None else (("10\n10\n" + "\n".join(map(str, range(1, 1001))) + "\n")
                          if name == "3.4-sdp-delete" else "0\n"), text=True,
                          capture_output=True, timeout=30, env=env_override or env)

for name in programs:
    result = run(name, via_make=True)
    assert result.returncode == 0, (name, result.stderr)
    assert "Страница дерева:" in result.stdout, (name, result.stdout)
fixed = run("3.1-trees")
assert "Размер дерева: 7" in fixed.stdout and "Контрольная сумма: 52" in fixed.stdout
assert "Высота дерева: 4" in fixed.stdout and "Средняя высота: 2.57" in fixed.stdout
for file in ["3.1-trees.svg", "3.1-trees-100.svg", "3.2-isdp.svg",
             "3.3-isdp.svg", "3.3-sdp-recursive.svg", "3.3-sdp-double.svg", "3.4-sdp-delete-0.svg"]:
    assert (root / file).is_file(), file
# All saved deletion steps must show one fewer node, down to the empty tree.
for step in range(11):
    svg = ET.parse(root / ("3.4-sdp-delete-%d.svg" % step)).getroot()
    assert len(svg.findall(".//{http://www.w3.org/2000/svg}circle")) == 10 - step

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

# Check every recursive/iterative search variant on all possible generated keys.
for name in early:
    if not name.startswith(("3.2-", "3.3-")):
        continue
    result = run(name, input_text="1002\n" + "\n".join(map(str, range(1002))) + "\n")
    assert result.returncode == 0
    hits = re.findall(r"(?:Ключ|Элемент) (\d+) найден", result.stdout)
    file = "3.2-isdp.svg" if name.startswith("3.2-") else "3.3-sdp-recursive.svg"
    tree = ET.parse(root / file).getroot()
    keys = {node.text for node in tree.findall(".//{http://www.w3.org/2000/svg}title")}
    assert set(hits) == keys, (name, len(hits), len(keys))

for name, filename in [("3.1-trees", "3.1-trees.svg"), ("3.2-isdp", "3.2-isdp.svg"),
                       ("3.3-sdp", "3.3-isdp.svg"), ("3.4-sdp-delete", "3.4-sdp-delete-0.svg")]:
    blocked = root / filename
    blocked.unlink()
    blocked.mkdir()
    result = run(name)
    assert result.returncode != 0, name
    assert filename in result.stderr, (name, result.stderr)
    assert "Страница дерева:" not in result.stdout, name
    blocked.rmdir()
    assert run(name).returncode == 0

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
    # Browser output and late child messages must go to a regular log file.
    log = root / "build" / "browser.log"
    log.unlink(missing_ok=True)
    opener.write_text('#!/bin/sh\n'
                      'if IFS= read -r value; then echo "INPUT_STOLEN:$value" >&2; exit 9; fi\n'
                      'echo "Browser opens in existing session"\n'
                      'echo "Failed sending zygote boot message" >&2\n'
                      '(sleep 0.2; echo "late browser message" >&2) &\n'
                      'exit 0\n')
    result = run("3.2-isdp", env_override=desktop, input_text="1\n0\n")
    assert result.returncode == 0, result.stderr
    assert "Ключ 0 не найден" in result.stdout
    assert "Browser opens" not in result.stdout
    assert "zygote" not in result.stderr
    assert "INPUT_STOLEN" not in log.read_text()
    assert "Browser opens in existing session" in log.read_text()
    assert "Failed sending zygote boot message" in log.read_text()
    opener.write_text("#!/bin/sh\necho 'browser rejected request' >&2\nexit 3\n")
    result = run("3.7-dbd", env_override=desktop)
    assert "Не удалось открыть браузер" in result.stderr
    assert str(log) in result.stderr
    assert "browser rejected request" in log.read_text()
    assert "browser rejected request" not in result.stderr

    # Failed exec remains visible, including the diagnostic file.
    opener.unlink()
    no_opener = dict(desktop, PATH=directory)
    result = run("3.7-dbd", env_override=no_opener)
    assert "Не удалось открыть браузер" in result.stderr
    assert "Открытие браузера" in log.read_text()

# Exercise local-file previews, zoom controls, and deletion step navigation.
from playwright.sync_api import sync_playwright
with sync_playwright() as p:
    browser = p.chromium.launch()
    for name in programs:
        folder_name = ("3.1-trees" if name.startswith("3.1-") else
                       "3.2-isdp" if name.startswith("3.2-") else
                       "3.3-sdp" if name.startswith("3.3-") else name)
        folder = root / "labs" / folder_name
        page = browser.new_page(viewport={"width": 1280, "height": 800})
        errors = []
        page.on("pageerror", lambda error: errors.append(str(error)))
        view = "3.1-view-100.html" if name == "3.1-trees-100" else name[:3] + "-view.html"
        page.goto((folder / view).as_uri())
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
        if name in ("3.4-sdp-delete", "3.6-avl-delete"):
            steps = root / (name + "-steps.js")
            (root / (name + "-1.svg")).write_bytes((root / (name + "-0.svg")).read_bytes())
            steps.write_text("window.treeSession='test'; window.deletedKeys=[123];")
            page.wait_for_function("() => document.getElementById('caption').textContent.includes('123')")
            page.get_by_role("button", name="← Назад").click()
            assert "Исходное" in page.locator("#caption").inner_text()
            steps.write_text("window.treeSession='next'; window.deletedKeys=[];")
            page.wait_for_function("() => document.getElementById('caption').textContent.includes('0 из 0')")
        page.close()
    browser.close()
assert "Дерево пусто" in (root / "3.4-sdp-delete-10.svg").read_text()
assert "late browser message" in (root / "build" / "browser.log").read_text()
print("Labs 3.1-3.9 and all early variants: build, SVG, paths and browser controls passed.")
