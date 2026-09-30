#include <iostream>
#include <string>
using namespace std;

class Cafe {
private:
    string name;
    string phone;
    string address;
    string hours;

public:
    Cafe() {
        name = "Не указано";
        phone = "Не указано";
        address = "Не указано";
        hours = "Не указано";
    }

    Cafe(string n, string p, string a, string h) {
        name = n;
        phone = p;
        address = a;
        hours = h;
    }

    void setName(string n) { name = n; }
    void setPhone(string p) { phone = p; }
    void setAddress(string a) { address = a; }
    void setHours(string h) { hours = h; }

    string getName() { return name; }
    string getPhone() { return phone; }
    string getAddress() { return address; }
    string getHours() { return hours; }

    virtual void show() {
        cout << "Название: " << name << endl;
        cout << "Телефон: " << phone << endl;
        cout << "Адрес: " << address << endl;
        cout << "Время работы: " << hours << endl;
    }
};

class PrivateCafe : public Cafe {
private:
    string owner;

public:
    PrivateCafe() : Cafe() {
        owner = "Не указано";
    }

    PrivateCafe(string n, string p, string a, string h, string o)
        : Cafe(n, p, a, h) {
        owner = o;
    }

    void setOwner(string o) { owner = o; }
    string getOwner() { return owner; }

    void show() override {
        Cafe::show();
        cout << "Владелец: " << owner << endl;
    }
};

int main() {
    Cafe first;
    Cafe second("Зерно", "111-22-33", "ул. Ленина, 10", "08:00-20:00");

    cout << "Кофейня без параметров:" << endl;
    first.show();
    cout << "\nКофейня с параметрами:" << endl;
    second.show();

    first.setName("Утро");
    first.setPhone("222-33-44");
    first.setAddress("ул. Мира, 5");
    first.setHours("09:00-21:00");

    cout << "\nИзмененные поля через методы get:" << endl;
    cout << first.getName() << endl;
    cout << first.getPhone() << endl;
    cout << first.getAddress() << endl;
    cout << first.getHours() << endl;

    PrivateCafe third;
    PrivateCafe fourth("Аромат", "333-44-55", "ул. Садовая, 3",
                       "10:00-22:00", "Иванов Иван Иванович");

    cout << "\nЧастная кофейня без параметров:" << endl;
    third.show();
    cout << "\nЧастная кофейня с параметрами:" << endl;
    fourth.show();

    fourth.setName("Новый аромат");
    fourth.setOwner("Петров Петр Петрович");
    cout << "\nНовый владелец: " << fourth.getOwner() << endl;

    cout << "\nВывод через указатель на базовый класс:" << endl;
    Cafe* cafe = &fourth;
    cafe->show();

    return 0;
}
