#include "tea.h"
#include <fstream>
#include <limits>
#include <cmath>
#include <cstdio>

int main() {
    ifstream text("tea.txt");
    if (!text) {
        cout << "Не удалось открыть tea.txt." << endl;
        return 1;
    }

    int n;
    if (!(text >> n) || n < 0 || n > 10000) {
        cout << "Неверное количество записей." << endl;
        return 1;
    }
    text.ignore(numeric_limits<streamsize>::max(), '\n');

    ofstream binary("tea.bin", ios::binary);
    if (!binary) {
        cout << "Не удалось создать tea.bin." << endl;
        return 1;
    }
    binary.write((char*)&n, sizeof(n));

    for (int i = 0; i < n; i++) {
        Tea tea = {};
        text.getline(tea.type, 40);
        text.getline(tea.package, 40);
        text.getline(tea.brand, 40);
        if (!(text >> tea.price >> tea.quantity) ||
            !isfinite(tea.price) || tea.price < 0 || tea.price > 1000000 ||
            tea.quantity < 0 || tea.quantity > 1000000 ||
            tea.type[0] == '\0' || tea.package[0] == '\0' ||
            tea.brand[0] == '\0') {
            cout << "Ошибка в записи " << i + 1 << endl;
            binary.close();
            remove("tea.bin");
            return 1;
        }
        text.ignore(numeric_limits<streamsize>::max(), '\n');
        binary.write((char*)&tea, sizeof(tea));
    }

    binary.close();
    if (!binary) {
        cout << "Ошибка записи tea.bin." << endl;
        return 1;
    }
    cout << "Создан tea.bin. Записей: " << n << endl;
    return 0;
}
