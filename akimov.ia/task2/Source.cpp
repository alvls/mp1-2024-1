#include <iostream>
#include <cmath>
#include <clocale>

using namespace std;

class Polynomial
{
    int degree;
    double *coefficients;
public:
    Polynomial()
    {
        degree = 0;
        coefficients = new double[13];
        for (int i = 0; i < 13; i++)
            coefficients[i] = 0.0;
    }

    ~Polynomial() {}

    void setDegree(int deg)
    {
        degree = deg;
    }

    void setCoefficients(double coeffs[])
    {
        for (int i = 0; i <= degree; i++)
            coefficients[i] = coeffs[i];
    }

    int getDegree()
    {
        return degree;
    }

    double getCoefficient(int i)
    {
        return coefficients[i];
    }

    double evaluate(double x)
    {
        double result = 0.0;
        for (int i = 0; i <= degree; i++)
            result += coefficients[i] * pow(x, i);
        return result;
    }

    Polynomial derivative()
    {
        Polynomial derivativePolynomial;
        derivativePolynomial.degree = degree - 1;
        for (int i = 1; i <= degree; i++)
            derivativePolynomial.coefficients[i - 1] = i * coefficients[i];
        return derivativePolynomial;
    }

    void print()
    {
        for (int i = degree; i >= 0; i--)
        {
            if (i < degree)
                cout << " + ";
            cout << coefficients[i] << "x^" << i;
        }
        cout << endl;
    }
};

int main()
{
    int r = 0;
    do
    {
        system("cls");
        Polynomial p;
        setlocale(LC_ALL, "rus");
        int degree, flag;
        do
        {
            flag = 0;
            cout << "Введите степень полинома от 0 до 12: ";
            cin >> degree;
            if (degree < 0 || degree > 12)
            {
                flag = 1;
                system("cls");
                cout << "Неверня степень полинома!" << endl;
            }
        } while (flag);
        p.setDegree(degree);
        double coefficients[13];
        for (int i = 0; i <= degree; i++)
        {
            cout << "Введите коэффициент полинома при x^" << i << ": ";
            cin >> coefficients[i];
        }
        p.setCoefficients(coefficients);
        cout << "Полином степени " << degree << ": ";
        p.print();
        double x;
        cout << "Введите значение x: ";
        cin >> x;
        cout << "Значение полинома в точке x = " << x << ": " << p.evaluate(x) << endl;
        Polynomial derivative = p.derivative();
        cout << "Производная полинома: ";
        derivative.print();
        cout << endl << "Чтобы перезапустить программу введите 1: ";
        cin >> r;
    } while (r == 1);
    system("pause");
    return 0;
}