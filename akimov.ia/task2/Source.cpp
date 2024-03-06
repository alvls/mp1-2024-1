#include <iostream>
#include <cmath>
#include <clocale>

using namespace std;

class Polynomial
{
    unsigned int degree;
    double *coefficients;
public:
    Polynomial(int deg)
    {
        degree = deg;
        coefficients = new double[degree + 1];
    }

    ~Polynomial() { delete[] coefficients; }

    void setDegree(unsigned int deg)
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

    void derivative()
    {
        degree--;
        for (int i = 0; i <= degree; i++)
            coefficients[i] = (i + 1) * coefficients[i + 1];
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
        setlocale(LC_ALL, "rus");
        unsigned int degree;
        int flag;
        do
        {
            flag = 0;
            cout << "������� ������� �������� �� 0 �� 12: ";
            cin >> degree;
            if (degree > 12)
            {
                flag = 1;
                system("cls");
                cout << "������� ������� ��������!" << endl;
            }
        } while (flag);
        Polynomial p(degree);
        double coefficients[13];
        for (int i = 0; i <= degree; i++)
        {
            cout << "������� ����������� �������� ��� x^" << i << ": ";
            cin >> coefficients[i];
        }
        p.setCoefficients(coefficients);
        cout << "������� ������� " << degree << ": ";
        p.print();
        double x;
        cout << "������� �������� x: ";
        cin >> x;
        cout << "�������� �������� � ����� x = " << x << ": " << p.evaluate(x) << endl;
        if (degree == 0)
            cout << "����������� ��������: 0";
        else
        {
            p.derivative();
            cout << "����������� ��������: ";
            p.print();
        }
        cout << endl << "����� ������������� ��������� ������� 1: ";
        cin >> r;
    } while (r == 1);
    system("pause");
    return 0;
}