#include <iostream>

class LongNumber {
private:
    int lowerPart;
    int upperPart;

public:
    LongNumber() : lowerPart(0), upperPart(0) {}

    LongNumber(long long value) {
        lowerPart = static_cast<int>(value);
        upperPart = static_cast<int>(value >> 32);
    }

    LongNumber operator+(const LongNumber& other) const {
        LongNumber result;
        result.upperPart = upperPart + other.upperPart;
        result.lowerPart = lowerPart + other.lowerPart;

        if (result.lowerPart < lowerPart || (result.upperPart == INT_MAX && other.upperPart > 0)) {
            std::cerr << "Overflow" << std::endl;
        }

        return result;
    }

    LongNumber operator-(const LongNumber& other) const {
        LongNumber result;
        result.upperPart = upperPart - other.upperPart;
        result.lowerPart = lowerPart - other.lowerPart;

        if (result.lowerPart > lowerPart || (result.upperPart == INT_MIN && other.upperPart > 0)) {
            std::cerr << "Underflow" << std::endl;
        }

        return result;
    }

    LongNumber operator*(const LongNumber& other) const {
        LongNumber result;
        long long lowerResult = static_cast<long long>(lowerPart) * other.lowerPart;
        result.upperPart = static_cast<int>((static_cast<long long>(upperPart) * other.lowerPart) + (lowerResult >> 32));
        result.lowerPart = static_cast<int>(lowerResult);

        if (result.upperPart > 0) {
            std::cerr << "Overflow" << std::endl;
        }

        return result;
    }

    LongNumber operator/(const LongNumber& other) const {
        LongNumber result;

        if (other.upperPart == 0 && other.lowerPart == 0) {
            std::cerr << "Division by zero" << std::endl;
            return result;
        }

        long long dividend = (static_cast<long long>(upperPart) << 32) | lowerPart;
        long long divisor = (static_cast<long long>(other.upperPart) << 32) | other.lowerPart;

        result.upperPart = static_cast<int>(dividend / divisor);
        result.lowerPart = static_cast<int>(dividend % divisor);

        return result;
    }

    LongNumber operator%(const LongNumber& other) const {
        LongNumber result;

        if (other.upperPart == 0 && other.lowerPart == 0) {
            std::cerr << "Division by zero" << std::endl;
            return result;
        }

        long long dividend = (static_cast<long long>(upperPart) << 32) | lowerPart;
        long long divisor = (static_cast<long long>(other.upperPart) << 32) | other.lowerPart;

        result.lowerPart = static_cast<int>(dividend % divisor);

        return result;
    }

    void display() const {
        std::cout << static_cast<long long>(upperPart) << " " << static_cast<unsigned int>(lowerPart) << std::endl;
    }
};

int main() {
    int r;
    setlocale(LC_ALL, "Russian");
    do {
        system("cls");

        long long num1, num2;
        std::cout << "Введите первое число: ";
        std::cin >> num1;

        std::cout << "Введите второе число: ";
        std::cin >> num2;

        LongNumber longNum1(num1);
        LongNumber longNum2(num2);

        LongNumber sum = longNum1 + longNum2;
        LongNumber diff = longNum1 - longNum2;
        LongNumber prod = longNum1 * longNum2;
        LongNumber quotient = longNum1 / longNum2;
        LongNumber remainder = longNum1 % longNum2;

        std::cout << "Сумма: ";
        sum.display();

        std::cout << "Разность: ";
        diff.display();

        std::cout << "Произведение: ";
        prod.display();

        if (num2 == 0)
            std::cout << "Частное: Ошибка: деление на ноль!" << std::endl;
        else {
            std::cout << "Частное: ";
            quotient.display();
            std::cout << "Остаток: ";
            remainder.display();
        }

        std::cout << "Желаете выполнить еще одну операцию? Введите 1: ";
        std::cin >> r;

    } while (r == 1);

    system("pause");
    return 0;
}