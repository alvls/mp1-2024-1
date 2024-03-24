#include <iostream>
#include <cmath>
#include <clocale>
#include "Func.h"

using namespace std;

class IntegralCalculator
{
private:
    double (*func)(double);
    double a, b;
    int n;
    string method;
public:
    IntegralCalculator()
    {
        func = nullptr;
        a = 0;
        b = 0;
        n = 0;
        method = "";
    }

    void setFunction(double (*f)(double))
    {
        func = f;
    }

    void setIntegrationLimits(double lower, double upper)
    {
        a = lower;
        b = upper;
    }

    double getIntegrationLimitsUpper()
    {
        return b;
    }

    double getIntegrationLimitsLower()
    {
        return a;
    }

    void setNumberOfSegments(int segments)
    {
        n = segments;
    }

    void setMethod(string m)
    {
        method = m;
    }

    double calculateIntegral()
    {
        if (method == "left")
        {
            return leftRectangleMethod();
        }
        else if (method == "right")
        {
            return rightRectangleMethod();
        }
        else if (method == "middle")
        {
            return middleRectangleMethod();
        }
    }

    void printResult(double result)
    {
        cout << "Результат: " << result << endl;
    }

private:
    double leftRectangleMethod()
    {
        double h = (b - a) / n;
        double sum = 0;
        for (int i = 0; i < n; i++)
        {
            double x = a + i * h;
            sum += func(x);
        }
        return h * sum;
    }

    double rightRectangleMethod()
    {
        double h = (b - a) / n;
        double sum = 0;
        for (int i = 1; i <= n; i++)
        {
            double x = a + i * h;
            sum += func(x);
        }
        return h * sum;
    }

    double middleRectangleMethod()
    {
        double h = (b - a) / n;
        double sum = 0;
        for (int i = 0; i < n; i++)
        {
            double x = a + (i + 0.5) * h;
            sum += func(x);
        }
        return h * sum;
    }
};

int main()
{
    int r = 0;
    do
    {
        system("cls");
        setlocale(LC_ALL, "rus");
        IntegralCalculator calculator;
        unsigned int func;
        int flag;
        do
        {
            cout << "Функции:" << endl << "1.sin(x)" << endl << "2.cos(x)" << endl << "3.exp(x)" << endl << "Введите номер выбранной функции: ";
            cin >> func;
            flag = 0;
            if (func == 0 || func > 3)
            {
                system("cls");
                cout << "Указанной функции не существует!" << endl;
                flag = 1;
            }
        } while (flag);
        switch (func)
        {
        case 1:
            calculator.setFunction(myFunctionSin);
        case 2:
            calculator.setFunction(myFunctionCos);
        case 3:
            calculator.setFunction(myFunctionExp);
        }
        double lower, upper;
        cout << "Задайте нижний предел интегрирования: ";
        cin >> lower;
        cout << "Задайте верхний предел интегрирования: ";
        cin >> upper;
        calculator.setIntegrationLimits(lower, upper);
        int n;
        cout << "Задайте число отрезков метода прямоугольника: ";
        cin >> n;
        calculator.setNumberOfSegments(n);
        int method;
        cout << "Методы:" << endl << "1.Левых прямоугольников" << endl << "2.Правых прямоугольников" << endl << "3.Средних прямоугольников" << endl << "Введите номер выбранного метода: ";
        cin >> method;
        switch (method)
        {
        case 1:
            calculator.setMethod("left");
        case 2:
            calculator.setMethod("right");
        case 3:
            calculator.setMethod("middle");
        }
        double result = calculator.calculateIntegral();
        calculator.printResult(result);
        cout << endl << "Чтобы перезапустить программу введите 1: ";
        cin >> r;
    } while (r == 1);
    system("pause");
    return 0;
}