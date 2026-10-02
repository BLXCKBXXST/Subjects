from pathlib import Path
import json
import sys
import textwrap
from xml.sax.saxutils import escape

from PIL import Image as PILImage, ImageDraw, ImageFont
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.lib import colors
from reportlab.lib.enums import TA_CENTER, TA_RIGHT, TA_JUSTIFY
from reportlab.lib.styles import ParagraphStyle
from reportlab.lib.pagesizes import A4
from reportlab.lib.units import mm
from reportlab.platypus import (
    SimpleDocTemplate, Paragraph, Spacer, PageBreak, Preformatted,
    Image, KeepTogether, Table, TableStyle,
)
from reportlab.graphics.shapes import Drawing, Rect, Ellipse, Line, Polygon, String

ROOT = Path(__file__).resolve().parents[1]
SETTINGS = json.loads((ROOT / 'reports/settings.json').read_text())
TMP = ROOT / 'build/report_images'
TMP.mkdir(parents=True, exist_ok=True)
FONTS = Path('/usr/share/fonts/truetype/dejavu')
for name, file in [('Body', 'DejaVuSerif.ttf'),
                   ('Bold', 'DejaVuSerif-Bold.ttf'),
                   ('Mono', 'DejaVuSansMono.ttf')]:
    pdfmetrics.registerFont(TTFont(name, str(FONTS / file)))

WIDTH = A4[0] - 45 * mm
BODY = ParagraphStyle('body', fontName='Body', fontSize=14, leading=21,
                      alignment=TA_JUSTIFY, firstLineIndent=12.5 * mm,
                      spaceAfter=8, splitLongWords=False)
HEAD = ParagraphStyle('head', fontName='Bold', fontSize=14, leading=21,
                      spaceBefore=12, spaceAfter=10, keepWithNext=True)
SMALL = ParagraphStyle('small', fontName='Body', fontSize=10, leading=14,
                       spaceAfter=6)
CENTER = ParagraphStyle('center', parent=BODY, alignment=TA_CENTER,
                        firstLineIndent=0)
RIGHT = ParagraphStyle('right', parent=BODY, alignment=TA_RIGHT,
                       firstLineIndent=0)
QUESTION = ParagraphStyle('question', fontName='Bold', fontSize=12, leading=18,
                          spaceBefore=6, spaceAfter=3, keepWithNext=True)
CODE = ParagraphStyle('code', fontName='Mono', fontSize=9, leading=10.5,
                      spaceAfter=10)

