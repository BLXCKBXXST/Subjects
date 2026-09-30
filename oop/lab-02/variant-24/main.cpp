#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class Triangle {
protected:
    double a;

public:
    Triangle(double side = 1) { a = side; }
    virtual ~Triangle() {}

    void setSide(double side) { a = side; }
    double height() { return a * sqrt(3.0) / 2; }
    double bisector() { return height(); }
    double perimeter() { return 3 * a; }
    virtual double area() { return a * a * sqrt(3.0) / 4; }

    virtual void show() {
        cout << "Сторона: " << a << endl;
        cout << "Высота: " << height() << endl;
        cout << "Биссектриса: " << bisector() << endl;
        cout << "Периметр: " << perimeter() << endl;
        cout << "Площадь: " << area() << endl;
    }
};

class Tetrahedron : public Triangle {
private:
    double h;

public:
    Tetrahedron(double side = 1) : Triangle(side) {
        h = side * sqrt(6.0) / 3;
    }

    void setSide(double side) {
        Triangle::setSide(side);
        h = side * sqrt(6.0) / 3;
    }

    double volume() { return Triangle::area() * h / 3; }
    double area() override { return 4 * Triangle::area(); }

    void show() override {
        cout << "Ребро: " << a << endl;
        cout << "Высота тетраэдра: " << h << endl;
        cout << "Площадь поверхности: " << area() << endl;
        cout << "Объем: " << volume() << endl;
    }
};

int main() {
    int n, m;
    cout << "Количество треугольников и тетраэдров: ";
    if (!(cin >> n >> m) || n < 0 || m < 0 || n > 10000 || m > 10000) {
        cout << "Количество должно быть от 0 до 10000." << endl;
        return 1;
    }

    Triangle* triangles = new Triangle[n];
    Tetrahedron* pyramids = new Tetrahedron[m];
    double side;
    double sum = 0;

    for (int i = 0; i < n; i++) {
        cout << "Сторона треугольника " << i + 1 << ": ";
        if (!(cin >> side) || !isfinite(side) || side <= 0 || side > 1000000) {
            cout << "Сторона должна быть больше 0 и не больше 1000000." << endl;
            delete[] triangles;
            delete[] pyramids;
            return 1;
        }
        triangles[i].setSide(side);
        sum += triangles[i].area();
    }

    for (int i = 0; i < m; i++) {
        cout << "Ребро тетраэдра " << i + 1 << ": ";
        if (!(cin >> side) || !isfinite(side) || side <= 0 || side > 1000000) {
            cout << "Ребро должно быть больше 0 и не больше 1000000." << endl;
            delete[] triangles;
            delete[] pyramids;
            return 1;
        }
        pyramids[i].setSide(side);
    }

    cout << fixed << setprecision(3);
    for (int i = 0; i < n; i++) {
        cout << "\nТреугольник " << i + 1 << endl;
        triangles[i].show();
    }
    for (int i = 0; i < m; i++) {
        cout << "\nТетраэдр " << i + 1 << endl;
        Triangle* figure = &pyramids[i];
        figure->show();
    }

    if (n > 0)
        cout << "\nСредняя площадь треугольников: " << sum / n << endl;
    else
        cout << "\nТреугольников нет." << endl;

    if (m > 0) {
        int smallest = 0;
        for (int i = 1; i < m; i++) {
            if (pyramids[i].volume() < pyramids[smallest].volume())
                smallest = i;
        }
        cout << "Тетраэдр с наименьшим объемом: " << smallest + 1 << endl;
        pyramids[smallest].show();
    } else {
        cout << "Тетраэдров нет." << endl;
    }

    delete[] triangles;
    delete[] pyramids;
    return 0;
}
