#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
using namespace std;

class Subscriber {
public:
    string fio;
    string phone;
    int birthday[3];

    void input() {
        cout << "ФИО: ";
        getline(cin >> ws, fio);
        cout << "Номер телефона: ";
        getline(cin >> ws, phone);
        cout << "Дата рождения (день месяц год): ";
        cin >> birthday[0] >> birthday[1] >> birthday[2];
    }

    void show() {
        cout << fio << " | " << phone << " | ";
        cout << birthday[0] << "." << birthday[1] << "."
             << birthday[2] << endl;
    }
};

bool newerYear(Subscriber a, Subscriber b) {
    return a.birthday[2] > b.birthday[2];
}

int main() {
    int n;
    cout << "Количество абонентов: ";
    cin >> n;

    deque<Subscriber> people;
    for (int i = 0; i < n; i++) {
        Subscriber person;
        person.input();
        people.push_back(person);
    }

    sort(people.begin(), people.end(), newerYear);
    cout << "\nОчередь по убыванию года рождения:" << endl;
    for (int i = 0; i < n; i++)
        people[i].show();

    int day;
    cout << "Число рождения для поиска: ";
    cin >> day;
    for (int i = 0; i < n; i++) {
        if (people[i].birthday[0] == day)
            people[i].show();
    }

    string answer;
    cout << "\nХотите добавить нового абонента? (да/нет): ";
    cin >> answer;
    if (answer == "да") {
        Subscriber person;
        person.input();
        deque<Subscriber>::iterator position = lower_bound(
            people.begin(), people.end(), person, newerYear);
        people.insert(position, person);
        n++;

        cout << "\nОчередь после добавления:" << endl;
        for (int i = 0; i < n; i++)
            people[i].show();
    }
    return 0;
}