LABS = {
    1: {
        'theme': 'Простые классы', 'variant': '24',
        'goal': 'Научиться создавать класс, его поля, конструктор и методы. '
                'Показать чтение и изменение данных объекта.',
        'task': 'Создать класс «Аэропорт» с полями «статус» и «количество полос». '
                'Добавить конструктор, методы чтения и изменения полей и вывод '
                'всех данных. В main показать объект до и после изменения. '
                'Дополнительно используются название аэропорта и город.',
        'algorithm': [
            'Создать объект Airport и передать начальные значения в конструктор.',
            'Вызвать show и вывести все поля до изменения.',
            'Через setName, setCity, setStatus и setRunways изменить каждое поле.',
            'Снова вызвать show, затем вызвать все четыре метода get.',
        ],
        'explanation': [
            'Класс описан в airport.h. Поля находятся в private, поэтому main '
            'обращается к ним через методы. Конструктор сразу заполняет все поля.',
            'Методы get возвращают значения, методы set записывают новые. '
            'Метод show печатает сведения. const у методов чтения означает, '
            'что эти методы не меняют объект. Все данные в примере учебные.',
        ],
        'sources': ['lab-01/variant-24/airport.h',
                    'lab-01/variant-24/airport_basic.cpp'],
        'inputs': [['Поле', 'До изменения', 'После изменения'],
                   ['Название', 'Учебный аэропорт', 'Новый учебный аэропорт'],
                   ['Город', 'Новосибирск', 'Омск'],
                   ['Статус', 'Местный', 'Международный'],
                   ['Полосы', '1', '2']],
        'result': 'После вызова методов set изменились все четыре поля. '
                  'Методы get вернули те же значения, которые показал show. '
                  'Таким образом, работа всех методов класса проверена.',
        'questions': [
            ('Что такое класс и объект', 'Класс описывает данные и действия. '
             'Объект - конкретный экземпляр этого класса.'),
            ('Для чего нужен конструктор', 'Он вызывается при создании объекта '
             'и задаёт начальные значения его полей.'),
            ('Чем отличаются private и public', 'Доступ к private идёт из методов '
             'класса. К public можно обращаться из main и других частей программы.'),
        ],
        'conclusion': 'Создан класс Airport. Проверены конструктор, чтение, '
                      'изменение и вывод всех полей объекта.',
    },
    2: {
        'theme': 'Наследование и полиморфизм', 'variant': '24',
        'goal': 'Изучить наследование классов, вызов конструктора базового '
                'класса и переопределение виртуальных методов.',
        'task': 'Создать класс равностороннего треугольника со стороной a. '
                'Вычислять высоту, биссектрису, периметр и площадь. Создать '
                'наследника «Тетраэдр», добавить вычисление объёма, '
                'переопределить площадь и вывод. Для N треугольников найти '
                'среднюю площадь, для M правильных тетраэдров - объект с '
                'наименьшим объёмом.',
        'algorithm': [
            'Ввести N и M. Создать массивы triangles и pyramids.',
            'Ввести стороны N треугольников. Сложить их площади.',
            'Ввести рёбра M тетраэдров и вычислить их высоты.',
            'Вывести сведения обо всех фигурах. Тетраэдры выводить через '
            'указатель Triangle для проверки полиморфизма.',
            'Если N больше нуля, разделить сумму площадей на N. '
            'Иначе сообщить, что треугольников нет.',
            'Если M больше нуля, пройти по массиву и сохранить номер '
            'тетраэдра с наименьшим объёмом. Иначе сообщить об отсутствии тетраэдров.',
            'Освободить память обоих массивов.',
        ],
        'explanation': [
            'Triangle хранит сторону a в protected. Поэтому класс Tetrahedron '
            'имеет доступ к стороне. Дополнительное поле h хранит высоту '
            'тетраэдра. Конструктор наследника вызывает Triangle(side). '
            'Его setSide изменяет сторону и сразу пересчитывает h.',
            'Для треугольника h = a√3/2, биссектриса равна высоте, P = 3a, '
            'S = a²√3/4. Для правильного тетраэдра H = a√6/3, '
            'Sпов = 4S, V = SH/3 = a³√2/12. Площадь тетраэдра означает '
            'площадь всей поверхности.',
            'Методы area и show объявлены virtual и переопределены с override. '
            'Когда figure указывает на тетраэдр, figure->show() вызывает '
            'метод тетраэдра. Средняя площадь считается только по N отдельным '
            'треугольникам.',
        ],
        'sources': ['lab-02/variant-24/main.cpp'],
        'inputs': [['Данные', 'Значения'], ['N и M', '3 и 3'],
                   ['Стороны треугольников', '2, 4, 6'],
                   ['Рёбра тетраэдров', '4, 2, 3']],
        'result': 'Средняя площадь равна (√3 + 4√3 + 9√3) / 3 ≈ 8.083. '
                  'Минимальный объём у второго тетраэдра с ребром 2: '
                  'V = 2√2/3 ≈ 0.943. Программа получила те же значения. '
                  'При N = 0 и M = 0 деления на ноль и обращения к пустому '
                  'массиву нет. При равных минимумах выбирается первый объект.',
        'questions': [
            ('Понятие подкласса', 'Подкласс наследуется от базового класса, '
             'использует его доступные поля и методы и может добавлять свои.'),
            ('Использование конструктора суперкласса', 'В записи '
             'Tetrahedron(side) : Triangle(side) сначала выполняется '
             'конструктор Triangle, затем тело конструктора Tetrahedron.'),
            ('Наследование методов суперкласса', 'Публичные методы базового '
             'класса доступны наследнику. Виртуальный метод можно '
             'переопределить, чтобы вызов зависел от реального типа объекта.'),
        ],
        'conclusion': 'Реализованы два связанных класса. Проверены формулы, '
                      'средняя площадь, поиск минимального объёма и '
                      'виртуальный вызов метода вывода.',
    },
    3: {
        'theme': 'Работа с двоичными файлами', 'variant': '24',
        'goal': 'Научиться создавать бинарный файл из текстовых данных, '
                'читать записи и обрабатывать их.',
        'task': 'Вывести ведомость закупок чая из таблицы 7, хранящуюся '
                'в двоичном файле. Определить, в какой упаковке чай продаётся '
                'лучше. По общему заданию нужны класс записи, исходный '
                'текстовый файл и две отдельные программы.',
        'algorithm': [
            'В tea.txt записать число записей, тип чая, упаковку, производителя, '
            'цену и количество. Использовать семь строк таблицы 7.',
            'Программой create прочитать текстовый файл и записать число '
            'записей и объекты Tea в tea.bin.',
            'Программой process прочитать объекты Tea в массив teas циклом read. '
            'Двумя циклами сложить количества по четырём упаковкам таблицы 7.',
            'Вернуться к первой записи методом seekg, снова прочитать '
            'бинарный файл и вывести ведомость. Сумма строки равна цене, '
            'умноженной на количество.',
            'Найти наибольшее количество и вывести все упаковки с таким '
            'результатом. Если количества равны нулю, сообщить об отсутствии продаж.',
        ],
        'explanation': [
            'В качестве критерия «продаётся лучше» выбрано количество '
            'проданных единиц, а не выручка. Поэтому разные виды чая в '
            'одинаковой упаковке складываются вместе. Цена нужна для '
            'вывода суммы закупок.',
            'Поля type, package и brand имеют тип char[40]. Здесь нет '
            'указателей и объектов string, поэтому можно записать байты '
            'одного объекта Tea через write. Метод read читает столько же '
            'байт. Файл рассчитан на тот же компилятор и платформу; '
            'после переноса его можно заново создать из tea.txt.',
            'Сначала read читает число записей, затем циклом заполняет массив '
            'teas. packages содержит четыре упаковки таблицы 7, counts - их '
            'количества. Два цикла сравнивают упаковки и складывают количества. '
            'Перед выводом файл читается повторно по требованию методички.',
        ],
        'sources': ['lab-03/variant-24/tea.h',
                    'lab-03/variant-24/create.cpp',
                    'lab-03/variant-24/process.cpp'],
        'inputs': [['Упаковка', 'Расчёт количества', 'Всего'],
                   ['Пачка', '50 + 89', '139'],
                   ['Пакетики', '23 + 56 + 32', '111'],
                   ['Жесть', '23', '23'], ['Фарфор', '76', '76']],
        'result': 'Лучше продаётся чай в пачках: 139 единиц. Общая сумма '
                  'семи записей равна 3665.10 грн. Все данные совпадают '
                  'с ручным подсчётом. Проверены пустая ведомость, '
                  'отсутствие файла, отрицательное количество записей '
                  'и обрыв записи.',
        'questions': [
            ('Понятие файла', 'Файл - именованная последовательность данных '
             'на устройстве хранения.'),
            ('Способ описания файла', 'Для чтения используется ifstream, '
             'для записи ofstream. Режим ios::binary включает бинарную обработку.'),
            ('Описание структурного типа', 'Тип записи объединяет несколько '
             'полей. В работе запись задана классом Tea.'),
            ('Стандартные функции для работы с файлами', 'open открывает файл, '
             'close закрывает, read читает байты, write записывает, '
             'seekg меняет позицию чтения.'),
            ('Подготовка файла для чтения', 'Нужно создать ifstream с именем '
             'файла или вызвать open и проверить, что файл открылся.'),
            ('Функции чтения данных', 'Для текста применяются >> и getline, '
             'для бинарного файла применяется read.'),
            ('Как распознать конец файла', 'По результату попытки чтения. '
             'Если read не смог получить нужное количество байт, поток '
             'переходит в состояние ошибки; eof показывает достижение конца.'),
        ],
        'conclusion': 'Создан и обработан бинарный файл с семью записями. '
                      'Ведомость выведена после повторного чтения. '
                      'Найдена упаковка с максимальным общим количеством.',
    },
    4: {
        'theme': 'Контейнерный класс vector',
        'variant': 'Общее задание, класс из варианта 24 работы 1',
        'goal': 'Изучить vector, итераторы и стандартные алгоритмы '
                'копирования, сортировки и поиска места вставки.',
        'task': 'Создать вектор объектов класса из работы 1. Переписать '
                'подходящие объекты в новый вектор. Проверить его на '
                'пустоту, отсортировать и вставить новый объект без '
                'нарушения порядка. Количество исходных объектов вводится '
                'с клавиатуры. Критерии отбора и сортировки выбираются самостоятельно.',
        'algorithm': [
            'Ввести N и данные N аэропортов. Добавить объекты в airports.',
            'Вызвать copy_if и скопировать в selected аэропорты, '
            'у которых не меньше двух полос.',
            'Если selected пуст, вывести сообщение и закончить работу.',
            'Вызвать sort и упорядочить selected по возрастанию числа полос.',
            'Ввести новый аэропорт с двумя или более полосами.',
            'Найти место методом lower_bound, вставить объект через insert '
            'и вывести результат.',
        ],
        'explanation': [
            'Используется тот же класс Airport, что в первой работе. '
            'Отбор выполняет функция hasSeveralRunways. Функция fewerRunways '
            'сравнивает количество полос у двух объектов.',
            'Алгоритм copy_if берёт подходящие объекты, а back_inserter '
            'добавляет их в конец нового вектора. sort упорядочивает '
            'вектор. lower_bound находит первую позицию, где число полос '
            'не меньше числа полос нового аэропорта. insert вставляет '
            'его перед этой позицией. Для равных значений строгий '
            'порядок по названию не задаётся.',
        ],
        'sources': ['lab-01/variant-24/airport.h', 'lab-04/main.cpp'],
        'inputs': [['Объект', 'Число полос', 'Действие'],
                   ['Учебный А', '1', 'Не проходит отбор'],
                   ['Учебный Б', '4', 'Копируется'],
                   ['Учебный В', '2', 'Копируется'],
                   ['Учебный Г', '3', 'Вставляется']],
        'result': 'Отобраны аэропорты с 4 и 2 полосами. После сортировки '
                  'получен порядок 2, 4. Новый аэропорт с 3 полосами '
                  'вставлен между ними: 2, 3, 4. Проверены также пустой '
                  'исходный вектор и отсутствие подходящих объектов.',
        'methods': [['Метод или функция', 'Назначение'],
                    ['push_back', 'Добавить объект в конец'],
                    ['begin и end', 'Границы диапазона итераторов'],
                    ['empty и size', 'Проверка пустоты и числа объектов'],
                    ['copy_if и back_inserter', 'Скопировать подходящие объекты'],
                    ['sort', 'Сортировка по числу полос'],
                    ['lower_bound', 'Поиск позиции для вставки'],
                    ['insert', 'Вставка по итератору'],
                    ['for_each', 'Вызов функции вывода для объектов']],
        'questions': [
            ('Чем vector отличается от обычного массива', 'Вектор хранит '
             'свой размер и может увеличиваться при добавлении объектов.'),
            ('Для чего нужны итераторы', 'Они задают позиции в контейнере '
             'и позволяют алгоритмам проходить диапазон от begin до end.'),
            ('Почему сохраняется сортировка', 'lower_bound ищет позицию '
             'с тем же правилом сравнения, которое использовал sort.'),
        ],
        'conclusion': 'Вектор заполнен с клавиатуры. Проверены отбор, '
                      'пустота, сортировка и вставка с сохранением порядка.',
    },
    5: {
        'theme': 'Контейнерный класс list', 'variant': '23',
        'goal': 'Изучить создание списка объектов, добавление элементов '
                'и проход по списку с помощью итераторов.',
        'task': 'По варианту 23 создать список людей. Каждая запись '
                'содержит фамилию, имя, знак зодиака и дату рождения в '
                'массиве из трёх чисел. По введённому знаку зодиака '
                'создать новый список подходящих людей. Если совпадений '
                'нет, вывести сообщение. В методичке нет варианта 24, '
                'поэтому выбран последний доступный вариант 23.',
        'algorithm': [
            'Ввести N и данные N людей. Проверить каждую дату рождения.',
            'Добавить объекты Person в people с помощью push_back.',
            'Вывести исходный список и ввести знак зодиака для поиска.',
            'Пройти по people от begin до end. При совпадении знака '
            'добавить копию объекта в selected.',
            'Если selected пуст, вывести сообщение. Иначе показать '
            'количество найденных людей и новый список.',
        ],
        'explanation': [
            'В Person поля surname, name и zodiac имеют тип string. '
            'Дата хранится в birthday[3]: день, месяц и год. Метод input '
            'читает данные, show выводит одну запись.',
            'Функция validDate проверяет месяц, количество дней и '
            'високосный год. Знак зодиака вводится как готовая строка, '
            'его вычисление по дате не требуется. При поиске строки '
            'должны совпадать, включая регистр букв.',
            'Итератор it указывает на текущий объект. Запись it->show() '
            'вызывает метод этого объекта. Выражение *it возвращает сам '
            'объект, который копируется через selected.push_back(*it). '
            'Исходный список при этом сохраняется.',
        ],
        'sources': ['lab-05/variant-23/main.cpp'],
        'inputs': [['Человек', 'Знак', 'Дата'],
                   ['Иванов Иван', 'Овен', '2.4.2004'],
                   ['Петрова Анна', 'Телец', '12.5.2003'],
                   ['Сидоров Петр', 'Овен', '9.4.2005']],
        'result': 'При поиске «Овен» новый список содержит Иванова Ивана '
                  'и Сидорова Петра. При поиске «Рыбы» совпадений нет, '
                  'что показано отдельным запуском. Также проверены '
                  'пустой список и даты 29.2.2003 и 29.2.2004: первая '
                  'отклоняется, вторая принимается.',
        'methods': [['Метод', 'Назначение'],
                    ['push_back', 'Добавить объект в конец списка'],
                    ['begin и end', 'Начало и конец прохода'],
                    ['empty', 'Проверить отсутствие результатов'],
                    ['size', 'Узнать количество найденных людей']],
        'questions': [
            ('Понятие динамической структуры', 'Это структура, память '
             'для которой выделяется и изменяется во время работы программы.'),
            ('Описание структурного типа', 'Структурный тип объединяет '
             'связанные поля. Здесь для одной записи используется класс Person.'),
            ('Описание указателя', 'Указатель хранит адрес объекта. '
             'Итератор списка похож по способу обращения, но служит '
             'для прохода по элементам контейнера.'),
            ('Основные операции со списками', 'Создание, добавление, '
             'вставка, удаление, поиск, сортировка и вывод. В этой '
             'работе нужны создание, добавление, поиск и вывод.'),
        ],
        'conclusion': 'Создан список объектов Person. По заданному '
                      'знаку сформирован отдельный список. Проверены '
                      'совпадения и сообщение об отсутствии результата.',
    },
}


