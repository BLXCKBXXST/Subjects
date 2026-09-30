#include "tea.h"
#include <fstream>
#include <string>
#include <cmath>

int main() {
    ifstream binary("tea.bin", ios::binary);
    int n;
    if (!binary.read((char*)&n, sizeof(n)) || n < 0 || n > 10000) {
        cout << "Файл tea.bin отсутствует или поврежден." << endl;
        return 1;
    }
    if (n == 0) {
        cout << "Ведомость пуста." << endl;
        return 0;
    }

    string* packages = new string[n];
    long long* counts = new long long[n]();
    int kinds = 0;
    Tea tea = {};

    for (int i = 0; i < n; i++) {
        if (!binary.read((char*)&tea, sizeof(tea)) ||
            tea.type[39] != '\0' || tea.package[39] != '\0' ||
            tea.brand[39] != '\0' || tea.type[0] == '\0' ||
            tea.package[0] == '\0' || tea.brand[0] == '\0' ||
            !isfinite(tea.price) || tea.price < 0 || tea.price > 1000000 ||
            tea.quantity < 0 || tea.quantity > 1000000) {
            cout << "Файл tea.bin поврежден." << endl;
            delete[] packages;
            delete[] counts;
            return 1;
        }
        int j = 0;
        while (j < kinds && packages[j] != tea.package)
            j++;
        if (j == kinds) {
            packages[j] = tea.package;
            kinds++;
        }
        counts[j] += tea.quantity;
    }

    binary.seekg(sizeof(n));
    cout << "Тип | Упаковка | Производитель | Цена, грн | "
         << "Количество | Сумма, грн" << endl;
    double total = 0;
    for (int i = 0; i < n; i++) {
        binary.read((char*)&tea, sizeof(tea));
        tea.show();
        total += tea.total();
    }
    cout << "Всего, грн: " << total << endl;

    long long best = 0;
    cout << "\nПродажи по упаковкам (штук):" << endl;
    for (int i = 0; i < kinds; i++) {
        cout << packages[i] << ": " << counts[i] << endl;
        if (counts[i] > best)
            best = counts[i];
    }
    if (best == 0) {
        cout << "Продаж нет." << endl;
    } else {
        cout << "Лучше продается:" << endl;
        for (int i = 0; i < kinds; i++) {
            if (counts[i] == best)
                cout << packages[i] << " (" << best << " шт.)" << endl;
        }
    }

    delete[] packages;
    delete[] counts;
    return 0;
}
