#include "tea.h"
#include <fstream>
#include <string>

int main() {
    ifstream binary("tea.bin", ios::binary);
    int n;
    if (!binary.read((char*)&n, sizeof(n)) || n < 0) {
        cout << "Файл tea.bin отсутствует или поврежден." << endl;
        return 1;
    }
    if (n == 0) {
        cout << "Ведомость пуста." << endl;
        return 0;
    }

    Tea* teas = new Tea[n];
    for (int i = 0; i < n; i++) {
        binary.read((char*)&teas[i], sizeof(Tea));
    }
    if (!binary) {
        cout << "Файл tea.bin поврежден." << endl;
        delete[] teas;
        return 1;
    }

    string packages[4] = {"Пачка", "Пакетики", "Жесть", "Фарфор"};
    long long counts[4] = {};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            if (teas[i].package == packages[j])
                counts[j] += teas[i].quantity;
        }
    }

    binary.seekg(sizeof(n));
    cout << "Тип | Упаковка | Производитель | Цена, грн | "
         << "Количество | Сумма, грн" << endl;
    double total = 0;
    for (int i = 0; i < n; i++) {
        binary.read((char*)&teas[i], sizeof(Tea));
        teas[i].show();
        total += teas[i].total();
    }
    cout << "Всего, грн: " << total << endl;

    long long best = 0;
    cout << "\nПродажи по упаковкам (штук):" << endl;
    for (int i = 0; i < 4; i++) {
        cout << packages[i] << ": " << counts[i] << endl;
        if (counts[i] > best)
            best = counts[i];
    }
    if (best == 0) {
        cout << "Продаж нет." << endl;
    } else {
        cout << "Лучше продается:" << endl;
        for (int i = 0; i < 4; i++) {
            if (counts[i] == best)
                cout << packages[i] << " (" << best << " шт.)" << endl;
        }
    }

    delete[] teas;
    return 0;
}