def paragraph(text, style=BODY):
    return Paragraph(escape(text), style)


def table(rows, compact=False):
    columns = len(rows[0])
    fractions = [0.33, 0.67] if columns == 2 else [0.31, 0.34, 0.35]
    cell_style = ParagraphStyle('cell', parent=SMALL,
                                fontSize=10 if compact else 11,
                                leading=12 if compact else 15)
    cells = [[paragraph(str(cell), cell_style) for cell in row] for row in rows]
    result = Table(cells, colWidths=[WIDTH * f for f in fractions], repeatRows=1)
    result.setStyle(TableStyle([
        ('GRID', (0, 0), (-1, -1), 0.5, colors.black),
        ('BACKGROUND', (0, 0), (-1, 0), colors.HexColor('#eeeeee')),
        ('VALIGN', (0, 0), (-1, -1), 'TOP'),
        ('LEFTPADDING', (0, 0), (-1, -1), 7),
        ('RIGHTPADDING', (0, 0), (-1, -1), 7),
        ('TOPPADDING', (0, 0), (-1, -1), 4 if compact else 7),
        ('BOTTOMPADDING', (0, 0), (-1, -1), 4 if compact else 7),
    ]))
    return result


def flowchart(num):
    labels = {
        1: ['Начало', 'Создать Airport', 'Вывести начальные поля',
            'Изменить все поля через set', 'Вывести поля через show и get', 'Конец'],
        2: ['Начало', 'Ввести N, M и стороны фигур', 'Вывести все фигуры',
            'N > 0: средняя площадь; иначе сообщение',
            'M > 0: минимальный объём; иначе сообщение', 'Освободить память', 'Конец'],
        3: ['Начало', 'Прочитать tea.txt и записать tea.bin',
            'Прочитать в массив, посчитать упаковки',
            'Повторно прочитать файл и вывести ведомость',
            'Вывести упаковки с максимальным количеством', 'Конец'],
        4: ['Начало', 'Ввод и заполнение airports', 'Отбор через copy_if',
            'selected пуст?', 'sort и ввод нового объекта',
            'lower_bound, insert и вывод', 'Конец'],
        5: ['Начало', 'Ввод и заполнение people', 'Ввод знака и отбор в selected',
            'selected пуст?', 'Вывести новый список', 'Конец'],
    }[num]
    gap = 42
    height = len(labels) * gap + 20
    d = Drawing(WIDTH, height)
    center = WIDTH / 2 - (42 if num in [4, 5] else 0)
    box_width = 275 if num in [2, 3] else 245
    def arrow(x1, y1, x2, y2):
        d.add(Line(x1, y1, x2, y2, strokeWidth=0.8))
        if x1 == x2:
            d.add(Polygon([x2, y2, x2 - 3, y2 + 6, x2 + 3, y2 + 6],
                          fillColor=colors.black))
        else:
            d.add(Polygon([x2, y2, x2 - 6, y2 - 3, x2 - 6, y2 + 3],
                          fillColor=colors.black))
    for i, label in enumerate(labels):
        y = height - 35 - i * gap
        if i in [0, len(labels) - 1]:
            d.add(Ellipse(center, y, 58, 19, fillColor=colors.white))
        elif '?' in label:
            d.add(Polygon([center, y + 20, center + 100, y,
                           center, y - 20, center - 100, y],
                          fillColor=colors.white))
            sx = WIDTH - 45
            arrow(center + 100, y, sx - 41, y)
            d.add(String(center + 107, y + 8, 'Да', fontName='Body', fontSize=9))
            d.add(Rect(sx - 41, y - 20, 82, 40, fillColor=colors.white))
            d.add(String(sx, y + 3, 'Сообщение', fontName='Body',
                         fontSize=9, textAnchor='middle'))
            d.add(String(sx, y - 10, 'об отсутствии', fontName='Body',
                         fontSize=9, textAnchor='middle'))
            end_y = height - 35 - (len(labels) - 1) * gap
            d.add(Line(sx, y - 20, sx, end_y, strokeWidth=0.8))
            d.add(Line(sx, end_y, center + 58, end_y, strokeWidth=0.8))
            d.add(String(center - 95, y - 18, 'Нет', fontName='Body', fontSize=9))
        else:
            d.add(Rect(center - box_width / 2, y - 18, box_width, 36,
                       fillColor=colors.white))
        lines = textwrap.wrap(label, width=37)
        for j, line in enumerate(lines):
            d.add(String(center, y + (len(lines) - 1) * 6 - j * 12 - 3,
                         line, fontName='Body', fontSize=10,
                         textAnchor='middle'))
        if i < len(labels) - 1:
            arrow(center, y - 19, center, y - gap + 19)
    return d


