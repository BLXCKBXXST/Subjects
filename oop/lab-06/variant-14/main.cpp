#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Toy {
public:
    string name;
    double price;

    void input() {
        cout << "Название игрушки: ";
        getline(cin >> ws, name);
        cout << "Стоимость: ";
        cin >> price;
    }
};

void show(queue<Toy> q) {
    while (!q.empty()) {
        cout << q.front().name << " - " << q.front().price << endl;
        q.pop();
    }
}

int main() {
    int n;
    cout << "Количество игрушек: ";
    cin >> n;

    queue<Toy> toys;
    for (int i = 0; i < n; i++) {
        Toy toy;
        toy.input();
        toys.push(toy);
    }

    cout << "\nОчередь игрушек:\n";
    show(toys);

    string name;
    cout << "\nНазвание игрушки для поиска: ";
    getline(cin >> ws, name);

    queue<Toy> q = toys;
    while (!q.empty()) {
        if (q.front().name == name)
            cout << "Стоимость: " << q.front().price << endl;
        q.pop();
    }

    cout << "\nНовое поступление:\n";
    Toy toy;
    toy.input();
    toys.push(toy);

    cout << "\nОчередь после поступления:\n";
    show(toys);

    q = toys;
    Toy expensive = q.front();
    while (!q.empty()) {
        if (q.front().price > expensive.price)
            expensive = q.front();
        q.pop();
    }

    cout << "\nСамая дорогая игрушка: "
         << expensive.name << " - " << expensive.price << endl;

    return 0;
}
