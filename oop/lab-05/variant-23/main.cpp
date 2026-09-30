#include <iostream>
#include <string>
#include <list>
using namespace std;

bool validDate(int day, int month, int year) {
    if (year < 1 || month < 1 || month > 12)
        return false;
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
        days[1] = 29;
    return day >= 1 && day <= days[month - 1];
}

class Person {
public:
    string surname;
    string name;
    string zodiac;
    int birthday[3];

    bool input() {
        cout << "Фамилия: ";
        getline(cin >> ws, surname);
        cout << "Имя: ";
        getline(cin >> ws, name);
        cout << "Знак зодиака: ";
        getline(cin >> ws, zodiac);
        cout << "Дата рождения (день месяц год): ";
        if (!(cin >> birthday[0] >> birthday[1] >> birthday[2]))
            return false;
        return validDate(birthday[0], birthday[1], birthday[2]);
    }

    void show() {
        cout << surname << " " << name << " | " << zodiac << " | ";
        cout << birthday[0] << "." << birthday[1] << "." << birthday[2] << endl;
    }
};

int main() {
    int n;
    cout << "Количество людей: ";
    if (!(cin >> n) || n < 0 || n > 10000) {
        cout << "Количество должно быть от 0 до 10000." << endl;
        return 1;
    }

    list<Person> people;
    for (int i = 0; i < n; i++) {
        cout << "\nЧеловек " << i + 1 << endl;
        Person person;
        if (!person.input()) {
            cout << "Неверная дата рождения." << endl;
            return 1;
        }
        people.push_back(person);
    }

    cout << "\nИсходный список:" << endl;
    for (list<Person>::iterator it = people.begin();
         it != people.end(); it++)
        it->show();

    string sign;
    cout << "Знак зодиака для поиска: ";
    if (!getline(cin >> ws, sign)) {
        cout << "Не удалось прочитать знак зодиака." << endl;
        return 1;
    }

    list<Person> selected;
    for (list<Person>::iterator it = people.begin();
         it != people.end(); it++) {
        if (it->zodiac == sign)
            selected.push_back(*it);
    }

    if (selected.empty()) {
        cout << "Людей с таким знаком зодиака нет." << endl;
    } else {
        cout << "\nНовый список. Найдено: " << selected.size() << endl;
        for (list<Person>::iterator it = selected.begin();
             it != selected.end(); it++)
            it->show();
    }
    return 0;
}
