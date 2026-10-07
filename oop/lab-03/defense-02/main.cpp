#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Cinema {
private:
    string name;
    string phone;
    string address;
    string hours;
    int hallCount;

public:
    Cinema() {
        name = "Не указано";
        phone = "Не указано";
        address = "Не указано";
        hours = "Не указано";
        hallCount = 0;
    }

    Cinema(string n, string p, string a, string h, int count) {
        name = n;
        phone = p;
        address = a;
        hours = h;
        hallCount = count;
    }

    void setName(string n) { name = n; }
    void setPhone(string p) { phone = p; }
    void setAddress(string a) { address = a; }
    void setHours(string h) { hours = h; }
    void setHallCount(int count) { hallCount = count; }

    string getName() { return name; }
    string getPhone() { return phone; }
    string getAddress() { return address; }
    string getHours() { return hours; }
    int getHallCount() { return hallCount; }

    virtual void show() {
        cout << "Название: " << name << endl;
        cout << "Телефон: " << phone << endl;
        cout << "Адрес: " << address << endl;
        cout << "Время работы: " << hours << endl;
        cout << "Количество кинозалов: " << hallCount << endl;
    }
};

class CinemaHall : public Cinema {
private:
    int capacity;

public:
    CinemaHall() : Cinema() {
        capacity = 0;
    }

    CinemaHall(string n, string p, string a, string h, int count, int c)
        : Cinema(n, p, a, h, count) {
        capacity = c;
    }

    void setCapacity(int c) { capacity = c; }
    int getCapacity() { return capacity; }

    void show() override {
        Cinema::show();
        cout << "Вместимость: " << capacity << endl;
    }
};

int main() {
    int n;
    cout << "Введите N: ";
    cin >> n;

    ifstream file("zal.txt");

    if (!file) {
        cout << "Не удалось открыть zal.txt" << endl;
        return 1;
    }

    CinemaHall* halls = new CinemaHall[n];

    string name;
    string phone;
    string address;
    string hours;
    int hallCount;
    int capacity;

    for (int i = 0; i < n; i++) {
        getline(file, name);
        getline(file, phone);
        getline(file, address);
        getline(file, hours);
        file >> hallCount;
        file >> capacity;
        file.ignore(1000, '\n');

        halls[i].setName(name);
        halls[i].setPhone(phone);
        halls[i].setAddress(address);
        halls[i].setHours(hours);
        halls[i].setHallCount(hallCount);
        halls[i].setCapacity(capacity);
    }

    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << "Объект " << i + 1 << endl;
        halls[i].show();
        cout << endl;
    }

    delete[] halls;
    return 0;
}
