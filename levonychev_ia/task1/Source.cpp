#include <iostream>
#include <ciso646>

class Trational
{
    int numerator;
    int denominator;

    int gcd(int a, int b)
    {
        int tmp;
        while (b != 0)
        {
            tmp = b;
            a = a % b;
            b = a;
            a = tmp;
        }
        return (a >= 0) ? a : -a;
    }
public:
    Trational(int a, int b)
    {
        if (b == 0)
        {
            throw std::invalid_argument("Error! The denominator ñan't be zero.");
        }
        if (b < 0)
        {
            a = -a;
            b = -b;
        }
        numerator = a / gcd(a, b);
        denominator = b / gcd(a, b);
    }
    Trational()
    {
        numerator = 0;
        denominator = 1;

    }

    void Print()
    {
        if (numerator == 0)
            std::cout << numerator;
        else
            std::cout << numerator << "/" << denominator;
    }
    Trational operator+(Trational c)
    {
        return Trational((numerator * c.denominator) + (c.numerator * denominator), denominator * c.denominator);

    }
    Trational operator-(Trational c)
    {
        return Trational((numerator * c.denominator) - (c.numerator * denominator), denominator * c.denominator);

    }
    Trational operator*(Trational c)
    {
        return Trational(numerator * c.numerator, denominator * c.denominator);
    }
    Trational operator/(Trational c)
    {
        if (c.numerator == 0)
        {
            throw std::invalid_argument("Error! Division by zero.");
        }
        return Trational(numerator * c.denominator, denominator * c.numerator);
    }
};

int main()
{
    int a, b;
    int c, d;
    std::cout << "Input the numerator of the first fraction: ";
    std::cin >> a;
    std::cout << "Input the demominator of the first fraction: ";
    std::cin >> b;
    std::cout << "Input the numerator of the second fraction: ";
    std::cin >> c;
    std::cout << "Input the demominator of the second fraction: ";
    std::cin >> d;
    Trational r1(a, b);
    Trational r2(c, d);
    Trational r3;
    Trational r4;
    Trational r5;
    Trational r6;
    r3 = r1 + r2;
    r4 = r1 - r2;
    r5 = r1 * r2;
    r6 = r1 / r2;

    r1.Print();
    std::cout << " + ";
    r2.Print();
    std::cout << " = ";
    r3.Print();
    std::cout << std::endl;

    r1.Print();
    std::cout << " - ";
    r2.Print();
    std::cout << " = ";
    r4.Print();
    std::cout << std::endl;

    r1.Print();
    std::cout << " * ";
    r2.Print();
    std::cout << " = ";
    r5.Print();
    std::cout << std::endl;

    r1.Print();
    std::cout << " / ";
    r2.Print();
    std::cout << " = ";
    r6.Print();
    std::cout << std::endl;
    system("pause");
    return 0;
}