def output_images(num):
    output = (ROOT / f'lab-{num:02d}/result.txt').read_text()
    if num == 2:
        output = output[output.index('\nТреугольник 1'):].strip()
    if num == 4:
        first = output.index('Отобранные аэропорты')
        cut = output.index('Новый аэропорт', first)
        last = output.index('После вставки.')
        output = output[first:cut].rstrip() + '\n\n' + output[last:]
    if num == 5:
        output = output[output.index('Исходный список:'):]
    if num == 5:
        extra = (ROOT / 'lab-05/result_missing.txt').read_text()
        extra = extra[extra.index('Исходный список:'):]
        output += '\nОтдельный запуск: поиск Рыбы\n' + extra
    lines = []
    for line in output.splitlines():
        lines.extend(textwrap.wrap(line, width=76, replace_whitespace=False,
                                   drop_whitespace=False) or [''])
    font = ImageFont.truetype(str(FONTS / 'DejaVuSansMono.ttf'), 21)
    chunks = []
    remaining = lines
    while len(remaining) > 24:
        target = (len(remaining) + 1) // 2 if len(remaining) <= 48 else 24
        candidates = [i for i in range(max(8, target - 5), min(25, target + 5))
                      if remaining[i] == '']
        cut = min(candidates, key=lambda i: abs(i - target)) if candidates else target
        chunks.append(remaining[:cut])
        remaining = remaining[cut:]
        while remaining and not remaining[0]:
            remaining = remaining[1:]
    if remaining:
        chunks.append(remaining)
    images = []
    for index, chunk in enumerate(chunks):
        img = PILImage.new('RGB', (1020, 55 + len(chunk) * 30), '#15181d')
        draw = ImageDraw.Draw(img)
        for row, line in enumerate(chunk):
            draw.text((24, 20 + row * 30), line, font=font, fill='#f1f2f4')
        path = TMP / f'lab{num}-{index}.png'
        img.save(path)
        images.append(path)
    return images


