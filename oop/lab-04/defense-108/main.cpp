#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

class Hotel {
private:
    string name;
    int totalPlaces;
    int occupiedPlaces;
    double pricePerDay;

public:
    Hotel(string n, int total, int occupied, double price) {
        name = n;
        totalPlaces = total;
        occupiedPlaces = occupied;
        pricePerDay = price;
    }

    double monthlyLoss() const {
        return (totalPlaces - occupiedPlaces) * pricePerDay * 30;
    }

    bool isMoreThanHalfFull() const {
        return occupiedPlaces > totalPlaces / 2.0;
    }

    void show() const {
        cout << "Название: " << name << endl;
        cout << "Всего мест: " << totalPlaces << endl;
        cout << "Заселено мест: " << occupiedPlaces << endl;
        cout << fixed << setprecision(2);
        cout << "Оплата за день: " << pricePerDay << endl;
        cout << "Убытки за месяц: " << monthlyLoss() << endl;
        cout << endl;
    }
};

Hotel readHotel(ifstream& file) {
    string name;
    int total = 0;
    int occupied = 0;
    double price = 0;

    getline(file >> ws, name);
    file >> total >> occupied >> price;
    return Hotel(name, total, occupied, price);
}

int main() {
    ifstream file("gost.txt");
    if (!file) {
        cout << "Не удалось открыть gost.txt." << endl;
        return 1;
    }

    static Hotel hotel1 = readHotel(file);
    static Hotel hotel2 = readHotel(file);
    Hotel* hotel3 = new Hotel(readHotel(file));
    Hotel* hotel4 = new Hotel(readHotel(file));

    if (!file) {
        cout << "В gost.txt должны быть данные четырёх гостиниц." << endl;
        delete hotel3;
        delete hotel4;
        return 1;
    }

    cout << "Статические объекты:" << endl;
    hotel1.show();
    hotel2.show();

    cout << "Динамические объекты:" << endl;
    hotel3->show();
    hotel4->show();

    Hotel* hotels[4] = {&hotel1, &hotel2, hotel3, hotel4};
    vector<Hotel> selected;

    for (int i = 0; i < 4; i++) {
        if (hotels[i]->isMoreThanHalfFull())
            selected.push_back(*hotels[i]);
    }

    cout << "Гостиницы, где занято больше 50% мест:" << endl;
    if (selected.empty())
        cout << "Таких гостиниц нет." << endl;

    for (int i = 0; i < (int)selected.size(); i++)
        selected[i].show();

    delete hotel3;
    delete hotel4;
    return 0;
}
