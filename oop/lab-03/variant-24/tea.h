#ifndef TEA_H
#define TEA_H

#include <iostream>
#include <iomanip>
using namespace std;

class Tea {
public:
    char type[40];
    char package[40];
    char brand[40];
    double price;
    int quantity;

    double total() { return price * quantity; }

    void show() {
        cout << type << " | " << package << " | " << brand << " | ";
        cout << fixed << setprecision(2) << price << " | ";
        cout << quantity << " | " << total() << endl;
    }
};

#endif
