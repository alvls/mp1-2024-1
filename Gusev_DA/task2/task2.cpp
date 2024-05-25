#include <iostream>
#include <cstring> // Для использования функций strncpy_s и strcpy_s
#include <algorithm> // Для использования функции reverse

#define _CRT_SECURE_NO_WARNINGS // Для отключения предупреждений о небезопасности

using namespace std;

#ifdef _WIN32
#include <windows.h>
void clearConsole() {
    system("cls");
}
#else
void clearConsole() {
    system("clear");
}
#endif

class MyString {
private:
    char str[41]; // Массив символов для хранения строки (плюс один символ для '\0')

public:
    MyString() {
        str[0] = '\0'; // Инициализируем строку пустым символом
    }

    void setString(const char* s) {
        if (strlen(s) <= 40) { // Проверяем длину строки
            strncpy_s(str, sizeof(str), s, sizeof(str) - 1); // Копируем строку в массив str
        }
        else {
            cout << "The length of the string exceeds 40 characters. Shorten the line.\n";
        }
    }

    void inputString() {
        cout << "Enter a string (no more than 40 characters): ";
        cin.ignore();
        cin.getline(str, sizeof(str)); // Считываем строку с учетом длины
        if (strlen(str) == 40) { // Добавляем проверку на максимальную длину
            cout << "The length of the string reaches 40 characters.\n";
        }
        else if (strlen(str) > 40) {
            cout << "The length of the string exceeds 40 characters. Shorten the line.\n";
            str[0] = '\0'; // Обнуляем строку
        }
    }

    int length() const {
        return strlen(str);
    }

    char getCharAt(int index) const {
        if (index >= 0 && index < strlen(str)) {
            return str[index];
        }
        else {
            cout << "The index goes beyond the line boundaries.\n";
            return '\0';
        }
    }

    void setCharAt(int index, char c) {
        if (index >= 0 && index < strlen(str)) {
            str[index] = c;
        }
        else {
            cout << "The index goes beyond the line boundaries.\n";
        }
    }

    string substring(int start, int end) const {
        if (start >= 0 && start < end && end <= strlen(str)) {
            char substr[41]; // Временный массив для подстроки
            strncpy_s(substr, sizeof(substr), str + start, end - start); // Копируем подстроку во временный массив
            substr[end - start] = '\0'; // Добавляем завершающий символ
            return substr;
        }
        else {
            cout << "Going beyond the line boundaries when selecting a substring.\n";
            return "";
        }
    }

    bool isPalindrome() const {
        int len = strlen(str);
        for (int i = 0; i < len / 2; ++i) {
            if (str[i] != str[len - 1 - i]) {
                return false;
            }
        }
        return true;
    }

    int countUniqueLatinChars() const {
        bool latinChars[26] = { false }; // Массив флагов для латинских символов
        int count = 0;
        for (int i = 0; i < strlen(str); ++i) {
            char c = tolower(str[i]); // Преобразуем символ в нижний регистр
            if (c >= 'a' && c <= 'z') {
                if (!latinChars[c - 'a']) { // Если символ еще не встречался
                    latinChars[c - 'a'] = true; // Помечаем его как встреченный
                    ++count; // Увеличиваем счетчик уникальных символов
                }
            }
        }
        return count;
    }

    void print() const {
        cout << str << endl;
    }

    ~MyString() {}
};

unsigned long long factorial(unsigned long long n) {
    if (n == 0) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
}

int main() {
    MyString myString;
    int choice;

    do {
        cout << "Entered line: ";
        myString.print();

        cout << "\nChoose an option:\n";
        cout << "1. Input string\n";
        cout << "2. Length of the string\n";
        cout << "3. Character by the index\n";
        cout << "4. Replacing a character by the index\n";
        cout << "5. Substring from a string\n";
        cout << "6. Check if the string is a palindrome\n";
        cout << "7. Number of different characters in a string\n";
        cout << "8. Factorial calculation\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
        case 1:
            myString.inputString();
            clearConsole(); // Используем функцию для очистки консоли
            break;
        case 2:
            clearConsole();
            cout << "Length of the string: " << myString.length() << endl;
            break;
        case 3:
            clearConsole();
            int index;
            cout << "Select index: ";
            cin >> index;
            cout << "Symbol be the index " << index << ": " << myString.getCharAt(index) << endl;
            break;
        case 4:
            clearConsole();
            int indexToReplace;
            char newChar;
            cout << "Input index to replace: ";
            cin >> indexToReplace;
            cout << "Input new symbol: ";
            cin >> newChar;
            myString.setCharAt(indexToReplace, newChar);
            break;
        case 5:
            clearConsole();
            int start, end;
            cout << "Set start and end indexes of the substring: ";
            cin >> start >> end;
            cout << "Substring: " << myString.substring(start, end) << endl;
            break;
        case 6:
            clearConsole();
            if (myString.isPalindrome()) {
                cout << "String is a palindrome.\n";
            }
            else {
                cout << "String isn't a palindrome.\n";
            }
            break;
        case 7:
            clearConsole();
            cout << "Number of different characters in a string: " << myString.countUniqueLatinChars() << endl;
            break;
        case 8:
            clearConsole();
            unsigned long long num;
            cout << "Enter a number to calculate factorial: ";
            cin >> num;
            cout << "Factorial of " << num << " is: " << factorial(num) << endl;
            break;
        case 0:
            break;
        default:
            clearConsole();
            cout << "Incorrect option. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
