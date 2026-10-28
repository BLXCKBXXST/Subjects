#include <iostream>
#include <string>
#include <list>
using namespace std;

class Person {
public:
    string surname;
    string name;
    string zodiac;
    int birthday[3];

    void input() {
        cout << "Фамилия: ";
        getline(cin >> ws, surname);
        cout << "Имя: ";
        getline(cin >> ws, name);
        cout << "Знак зодиака: ";
        getline(cin >> ws, zodiac);
        cout << "Дата рождения (день месяц год): ";
        cin >> birthday[0] >> birthday[1] >> birthday[2];
    }

    void show() {
        cout << surname << " " << name << " | " << zodiac << " | ";
        cout << birthday[0] << "." << birthday[1] << "." << birthday[2] << endl;
    }
};

int main() {
    int n;
    cout << "Количество людей: ";
    cin >> n;

    list<Person> people;
    for (int i = 0; i < n; i++) {
        cout << "\nЧеловек " << i + 1 << endl;
        Person person;
        person.input();
        people.push_back(person);
    }

    cout << "\nИсходный список:" << endl;
    for (list<Person>::iterator it = people.begin();
         it != people.end(); it++)
        it->show();

    string sign;
    cout << "Знак зодиака для поиска: ";
    getline(cin >> ws, sign);

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
