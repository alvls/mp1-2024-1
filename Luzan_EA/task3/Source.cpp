#include "Menu.h"

using namespace std;

void clearScreen() {
    system("cls");
}

int main() {
    try {
        const int SIZE = 7;
        Menu h(SIZE);
        string a[SIZE] = {"0 ", "1 ", "2 ","3 ", "4 ", "5 ", "6 "};
        for (int i = 0; i < SIZE; i++) {
            h.setItm("itmName" + a[i], i);
        }

        h.getInp(10,10);
        clearScreen();
        h.printLastChoice();

    }
    catch (int err) {
        switch (err) {
        case 1:
            cout << "Console failed to start\n";
            break;
        default:
            cout << "Something went wrong\n";
        }
    }
    catch (exception) {
        cout << "Something went wrong\n";
    }

    system("pause");
    return 0;
}