def footer(canvas, doc):
    canvas.setTitle(f'Лабораторная работа {doc.lab_number} Язиков')
    canvas.setAuthor(SETTINGS['student'])
    if doc.page > 1:
        canvas.setFont('Body', 10)
        canvas.drawCentredString(A4[0] / 2, 12 * mm, str(doc.page))


def build(num, lab):
    story = []
    story.append(paragraph('Федеральное агентство связи', CENTER))
    story.append(Spacer(1, 12 * mm))
    story.append(paragraph('Сибирский государственный университет '
                           'телекоммуникаций и информатики', CENTER))
    story.append(Spacer(1, 28 * mm))
    story.append(paragraph('Кафедра ТС и ВС', CENTER))
    story.append(Spacer(1, 28 * mm))
    title = ParagraphStyle('title', parent=CENTER, fontName='Bold',
                           fontSize=18, leading=26)
    story.append(paragraph(f'Лабораторная работа №{num}', title))
    story.append(Spacer(1, 12 * mm))
    story.append(paragraph('По дисциплине Объектно-ориентированное '
                           'программирование', CENTER))
    story.append(Spacer(1, 25 * mm))
    story.append(paragraph('Выполнил: ' + SETTINGS['student'], RIGHT))
    story.append(paragraph('Группа: ' + SETTINGS['group'], RIGHT))
    story.append(paragraph('Вариант: ' + lab['variant'], RIGHT))
    story.append(Spacer(1, 10 * mm))
    story.append(paragraph('Проверила: ' + SETTINGS['teacher'], RIGHT))
    story.append(Spacer(1, 17 * mm))
    story.append(paragraph(f'Новосибирск {SETTINGS["year"]}', CENTER))
    story.append(PageBreak())
    story.append(paragraph(f'Лабораторная работа {num}', HEAD))
    story.append(paragraph('Тема: ' + lab['theme']))
    story.append(paragraph('Цель работы: ' + lab['goal']))
    story.append(paragraph('Задание', HEAD))
    story.append(paragraph(lab['task']))
    story.append(paragraph('Алгоритм решения', HEAD))
    for i, step in enumerate(lab['algorithm'], 1):
        story.append(paragraph(f'{i}. {step}'))
    story.append(PageBreak())
    story.append(paragraph('Схема алгоритма', HEAD))
    story.append(flowchart(num))
    story.append(paragraph('Схема отражает последовательность действий программы.', SMALL))
    story.append(Spacer(1, 6))
    story.append(paragraph('Пояснения к программе', HEAD))
    for text in lab['explanation']:
        story.append(paragraph(text))
    story.append(PageBreak())
    story.append(paragraph('Текст программы', HEAD))
    for file in lab['sources']:
        heading = paragraph(file, SMALL)
        source = '\n'.join(line for line in (ROOT / file).read_text().splitlines() if line.strip())
        first_code = ParagraphStyle('firstcode', parent=CODE, spaceAfter=0)
        lines = source.splitlines()
        story.append(KeepTogether([heading, Preformatted('\n'.join(lines[:3]), first_code)]))
        story.append(Preformatted('\n'.join(lines[3:]), CODE, maxLineLength=80))
    if num == 3:
        story.append(paragraph('Исходный текстовый файл tea.txt', HEAD))
        story.append(Preformatted((ROOT / 'lab-03/variant-24/tea.txt').read_text(), CODE))
    if 'methods' in lab:
        story.append(paragraph('Использованные методы и функции', HEAD))
        story.append(table(lab['methods'], compact=True))
    story.append(PageBreak())
    story.append(paragraph('Результаты выполнения', HEAD))
    story.append(paragraph('Программы собраны с параметрами '
                           '-std=c++11 -Wall -Wextra -pedantic. '
                           'Предупреждений компилятора нет. Ниже '
                           'приведены данные контрольного примера '
                           'и изображения фактического вывода.'))
    story.append(table(lab['inputs']))
    story.append(Spacer(1, 10))
    if num == 5:
        story.append(paragraph('Знак для поиска в основном запуске: Овен.'))
    for i, path in enumerate(output_images(num), 1):
        with PILImage.open(path) as im:
            h = WIDTH * im.height / im.width
        story.append(KeepTogether([Image(str(path), width=WIDTH, height=h),
                                   paragraph(f'Рисунок {i} - Вывод программы', SMALL)]))
        story.append(Spacer(1, 8))
    story.append(paragraph(lab['result']))
    story.append(PageBreak())
    story.append(paragraph('Ответы на контрольные вопросы', HEAD))
    for i, (question, answer) in enumerate(lab['questions'], 1):
        story.append(paragraph(f'{i}. {question}', QUESTION))
        story.append(paragraph(answer))
    story.append(paragraph('Вывод', HEAD))
    story.append(paragraph(lab['conclusion']))
    output = ROOT / f'lab-{num:02d}' / f'Лаб№{num}_Язиков.pdf'
    doc = SimpleDocTemplate(str(output), pagesize=A4,
                            leftMargin=30 * mm, rightMargin=15 * mm,
                            topMargin=20 * mm, bottomMargin=20 * mm)
    doc.lab_number = num
    doc.build(story, onFirstPage=footer, onLaterPages=footer)
    print(output)


if __name__ == '__main__':
    numbers = [int(sys.argv[1])] if len(sys.argv) > 1 else LABS
    for number in numbers:
        build(number, LABS[number])
