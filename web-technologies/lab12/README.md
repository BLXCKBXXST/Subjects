# Лабораторная работа №12
**Основы HTML и CSS**

После двух дизайн-лаб ([lab10](../lab10/), [lab11](../lab11/)), где макет
рисовался в Figma, эта работа возвращает на уровень кода: студент пишет
HTML и CSS руками, решая четыре независимых Codepen-задания. Здесь лежат
методичка, локальные решения и LaTeX-отчёт.


**Архив предмета:** [PDF-копия отчёта](archive/lab12_archival.pdf) и [восстановленные материалы](archive/README.md). Четыре локальных решения заново отображены в браузере. Скриншоты прежних форков Codepen не сохранились. Это архив уже законченной дисциплины — повторно выполнять лабораторную ради документации не требуется.

---

## 🛠️ Среда

| Что | Где |
|---|---|
| Онлайн-редактор | [Codepen](https://codepen.io) (бесплатный аккаунт) |
| Локальный браузер | любой современный (Chromium, Firefox) для просмотра `codepen-solutions/*/index.html` |
| Эталонные стили заданий | [`styles.css`](https://netology-code.github.io/resourses/codepen/styles.css) и [`style.css`](https://netology-code.github.io/resourses/codepen/style.css) Netology |
| UI-фреймворк pen-ов | [Material Design Lite](https://getmdl.io) (`material.indigo-pink.min.css`) |

---

## 📋 Задачи

Методичка делит работу на два блока (HTML и CSS), внутри каждого — два
подблока с несколькими задачами:

**Блок 1. Основы HTML**

1. **1.1 — Теги для разметки текста и атрибуты.** Разметить три секции:
   текст про нейросети (`<h2>` + два `<p>` + ссылка), исправить
   разметку «Дороги» (заголовок + абзацы + цитата), оформить заметки про
   гейзеры Камчатки (`<h3>` + `<img>` + `<p>`).
2. **1.2 — Списки и таблицы.** Составить маркированный и нумерованный
   списки, написать таблицу заказа аниматоров с `<tfoot>` и `colspan`,
   починить «развалившуюся» таблицу звёзд эстрады до формата 7 × 4.

**Блок 2. Основы CSS**

3. **2.1 — Селекторы и свойства.** Написать четыре CSS-правила к разметке
   «Калуша с Калушатами»: цвет вложенного `<h2>`, цвет всех `<strong>`,
   стилизация `<span>` внутри `<blockquote>`, курсив `<strong>` внутри
   `<ol>`.
4. **2.2 — Оформление текстовых блоков при помощи CSS.** Стилизовать
   страницу про Эйнштейна: класс `main-header`, все абзацы, `<strong>`
   в `.lead`, два уровня маркеров в `.works-list`, цитата на фоновой
   картинке.

---

## 📁 Структура папки

```
lab12/
├── README.md                       ← этот файл
├── Методичка (lab12).pdf           ← задание преподавателя
│
├── codepen-solutions/              ← четыре локальных решения
│   ├── README.md                   ← workflow Fork → правки → Save → URL
│   ├── img/                        ← 4 JPG из методички (Yandex Disk)
│   ├── 1.1-html-tags/index.html
│   ├── 1.2-lists-tables/index.html
│   ├── 2.1-selectors/{index.html, styles.css}
│   └── 2.2-text-styling/{index.html, styles.css}
│
└── latex-report/                   ← LaTeX-отчёт для Overleaf
    ├── main.tex, config.tex, parts/, fonts/, screenshots/, img/
    └── lab12_latex_report.pdf      ← скомпилированный отчёт (появится после компиляции)
```

---

## 🚀 Порядок работы

1. **Открыть локальные решения.** `xdg-open codepen-solutions/1.1-html-tags/index.html`
   и т.д. для четырёх блоков. Картинки лежат локально, CSS Netology и MDL
   тянутся с CDN — для первого открытия нужен интернет.
2. **Зайти на Codepen,** перейти на каждый из четырёх стартовых pen-ов
   (ссылки `clck.ru/...` — см. [`codepen-solutions/README.md`](codepen-solutions/README.md)).
3. **Форкнуть каждый pen** (`Fork` в правом верхнем углу).
4. **Перенести правки** из локальных `index.html`/`styles.css` в
   соответствующие панели форка.
5. **Сохранить форк** (`Save`), скопировать URL и вписать его в
   [`latex-report/parts/chap3.tex`](latex-report/parts/chap3.tex) рядом с
   соответствующим блоком (для текущего варианта уже подставлено).
6. **Снять скриншоты** по списку [`latex-report/screenshots/README.md`](latex-report/screenshots/README.md)
   и положить в [`latex-report/img/`](latex-report/img/).
7. **Скомпилировать отчёт** в Overleaf (Compiler: **XeLaTeX**, Main:
   `main.tex`) → положить итоговый PDF рядом с `main.tex`.

---

## 🔗 Ссылки на форки Codepen

| Блок | URL форка |
|---|---|
| 1.1 | [codepen.io/blxckweed/pen/EaNmYge](https://codepen.io/blxckweed/pen/EaNmYge) |
| 1.2 | [codepen.io/blxckweed/pen/YPpVKpm](https://codepen.io/blxckweed/pen/YPpVKpm) |
| 2.1 | [codepen.io/blxckweed/pen/vEymBmY](https://codepen.io/blxckweed/pen/vEymBmY) |
| 2.2 | [codepen.io/blxckweed/pen/vEymBxB](https://codepen.io/blxckweed/pen/vEymBxB) |

Эти же URL подставлены в `latex-report/parts/chap3.tex`.

---

## 📤 Формат сдачи

PDF-отчёт (скомпилированный из `latex-report/`) + четыре URL форков
Codepen — загружаются в ЭИОС. Локальные `codepen-solutions/*/index.html`
не сдаются преподавателю напрямую — это вспомогательный материал для
быстрого редактирования вне Codepen.

---

## Отчёт

В [latex-report/](latex-report/README.md) находятся LaTeX-исходники и подробная инструкция по сборке. [Список скриншотов](latex-report/screenshots/README.md) указывает реальные кадры, которые нужно получить и положить в `latex-report/img/`. **В Subjects пока нет готового PDF этой работы**: после добавления изображений собери отчёт через XeLaTeX или импортируй ZIP в Overleaf по инструкции.

[Общие правила для отчётов](../REPORTS.md).
