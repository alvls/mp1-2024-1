#include <iostream>
#include <cmath>

class TaylorSeries {
private:
    std::string currentFunction;
    int numTerms;

public:
    TaylorSeries() : currentFunction(), numTerms() {}

    void setCurrentFunction(std::string func) {
        currentFunction = func;
    }

    std::string getCurrentFunction() {
        return currentFunction;
    }

    void setNumTerms(int n) {
        numTerms = n;
    }

    int getNumTerms() {
        return numTerms;
    }

    double computeTermValue(double x, int n) {
        if (currentFunction == "sin(x)") {
            return pow(-1, n) * pow(x, 2 * n + 1) / factorial(2 * n + 1);
        }
        else if (currentFunction == "cos(x)") {
            return pow(-1, n) * pow(x, 2 * n) / factorial(2 * n);
        }
        else {
            return pow(x, n) / factorial(n);
        }
    }

    double computeTaylorSeriesValue(double x) {
        double sum = 0.0;
        for (int i = 0; i < numTerms; ++i) {
            sum += computeTermValue(x, i);
        }
        return sum;
    }

    double computeDeviation(double x) {
        double referenceValue = 0.0;
        if (currentFunction == "sin(x)") {
            referenceValue = sin(x);
        }
        else if (currentFunction == "cos(x)") {
            referenceValue = cos(x);
        }
        else if (currentFunction == "exp(x)") {
            referenceValue = exp(x);
        }
        return abs(referenceValue - computeTaylorSeriesValue(x));
    }

private:
    int factorial(int n) {
        if (n == 0 || n == 1) {
            return 1;
        }
        return n * factorial(n - 1);
    }
};

int main() {
    TaylorSeries taylorSeries;
    setlocale(LC_ALL, "Rus");
    std::cout << "Выберите функцию для вычисления ряда Тейлора:" << std::endl;
    std::cout << "1. sin(x)" << std::endl;
    std::cout << "2. cos(x)" << std::endl;
    std::cout << "3. exp(x)" << std::endl;
    std::cout << "4. Выйти из программы" << std::endl;
    std::cout << ">> ";

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
        taylorSeries.setCurrentFunction("sin(x)");
        break;
    case 2:
        taylorSeries.setCurrentFunction("cos(x)");
        break;
    case 3:
        taylorSeries.setCurrentFunction("exp(x)");
        break;
    case 4:
        return 0;
    default:
        std::cout << "Некорректный выбор." << std::endl;
        return 0;
    }

    int numTerms;
    std::cout << "Введите количество членов ряда Тейлора: ";
    std::cin >> numTerms;
    taylorSeries.setNumTerms(numTerms);

    std::cout << "Выбранная функция: " << taylorSeries.getCurrentFunction() << std::endl;
    std::cout << "количество членов ряда Тейлора: " << taylorSeries.getNumTerms() << std::endl;

    double x;
    std::cout << "Введите значение x: ";
    std::cin >> x;

    double referenceValue;
    if (taylorSeries.getCurrentFunction() == "sin(x)") {
        referenceValue = sin(x);
    }
    else if (taylorSeries.getCurrentFunction() == "cos(x)") {
        referenceValue = cos(x);
    }
    else {
        referenceValue = exp(x);
    }

    double taylorSeriesValue = taylorSeries.computeTaylorSeriesValue(x);
    double deviation = taylorSeries.computeDeviation(x);
    std::cout << "Точное значение функции в точке x: " << referenceValue << std::endl;
    std::cout << "Значение ряда Тейлора в точке x: " << taylorSeriesValue << std::endl;
    std::cout << "Отклонение от точного значения: " << deviation << std::endl;

    system("pause");
}
