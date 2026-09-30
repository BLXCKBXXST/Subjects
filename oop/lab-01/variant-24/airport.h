#ifndef AIRPORT_H
#define AIRPORT_H

#include <iostream>
#include <string>
using namespace std;

class Airport {
private:
    string name;
    string city;
    string status;
    int runways;

public:
    Airport(string n, string c, string s, int r) {
        name = n;
        city = c;
        status = s;
        runways = r;
    }

    string getName() const { return name; }
    string getCity() const { return city; }
    string getStatus() const { return status; }
    int getRunways() const { return runways; }

    void setName(string n) { name = n; }
    void setCity(string c) { city = c; }
    void setStatus(string s) { status = s; }
    void setRunways(int r) { runways = r; }

    void show() const {
        cout << "Название: " << name << endl;
        cout << "Город: " << city << endl;
        cout << "Статус: " << status << endl;
        cout << "Количество полос: " << runways << endl;
    }
};

#endif
