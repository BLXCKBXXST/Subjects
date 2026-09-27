#!/usr/bin/env python3
"""Проверка связей между LaTeX, списками скриншотов и файлами img/."""

import argparse
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
IMAGE_REF = re.compile(
    r"\\(?:includegraphics|ReportImage)(?:\[[^\]]*\])?\{img/([^}]+)\}"
)
GUIDE_NAME = re.compile(r"\x60([0-9]{2}_[^\x60 \t\n]+\.(?:png|jpe?g))\x60", re.I)


def candidates(name: str) -> list[str]:
    if Path(name).suffix.lower() in {".png", ".jpg", ".jpeg"}:
        return [name]
    return [name + ext for ext in (".png", ".jpg", ".jpeg")]


def check_lab(number: int) -> tuple[list[str], list[str]]:
    lab = ROOT / f"lab{number}" / "latex-report"
    problems: list[str] = []
    unfinished: list[str] = []
    guide = lab / "screenshots" / "README.md"
    if not guide.is_file():
        return [f"lab{number}: нет screenshots/README.md"], []

    documented = set(GUIDE_NAME.findall(guide.read_text(encoding="utf-8")))
    referenced: set[str] = set()
    chapters = list((lab / "parts").glob("*.tex"))
    if not chapters or not (lab / "main.tex").exists():
        return [f"lab{number}: не найдены main.tex или главы отчёта"], []

    for chapter in chapters:
        body = chapter.read_text(encoding="utf-8")
        referenced.update(IMAGE_REF.findall(body))
        if number >= 10 and "TODO: вставить URL общего доступа" in body:
            unfinished.append(f"lab{number}: не заменена ссылка на Figma в {chapter.name}")

    for name in sorted(referenced):
        options = candidates(name)
        if not any(option in documented for option in options):
            problems.append(f"lab{number}: img/{name} используется в TeX, но не описан в списке")
        if not any((lab / "img" / option).is_file() for option in options):
            unfinished.append(f"lab{number}: нет реального изображения img/{name}")

    for name in sorted(documented):
        if not any(name in candidates(ref) for ref in referenced):
            problems.append(f"lab{number}: {name} указан в списке, но не включён в главы")
    if not (lab / "README.md").is_file():
        problems.append(f"lab{number}: нет инструкции latex-report/README.md")
    return problems, unfinished



def check_archive() -> int:
    """Check completed archival PDFs and genuinely rendered evidence, not lost originals."""
    expected = {10: 3, 11: 7, 12: 4, 13: 4, 14: 2}
    errors: list[str] = []
    for lab, number in expected.items():
        archive = ROOT / f"lab{lab}" / "archive"
        pdf = archive / f"lab{lab}_archival.pdf"
        images = sorted((archive / "evidence").glob("*.png"))
        if not (archive / "README.md").is_file():
            errors.append(f"lab{lab}: нет архивного README")
        if not pdf.is_file() or pdf.stat().st_size < 10000 or not pdf.read_bytes().startswith(b"%PDF-"):
            errors.append(f"lab{lab}: архивный PDF отсутствует или некорректен")
        if len(images) != number:
            errors.append(f"lab{lab}: найдено {len(images)} восстановленных PNG вместо {number}")
        for img in images:
            if not img.read_bytes().startswith(b"\x89PNG\r\n\x1a\n"):
                errors.append(f"lab{lab}: некорректный PNG {img.name}")
        print(f"lab{lab}: архивный PDF {'есть' if pdf.is_file() else 'НЕТ'}, PNG: {len(images)}/{number}")
    for err in errors:
        print("ERROR:", err)
    if errors:
        return 1
    print("Архивные файлы на месте. Это не проверка отсутствующих исторических скриншотов.")
    return 0


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--strict", action="store_true",
        help="Также считать ошибкой отсутствие реальных изображений и незаменённые TODO",
    )
    parser.add_argument("--archive", action="store_true", help="Проверить готовые архивные PDF и восстановленные изображения")
    args = parser.parse_args()
    if args.archive:
        return check_archive()
    errors: list[str] = []
    unfinished: list[str] = []
    for number in range(4, 15):
        issues, missing = check_lab(number)
        errors.extend(issues)
        unfinished.extend(missing)
        status = "OK" if not issues else "ОШИБКА"
        print(f"lab{number}: {status}, незавершённых пунктов: {len(missing)}")

    for item in errors:
        print("ERROR:", item)
    for item in unfinished:
        print("TODO:", item)

    if errors:
        return 1
    if unfinished and args.strict:
        return 2
    if unfinished:
        print("Структура согласована, но поздние отчёты ещё требуют реальных скриншотов.")
    else:
        print("Ссылки и изображения согласованы; проверь итоговый PDF глазами.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
