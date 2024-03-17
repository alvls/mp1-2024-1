#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cstdlib>

class String {
private:
    std::string str;
public:
    String() : str("") {}

    void setString(const std::string& s) {
        if (s.length() <= 40) {
            str = s;
        }
        else {
            std::cout << "The length of the string exceeds 40 characters. Shorten the line.\n";
        }
    }

    void inputString() {
        std::cout << "Enter a string (no more than 40 characters): ";
        std::cin.ignore();
        std::getline(std::cin, str);
        if (str.length() > 40) {
            std::cout << "The length of the string exceeds 40 characters. Shorten the line.\n";
            str = "";
        }
    }

    int length() const {
        return str.length();
    }

    char getCharAt(int index) const {
        if (index >= 0 && index < str.length()) {
            return str[index];
        }
        else {
            std::cout << "The index goes beyond the line boundaries.\n";
            return '0';
        }
    }

    void setCharAt(int index, char c) {
        if (index >= 0 && index < str.length()) {
            str[index] = c;
        }
        else {
            std::cout << "The index goes beyond the line boundaries.\n";
        }
    }

    std::string substring(int start, int end) const {
        if (start >= 0 && start < end && end <= str.length()) {
            return str.substr(start, end - start);
        }
        else {
            std::cout << "Going beyond the line boundaries when selecting a substring.\n";
            return "";
        }
    }

    bool isPalindrome() const {
        std::string revStr = str;
        std::reverse(revStr.begin(), revStr.end());
        return str == revStr;
    }

    int countUniqueLatinChars() const {
        std::unordered_set<char> latinChars;
        for (char c : str) {
            if (isalpha(c) && islower(c)) {
                latinChars.insert(c);
            }
        }
        return latinChars.size();
    }

    void print() const {
        std::cout << str << std::endl;
    }

    ~String() {}
};

int main() {
    String myString;
    int choice;

    do {
        std::cout << "Entered line: ";
        myString.print();

        std::cout << "\nChoose an option:\n";
        std::cout << "1. Input string\n";
        std::cout << "2. Length of the string\n";
        std::cout << "3. Character by the index\n";
        std::cout << "4. Replacing a character by the index\n";
        std::cout << "5. Substring from a string\n";
        std::cout << "6. Check if the string is a palindrome\n";
        std::cout << "7. Number of different characters in a string\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";

        std::cin >> choice;

        switch (choice) {
        case 1:
            myString.inputString();
            system("cls");
            break;
        case 2:
            system("cls");
            std::cout << "Length of the string: " << myString.length() << std::endl;
            break;
        case 3:
            system("cls");
            int index;
            std::cout << "Select index: ";
            std::cin >> index;
            std::cout << "Symbol be the index " << index << ": " << myString.getCharAt(index) << std::endl;
            break;
        case 4:
            system("cls");
            int indexToReplace;
            char newChar;
            std::cout << "Input index to replace: ";
            std::cin >> indexToReplace;
            std::cout << "Input new symbol: ";
            std::cin >> newChar;
            myString.setCharAt(indexToReplace, newChar);
            break;
        case 5:
            system("cls");
            int start, end;
            std::cout << "Set start and end indexes of the substring: ";
            std::cin >> start >> end;
            std::cout << "Substring: " << myString.substring(start, end) << std::endl;
            break;
        case 6:
            system("cls");
            if (myString.isPalindrome()) {
                std::cout << "String is a palindrom.\n";
            }
            else {
                std::cout << "String isn't a palindrom.\n";
            }
            break;
        case 7:
            system("cls");
            std::cout << "Number of different characters in a string: " << myString.countUniqueLatinChars() << std::endl;
            break;
        case 0:
            break;
        default:
            system("cls");
            std::cout << "Incorrect option. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
