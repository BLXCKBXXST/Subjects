import collections
import os
from pathlib import Path
import re
import struct
import subprocess
import tempfile
import xml.etree.ElementTree as ET

root = Path(__file__).resolve().parents[1]
folder = root / "coursework" / "src"
svg = folder / "a2.svg"
state = folder / "a2-state.js"
base = root / "coursework" / "testBase1.dat"
env = dict(os.environ, SAOD_NO_BROWSER="1")
raw = base.read_bytes()
record = struct.Struct("<12s32s16shh")
rows = [record.unpack_from(raw, pos) for pos in range(0, len(raw), record.size)]
assert len(rows) == 4000

def text_field(value):
    return value.split(b"\0", 1)[0].decode("cp866").rstrip(" ")

years = collections.Counter(row[3] for row in rows)
year = years.most_common(1)[0][0]
other_year = next(value for value, _ in reversed(years.most_common()) if value != year)
weights = collections.Counter(text_field(row[1]) for row in rows if row[3] == year)
title = weights.most_common(1)[0][0]
query = "2\nq\n3\n%d\n" % year

def run(input_text, desktop=None, make=False):
    command = (["make", "-C", str(root / "coursework"), "run"] if make
               else [str(root / "build" / "coursework")])
    return subprocess.run(command, cwd=tempfile.gettempdir(), input=input_text,
                          capture_output=True, text=True, encoding="utf-8",
                          errors="strict", timeout=30, env=desktop or env)

def table_rows(output, columns=6):
    result = []
    for line in output.splitlines():
        cells = [value.strip() for value in line.split("│")[1:-1]]
        if len(cells) == columns and cells[0].isdigit():
            result.append(cells)
    return result

def svg_weights():
    tree = ET.parse(svg).getroot()
    result = {}
    for group in tree.findall(".//{http://www.w3.org/2000/svg}g"):
        heading = group.find("{http://www.w3.org/2000/svg}title")
        if heading is not None:
            weight = next(node.text for node in group.findall("{http://www.w3.org/2000/svg}text")
                          if node.get("class") == "weight")
            result[heading.text or ""] = int(weight.split(":")[1])
    return result

initial = run("0\n")
assert initial.returncode == 0, initial.stderr
assert "Загружено записей: 4000" in initial.stdout
assert "Страница дерева:" not in initial.stdout
assert not svg_weights()
assert "Сначала выполните сортировку." in run("3\n0\n").stdout

sorted_result = run("2\n\nQ\n0\n")
assert sorted_result.returncode == 0
sorted_pages = table_rows(sorted_result.stdout)
assert len(sorted_pages) == 40
assert [int(r[0]) for r in sorted_pages] == list(range(1, 41))
expected = sorted(rows, key=lambda row: (row[3], row[0]))
for printed, actual in zip(sorted_pages, expected[:40]):
    assert (int(printed[4]), printed[1]) == (actual[3], text_field(actual[0]))

pages = run("1\n\nq\n0\n")
assert len(table_rows(pages.stdout)) == 40
all_rows = table_rows(run("4\n0\n").stdout)
assert len(all_rows) == 4000 and all_rows[-1][0] == "4000"

result = run(query + "Такого заглавия точно нет\n" + title + "\n\n0\n", make=True)
assert result.returncode == 0, result.stderr
assert "Записей с таким заглавием нет." in result.stdout
found = list(map(int, re.findall(r"Найдено записей: (\d+)", result.stdout)))
assert found == [years[year], weights[title]], found
traversal_output = result.stdout.split("Обход дерева А2 слева направо:\n", 1)[1]
traversal = table_rows(traversal_output.split("Введите заглавие книги", 1)[0], columns=7)
assert len(traversal) == years[year]
assert [int(row[0]) for row in traversal] == list(range(1, years[year] + 1))
assert [row[2] for row in traversal] == sorted(
    key for key, weight in weights.items() for _ in range(weight))
assert all(int(row[6]) == weights[row[2]] for row in traversal)
actual_records = collections.Counter(tuple(row[1:6]) for row in traversal)
expected_records = collections.Counter(
    (text_field(row[0]), text_field(row[1]), text_field(row[2]), str(row[3]), str(row[4]))
    for row in rows if row[3] == year)
assert actual_records == expected_records
assert svg_weights() == weights

invalid = run("abc\n99999999999999999999999\n2\nq\n3\nwrong\n-1\n0\n")
assert invalid.returncode == 0 and "Введите целое число." in invalid.stdout
assert "Записей с таким годом нет." in invalid.stdout
assert not svg_weights()
long_line = run(query + ("x" * 200) + "\n" + title + "\n\n0\n")
assert long_line.returncode == 0
assert "Слишком длинная строка." in long_line.stdout
assert re.findall(r"Найдено записей: (\d+)", long_line.stdout)[-1] == str(weights[title])

