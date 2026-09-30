#include "airport.h"

int main() {
    Airport airport("Учебный аэропорт", "Новосибирск", "Местный", 1);

    cout << "До изменения:" << endl;
    airport.show();

    airport.setName("Новый учебный аэропорт");
    airport.setCity("Омск");
    airport.setStatus("Международный");
    airport.setRunways(2);

    cout << "\nПосле изменения:" << endl;
    airport.show();

    cout << "\nЧтение полей через методы:" << endl;
    cout << airport.getName() << endl;
    cout << airport.getCity() << endl;
    cout << airport.getStatus() << endl;
    cout << airport.getRunways() << endl;

    return 0;
}
