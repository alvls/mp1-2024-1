#include "TextEditor.h"

int main() {
    TextEditor t(10, 10, 5);
    t.place();
    t.setStr();
    string s1 = t.getStr();
    COORD p1 = t.getPos();
    cout << "Coordinates of the field: " << p1.X << ' ' << p1.Y << '\n';
    cout << "Input string: " << s1 << '\n';

    t.setPos(15, 15);
    t.setLen(10);
    t.place();
    t.setStr();
    string s2 = t.getStr();
    COORD p2 = t.getPos();
    cout << "New coordinates: " << p2.X << ' ' << p2.Y << '\n';
    cout << "New string: " << s2 << '\n';

    system("pause");
}