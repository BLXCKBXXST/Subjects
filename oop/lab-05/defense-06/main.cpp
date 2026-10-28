#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
using namespace std;

class Train {
public:
    int number;
    string station;
    double ticketPrice;
    int seats;
    int soldTickets;

    void input(ifstream& file) {
        file >> number;
        getline(file >> ws, station);
        file >> ticketPrice >> seats >> soldTickets;
    }

    int unsoldTickets() const {
        return seats - soldTickets;
    }

    void show() const {
        cout << "Номер поезда: " << number << endl;
        cout << "Станция следования: " << station << endl;
        cout << "Стоимость билета: " << fixed << setprecision(2)
             << ticketPrice << endl;
        cout << "Число мест: " << seats << endl;
        cout << "Продано билетов: " << soldTickets << endl;
        cout << "Не продано билетов: " << unsoldTickets() << endl;
        cout << endl;
    }
};

int main() {
    ifstream file("Edem.txt");
    if (!file) {
        cout << "Не удалось открыть Edem.txt." << endl;
        return 1;
    }

    int n;
    file >> n;
    list<Train> trains;

    for (int i = 0; i < n; i++) {
        Train train;
        train.input(file);
        trains.push_back(train);
    }

    cout << "Исходный список:" << endl;
    for (list<Train>::iterator it = trains.begin();
         it != trains.end(); it++)
        it->show();

    list<Train> selected;
    for (list<Train>::iterator it = trains.begin();
         it != trains.end(); it++) {
        if (it->unsoldTickets() > it->seats / 2.0)
            selected.push_back(*it);
    }

    if (selected.empty()) {
        cout << "Поездов с непроданными билетами больше половины мест нет."
             << endl;
    } else {
        cout << "Поезда, у которых непродано больше половины мест:" << endl;
        cout << "Найдено: " << selected.size() << endl;
        for (list<Train>::iterator it = selected.begin();
             it != selected.end(); it++)
            it->show();
    }
    return 0;
}
