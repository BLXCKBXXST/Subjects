#include "../lab-01/variant-24/airport.h"
#include <vector>
#include <algorithm>
#include <iterator>

bool hasSeveralRunways(const Airport& airport) {
    return airport.getRunways() >= 2;
}

bool fewerRunways(const Airport& first, const Airport& second) {
    return first.getRunways() < second.getRunways();
}

void showAirport(const Airport& airport) {
    airport.show();
    cout << endl;
}

int main() {
    int n;
    cout << "Количество аэропортов: ";
    if (!(cin >> n) || n < 0 || n > 10000) {
        cout << "Количество должно быть от 0 до 10000." << endl;
        return 1;
    }

    vector<Airport> airports;
    string name, city, status;
    int runways;

    for (int i = 0; i < n; i++) {
        cout << "\nАэропорт " << i + 1 << endl;
        cout << "Название: ";
        getline(cin >> ws, name);
        cout << "Город: ";
        getline(cin >> ws, city);
        cout << "Статус: ";
        getline(cin >> ws, status);
        cout << "Количество полос: ";
        if (!(cin >> runways) || runways < 1) {
            cout << "Количество полос должно быть положительным." << endl;
            return 1;
        }
        airports.push_back(Airport(name, city, status, runways));
    }

    cout << "\nИсходный вектор:" << endl;
    for_each(airports.begin(), airports.end(), showAirport);

    vector<Airport> selected;
    copy_if(airports.begin(), airports.end(),
            back_inserter(selected), hasSeveralRunways);

    if (selected.empty()) {
        cout << "Нет аэропортов с двумя и более полосами." << endl;
        return 0;
    }

    sort(selected.begin(), selected.end(), fewerRunways);
    cout << "Отобранные аэропорты по возрастанию числа полос:" << endl;
    for_each(selected.begin(), selected.end(), showAirport);

    cout << "Новый аэропорт" << endl;
    cout << "Название: ";
    getline(cin >> ws, name);
    cout << "Город: ";
    getline(cin >> ws, city);
    cout << "Статус: ";
    getline(cin >> ws, status);
    cout << "Количество полос (не меньше 2): ";
    if (!(cin >> runways) || runways < 2) {
        cout << "Новый аэропорт не подходит под условие отбора." << endl;
        return 1;
    }

    Airport airport(name, city, status, runways);
    vector<Airport>::iterator position = lower_bound(
        selected.begin(), selected.end(), airport, fewerRunways);
    selected.insert(position, airport);

    cout << "\nПосле вставки. Объектов: " << selected.size() << endl;
    for_each(selected.begin(), selected.end(), showAirport);
    return 0;
}
