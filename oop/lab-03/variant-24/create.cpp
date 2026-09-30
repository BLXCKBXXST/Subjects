#include "tea.h"
#include <fstream>

int main() {
    ifstream text("tea.txt");
    if (!text) {
        cout << "Не удалось открыть tea.txt." << endl;
        return 1;
    }

    int n;
    if (!(text >> n) || n < 0) {
        cout << "Неверное количество записей." << endl;
        return 1;
    }

    ofstream binary("tea.bin", ios::binary);
    if (!binary) {
        cout << "Не удалось создать tea.bin." << endl;
        return 1;
    }
    binary.write((char*)&n, sizeof(n));

    for (int i = 0; i < n; i++) {
        Tea tea = {};
        text >> ws;
        text.getline(tea.type, 40);
        text.getline(tea.package, 40);
        text.getline(tea.brand, 40);
        if (!(text >> tea.price >> tea.quantity)) {
            cout << "Ошибка в записи " << i + 1 << endl;
            return 1;
        }
        binary.write((char*)&tea, sizeof(tea));
    }

    text.close();
    binary.close();
    cout << "Создан tea.bin. Записей: " << n << endl;
    return 0;
}
