#include <iostream>
#include <cstring>
#include <math.h>
using namespace std;

// ======================= ПУНКТ A =======================
// Абстрактный тип данных Одномерный массив" для int
// Перегрузка: [], ==, !=

class IntArray {
private:
    int* data;
    int size;

public:
    IntArray() : data(nullptr), size(0) {}

    IntArray(int sz) : size(sz) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
    }

    IntArray(IntArray& other) : size(other.size) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    IntArray(int* other, int size) : size(size) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other[i];
        }
    }

    ~IntArray() {
        delete[] data;
    }


    // [] доступ по индексу
    int& operator[](int index) {
        return data[index];
    }

    // == проверка на равенство
    bool operator==(const IntArray& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    bool operator!=(const IntArray& other) const {
        return !(*this == other);
    }

    int getSize() const { return size; }
};


// ======================= ПУНКТ B =======================
// Иерархия классов: базовый Vector2D, производный Vector3D
// Статический член: подсчет максимальной длины среди всех векторов
// Виртуальные функции: length() и print() (минимум 2)

class Vector2D {
private:
    double x, y;
    static double maxLength;

protected:
    static void updateMax(double len) {
        if (len > maxLength) maxLength = len;
    }

public:
    Vector2D(double x = 0, double y = 0) : x(x), y(y) {
        updateMax(length());
    }

    // вычисление длины
    virtual double length() {
        double len = sqrt(x*x + y*y);
        return len;
    }

    // печать информации
    virtual void print() {
        cout << "2D Vector: (" << x << ", " << y << "), len = " << this->length() << endl;
    }


    virtual ~Vector2D() {}


    static double getMaxLength() { return maxLength; }
    static void resetMaxLength() { maxLength = 0; }

    double getX() const { return x; }
    double getY() const { return y; }


    bool operator==(const Vector2D& other) const {
        return (x == other.x) && (y == other.y);
    }
    bool operator!=(const Vector2D& other) const {
        return !(*this == other);
    }
};

double Vector2D::maxLength = 0.0;

class Vector3D : public Vector2D {
private:
    double z;

public:
    Vector3D(double x = 0, double y = 0, double z = 0) : Vector2D(x, y), z(z) {
        updateMax(length());
    }

    double length() {
        double len = sqrt(getX()*getX() + getY()*getY() + z*z);
        return len;
    }


    void print() {
        cout << "3D Vector: (" << getX() << ", " << getY() << ", " << z << "), len = " << length() << endl;
    }

    double getZ() const { return z; }

    bool operator==(const Vector3D& other) {
        return (getX() == other.getX()) && (getY() == other.getY()) && (z == other.z);
    }
    bool operator!=(const Vector3D& other) {
        return !(*this == other);
    }
};


// ======================= ПУНКТ C =======================
// Шаблонный класс одномерного массива

template <typename T>
class Array {
private:
    T* data;
    int size;

public:
    Array() : data(nullptr), size(0) {}

    Array(int sz) : size(sz) {
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = T();
        }
    }

    Array(const Array& other) : size(other.size) {
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    Array(T* other, int sz) : size(sz) {
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = other[i];
        }
    }

    ~Array() {
        delete[] data;
    }

    // [] доступ по индексу
    T& operator[](int index) {
        return data[index];
    }

    // ==
    bool operator==(const Array& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    // !=
    bool operator!=(const Array& other) const {
        return !(*this == other);
    }

    int getSize() const { return size; }


};



int main() {
    // === пункт а ===
    cout << "=== a ===" << endl;

    IntArray a1(3);
    a1[0] = 10; a1[1] = 20; a1[2] = 30;

    IntArray a2(a1);

    cout << "a1 == a2? " << (a1 == a2) << endl;  // 1 (true)

    a2[0] = 99;
    cout << "a1 != a2? " << (a1 != a2) << endl;  // 1 (true)


    // === пункт b ===
    cout << "\n=== b ===" << endl;


    Vector2D v2(3, 4);
    Vector3D v3(4, 4, 4);
    v2.print();
    v3.print();
    cout << "Max length: " << Vector2D::getMaxLength() << endl;

    Vector2D* p = new Vector3D(1, 1, 1);
    p->print();
    delete p;


    // === пункт c ===
    cout << "\n=== c ===" << endl;

    // С int
    Array<int> intArr(3);
    intArr[0] = 5; intArr[1] = 10; intArr[2] = 15;
    cout << "intArr: ";
    for (int i = 0; i < intArr.getSize(); i++)
        cout << intArr[i] << " ";
    cout << endl;

    // С Vector2D
    Array<Vector2D> vecArr(2);
    vecArr[0] = Vector2D(1, 2);
    vecArr[1] = Vector2D(3, 4);
    cout << "vecArr:" << endl;
    for (int i = 0; i < vecArr.getSize(); i++)
        vecArr[i].print();

    // С Vector3D
    Array<Vector3D> vec3Arr(2);
    vec3Arr[0] = Vector3D(1, 1, 1);
    vec3Arr[1] = Vector3D(2, 2, 2);
    cout << "vec3Arr:" << endl;
    for (int i = 0; i < vec3Arr.getSize(); i++)
        vec3Arr[i].print();

    // Сравнение массивов
    Array<int> intArr2(intArr);
    cout << "intArr == intArr2 ? " << (intArr == intArr2) << endl;

    return 0;
}