# Missing, truncated, and oversized bases must be reported.
saved = base.with_suffix(".test-backup")
base.rename(saved)
try:
    missing = run("0\n")
    assert missing.returncode != 0 and "testBase1.dat" in missing.stderr
    for data in (raw[:63], raw + b"x"):
        base.write_bytes(data)
        broken = run("0\n")
        assert broken.returncode != 0 and "полных записей" in broken.stderr
        base.unlink()
finally:
    if base.exists():
        base.unlink()
    saved.rename(base)

# A save failure must not open an old tree.
svg.unlink()
svg.mkdir()
blocked = run("0\n")
assert blocked.returncode != 0 and "a2.svg" in blocked.stderr
assert "Страница дерева:" not in blocked.stdout
svg.rmdir()
svg.symlink_to("/dev/full")
try:
    full = run("0\n")
    assert full.returncode != 0 and "a2.svg" in full.stderr
finally:
    svg.unlink()

# Successful preview opens only after the tree exists; paths are absolute.
with tempfile.TemporaryDirectory() as directory:
    opener = Path(directory) / "xdg-open"
    marker = Path(directory) / "opened"
    opener.write_text('#!/bin/sh\nprintf "%s\\n" "$1" >> "$OPEN_MARKER"\nexit 0\n')
    opener.chmod(0o755)
    desktop = dict(os.environ, PATH=directory + os.pathsep + os.environ["PATH"],
                   OPEN_MARKER=str(marker))
    desktop.pop("SAOD_NO_BROWSER", None)
    assert run("0\n", desktop=desktop).returncode == 0
    assert not marker.exists()
    result = run(query + "\n3\n-1\n0\n", desktop=desktop)
    assert result.returncode == 0, result.stderr
    assert marker.read_text().splitlines() == [str(folder / "a2.html")]
    assert not svg_weights()
    opener.write_text("#!/bin/sh\nexit 3\n")
    result = run(query + "\n0\n", desktop=desktop)
    assert result.returncode == 0 and "Не удалось открыть браузер" in result.stderr

from playwright.sync_api import sync_playwright
with sync_playwright() as p:
    browser = p.chromium.launch()
    page = browser.new_page(viewport={"width": 1280, "height": 800})
    errors = []
    page.on("pageerror", lambda error: errors.append(str(error)))
    page.goto((folder / "a2.html").as_uri())
    page.wait_for_function("() => document.getElementById('tree').naturalWidth > 0")
    label = page.locator(".tree-view .status")
    page.get_by_role("button", name="100%", exact=True).click()
    page.get_by_role("button", name="+", exact=True).click()
    assert label.inner_text() == "125%"
    old_source = page.locator("#tree").get_attribute("src")
    page.wait_for_timeout(1300)
    assert label.inner_text() == "125%"
    assert page.locator("#tree").get_attribute("src") == old_source
    assert run("2\nq\n3\n%d\n\n0\n" % other_year).returncode == 0
    page.wait_for_function("(old) => document.getElementById('tree').getAttribute('src') !== old", arg=old_source)
    assert label.inner_text() == "125%"
    old_source = page.locator("#tree").get_attribute("src")
    assert run("2\nq\n3\n-1\n0\n").returncode == 0
    page.wait_for_function("(old) => document.getElementById('tree').getAttribute('src') !== old", arg=old_source)
    page.wait_for_function("() => document.getElementById('tree').naturalWidth === 400")
    assert not errors, errors
    page.close()

    # Check actual SVG geometry, text wrapping, XML characters, and level separators.
    for path in [root / "build" / "coursework-long.svg"]:
        drawing = browser.new_page()
        drawing.goto(path.as_uri())
        assert drawing.locator("rect.node").count() == 5
        assert drawing.locator("g[stroke-opacity='0.30']").count() == 1
        assert drawing.evaluate("""() => [...document.querySelectorAll('rect.node')].every(rect => {
            const box = rect.getBBox();
            return [...rect.parentNode.querySelectorAll('text')].every(text => {
                const t = text.getBBox();
                return t.x >= box.x && t.y >= box.y &&
                       t.x + t.width <= box.x + box.width &&
                       t.y + t.height <= box.y + box.height;
            });
        })"""), "Text outside node"
        assert drawing.evaluate("""() => {
            const boxes = [...document.querySelectorAll('rect.node')].map(node => node.getBBox());
            return boxes.every((a, i) => boxes.slice(i + 1).every(b =>
                a.x + a.width <= b.x || b.x + b.width <= a.x ||
                a.y + a.height <= b.y || b.y + b.height <= a.y));
        }"""), "Overlapping nodes"
        drawing.close()
    browser.close()
print("Coursework: real base, all menu modes, input, file errors, browser, duplicates and geometry passed.")
