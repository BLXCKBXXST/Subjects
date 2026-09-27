#!/usr/bin/env python3
"""Make an archival copy of reports 10-14 from the preserved sources.

The original LaTeX, source code and historical screenshot instructions are
never overwritten. Images under archive/evidence/ are NEW reconstructions
(rendered from saved HTML or actual reruns of saved JavaScript).
"""
from pathlib import Path
import re
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
WEB = ROOT / "web-technologies"
BUILD = ROOT / ".web-archive-build"

BROWSER = []
for name, width, height in [("desktop", 1440, 920), ("tablet", 768, 950),
                            ("mobile", 390, 900)]:
    BROWSER.append((10, "figma-mockup/" + name + ".html", "html-" + name + ".png", width, height))
for name in ["home", "team", "player", "tournament", "shop"]:
    BROWSER.append((11, "figma-mockup/desktop/" + name + ".html",
                    "html-" + name + ".png", 1440, 920))
for name, width in [("tablet", 768), ("mobile", 390)]:
    BROWSER.append((11, "figma-mockup/" + name + "/home.html",
                    "html-" + name + "-home.png", width, 940))
for code, folder in [("1-1", "1.1-html-tags"), ("1-2", "1.2-lists-tables"),
                     ("2-1", "2.1-selectors"), ("2-2", "2.2-text-styling")]:
    BROWSER.append((12, "codepen-solutions/" + folder + "/index.html",
                    "local-" + code + ".png", 1280, 1000))
for name, width, height in [("desktop", 1280, 940), ("mobile", 390, 940)]:
    BROWSER.append((14, "resume/index.html", "html-" + name + ".png", width, height))

NODE = [("les1-1", "les-1/task1.js"), ("les1-2", "les-1/task2.js"),
        ("les2-1", "les-2/task1.js"), ("les2-2", "les-2/task2.js")]

CAPTIONS = {
    10: {"html-desktop.png": "HTML-макет магазина, десктоп, фрагмент",
         "html-tablet.png": "HTML-макет магазина, планшет, фрагмент",
         "html-mobile.png": "HTML-макет магазина, телефон, фрагмент"},
    11: {**{"html-" + name + ".png": "HTML-макет PHYGITAL FC: " + title + ", фрагмент"
             for name, title in [("home", "главная"), ("team", "команда"),
                                  ("player", "участник"), ("tournament", "таблица"),
                                  ("shop", "магазин")]},
         "html-tablet-home.png": "HTML-макет главной страницы: планшет, фрагмент",
         "html-mobile-home.png": "HTML-макет главной страницы: телефон, фрагмент"},
    12: {"local-" + code + ".png": "Повторный рендер сохранённого HTML/CSS, задание " + code
         for code in ["1-1", "1-2", "2-1", "2-2"]},
    13: {"node-" + code + ".png": "Повторный запуск сохранённого JS: " + desc
         for code, desc in [("les1-1", "урок 1, задача 1"), ("les1-2", "урок 1, задача 2"),
                            ("les2-1", "урок 2, задача 1"), ("les2-2", "урок 2, задача 2")]},
    14: {"html-desktop.png": "Повторный рендер сохранённого резюме: десктоп, фрагмент",
         "html-mobile.png": "Повторный рендер сохранённого резюме: телефон, фрагмент"}
}
NOTES = {
    10: "Сохранились HTML-макеты магазина для трёх разрешений; файл Figma, ссылка на него и исторические скриншоты не сохранились.",
    11: "Сохранились HTML-макеты пяти страниц для трёх разрешений; файл Figma, ссылка на него и исторические скриншоты не сохранились.",
    12: "Сохранились локальные HTML/CSS-решения и адреса Codepen из исходного отчёта. Исторические скриншоты редактора не сохранились; доступность прежних форков не проверена.",
    13: "Сохранились JavaScript-файлы и код сайта Marvel. Показанные в приложении консольные результаты получены повторным запуском. Состояние старого API и прежнего сервера не проверено.",
    14: "Сохранились HTML/CSS/JS-файлы резюме. Повторные рендеры не доказывают публикацию на прежнем домене или прежнее состояние Docker-стенда."
}
FIGURE = re.compile(r"\\begin\{figure\}(?:\[[^]]*\])?[\s\S]*?\\end\{figure\}")
IMAGE = re.compile(r"\\(?:ReportImage|includegraphics)(?:\[[^]]*\])?\{(img/[^}]+)\}")


def out_path(lab, name):
    path = WEB / ("lab" + str(lab)) / "archive" / "evidence" / name
    path.parent.mkdir(parents=True, exist_ok=True)
    return path


