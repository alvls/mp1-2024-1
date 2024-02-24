#include<iostream>
using namespace std;

class LenConv {
private:
    double len;
    const int unitCount = 6;
    const double coeffs[6] = { 1.0, 0.001, 0.000621371, 3.28084, 1/0.0000000001, 1/9.46E15 };

public:
    enum Units {
        Meters,
        Kilometers,
        Miles,
        Feet,
        Angstrom,
        Lightyear
    };

    Units unitFromInt(int n) {
        if (n < unitCount) return static_cast<Units>(n);
        cout << "! Неизвестная мера. Интерпретировано как метры." << endl;
        return Meters;
    }

    LenConv(double lenMeters = 0.) { len = lenMeters; } //Конструктор по умолчанию совмещён здесь. Конструктор копирования от компилятора подойдёт, так как указатели не используются

    void setLenInMeters(double ulen) { len = ulen; }

    void setLenInUnit(double ulen, Units fromUnit){ len = ulen / coeffs[fromUnit]; }

    double getLenInMeters() { return len; }

    double getLenInUnit(Units unit) { return len * coeffs[unit]; }

    double convertLenFromTo(double ulen, Units fromUnit, Units toUnit) {
        len = ulen / coeffs[fromUnit];
        return  len * coeffs[toUnit];
    }

    void printLenInMeters() { cout<< len; }

    void printLenInUnit(Units unit) { cout<< len * coeffs[unit]; }

};

void main() {
    setlocale(LC_ALL, "RU");
    LenConv c(42);
    c.printLenInMeters();
    cout << " <= Значение в метрах задано в конструкторе" << endl;
    cout << "Зададим длину 10 метров, выведем в метрах и футах" << endl;
    c.setLenInMeters(10);
    cout << c.getLenInMeters() << " " << c.getLenInUnit(c.Feet) << endl;

    cout << "Зададим длину 2 фута, выведем в метрах и футах" << endl;
    c.setLenInUnit(2, c.Feet);
    cout << c.getLenInMeters() <<" " << c.getLenInUnit(c.Feet)<<endl;

    cout << "Зададим длину 5 миль, выведем резьтат конвертации в футы" << endl;
    cout << c.convertLenFromTo(5, c.Miles,c.Feet) << endl;

    cout << "Выведем методами класса сохранённое значение в милях, в футах и в метрах" << endl;
    c.printLenInUnit(c.Miles);
    cout << " ";
    c.printLenInUnit(c.Feet);
    cout << " ";
    c.printLenInMeters();

    //LenConv b(c); //копирование по умолчанию работает правильно
    //b.printLenInMeters();

    cout<< endl<<endl<<"Введите длину в метрах"<<endl;

    double m = 0.;
    cin >> m;
    c.setLenInMeters(m);
    cout << endl << "Введите индекс единицы измерения, в которой нужно вывести длину" << endl;
    cout << "0 Meters (метры)\n1 Kilometers (километры)\n2 Miles (мили)\n3 Feet (футы)\n4 Angstrom (ангстремы)\n5 Lightyear (световые годы)\n";
    int u = 0;
    cin >> u;
    cout << endl << "Ответ:" << endl;
    c.printLenInUnit(c.unitFromInt(u));

    cout << endl;
    system("pause");
}