def capture():
    from playwright.sync_api import sync_playwright
    from PIL import Image, ImageDraw, ImageFont, ImageStat
    with sync_playwright() as p:
        browser = p.chromium.launch(headless=True)
        for lab, src, name, width, height in BROWSER:
            srcfile = WEB / ("lab" + str(lab)) / src
            target = out_path(lab, name)
            page = browser.new_page(viewport={"width": width, "height": height},
                                    device_scale_factor=1)
            try:
                page.goto(srcfile.resolve().as_uri(), wait_until="domcontentloaded", timeout=30000)
                page.wait_for_timeout(1300)
                if lab == 14 and not page.locator("#resume-root").inner_text().strip():
                    raise RuntimeError("Resume did not render")
                page.screenshot(path=str(target), full_page=False, animations="disabled")
                with Image.open(target) as img:
                    std = sum(ImageStat.Stat(img.convert("RGB").resize((160, 100))).stddev)
                    if std < 6:
                        raise RuntimeError("Page appears blank")
                print(f"captured lab{lab}: {src} -> {name}")
            except Exception:
                target.unlink(missing_ok=True)
                raise
            finally:
                page.close()
        browser.close()

    font = ImageFont.truetype("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf", 21)
    for label, src in NODE:
        script = WEB / "lab13" / src
        result = subprocess.run(["node", str(script)], cwd=script.parent,
                                capture_output=True, text=True, timeout=15, check=True)
        lines = ["$ node " + src, ""] + result.stdout.rstrip().splitlines()
        im = Image.new("RGB", (1150, max(200, 36 * len(lines) + 60)), "#182132")
        draw = ImageDraw.Draw(im)
        for i, line in enumerate(lines):
            draw.text((26, 28 + 36 * i), line, font=font,
                      fill="#a3e5d2" if i == 0 else "#f5f7fa")
        im.save(out_path(13, "node-" + label + ".png"), optimize=True)
        print(f"re-ran lab13: {src}")
    print("Reconstructed 20 images; none is presented as historical evidence.")


def prepare():
    if BUILD.exists():
        shutil.rmtree(BUILD)
    BUILD.mkdir(parents=True)
    total_missing = 0
    total_evidence = 0
    for lab in range(10, 15):
        original = WEB / ("lab" + str(lab)) / "latex-report"
        dest = BUILD / ("lab" + str(lab))
        shutil.copytree(original, dest,
                        ignore=shutil.ignore_patterns("*.pdf", "*.aux", "*.log", "*.out", "*.toc"))
        (dest / "img").mkdir(exist_ok=True)
        missing = 0
        for chapter in sorted((dest / "parts").glob("*.tex")):
            raw = chapter.read_text(encoding="utf-8")
            def remove_unsaved(m):
                nonlocal missing
                block = m.group(0)
                img = IMAGE.search(block)
                if not img:
                    return block
                stem = img.group(1)
                if any((dest / (stem + ext)).is_file()
                       for ext in ("", ".png", ".jpg", ".jpeg")):
                    return block
                missing += 1
                return "% Original screenshot absent in archive: original figure omitted.\n"
            raw = FIGURE.sub(remove_unsaved, raw)
            raw = raw.replace("TODO: вставить URL общего доступа к Figma-файлу",
                              "Архив: оригинальная ссылка на Figma не сохранилась")
            chapter.write_text(raw, encoding="utf-8")
        total_missing += missing
        note = (r"\section*{Примечание к архивной копии}" + "\n"
                "Это архивная версия сохранившегося текста отчёта, а не повторно "
                "выполненная лабораторная работа. Исторические скриншоты отсутствуют, "
                "поэтому соответствующие рисунки в этой копии опущены. "
                "Иллюстрации в приложении получены повторным отображением "
                "сохранённых исходников и не заменяют оригинальных свидетельств выполнения. "
                + NOTES[lab] + "\n" + r"\par\bigskip" + "\n")
        (dest / "parts" / "archive-note.tex").write_text(note, encoding="utf-8")
        app = [r"\appendix", r"\chapter{Восстановленные иллюстрации}",
               "Все рисунки в этом приложении созданы при архивировании по "
               "сохранённым файлам проекта. Они не являются прежними "
               "скриншотами Figma, Codepen или удалённого сервера."]
        included = 0
        for file, caption in CAPTIONS[lab].items():
            evidence = WEB / ("lab" + str(lab)) / "archive" / "evidence" / file
            if not evidence.is_file():
                raise FileNotFoundError(str(evidence))
            shutil.copy2(evidence, dest / "img" / ("archive-" + file))
            app += [r"\begin{figure}[htbp]", r"\centering",
                    r"\includegraphics[width=0.88\textwidth,height=0.72\textheight,keepaspectratio]{img/archive-"
                    + file + "}", r"\caption{" + caption + "}", r"\end{figure}"]
            included += 1
        total_evidence += included
        (dest / "parts" / "archive-appendix.tex").write_text("\n".join(app) + "\n", encoding="utf-8")
        main = dest / "main.tex"
        raw = main.read_text(encoding="utf-8")
        assert r"\input{parts/intro}" in raw and r"\input{parts/conclusion}" in raw
        raw = raw.replace(r"\input{parts/intro}",
                          r"\input{parts/archive-note}" + "\n" + r"\input{parts/intro}", 1)
        raw = raw.replace(r"\input{parts/conclusion}",
                          r"\input{parts/conclusion}" + "\n" +
                          r"\input{parts/archive-appendix}", 1)
        main.write_text(raw, encoding="utf-8")
        print(f"lab{lab}: omitted {missing} unsaved figures; appended {included} reconstructed images")
    if total_missing != 54 or total_evidence != 20:
        sys.exit(f"Audit failed: {total_missing} unsaved originals / {total_evidence} reconstruction renders; expected 54/20")
    print("Archival LaTeX prepared. Original report sources remain untouched.")


if __name__ == "__main__":
    if len(sys.argv) != 2 or sys.argv[1] not in {"capture", "prepare"}:
        sys.exit("usage: python archive_web.py capture|prepare")
    globals()[sys.argv[1]]()
