#include "Vect.h"

using namespace std;

int main() {
    vect v1(3), v2(3), v(3);
    //vect v1(3), v2(4), v(3);

    v1.setCoord(1, 0);
    v1.setCoord(77, 1);
    v1.setCoord(5, 2);

    v2.setCoord(35, 0);
    v2.setCoord(21, 1);
    v2.setCoord(-10, 2);
   // v2.setCoord(10, 3);

    cout << "v2 second coordination is " << v2.getCoord(1) << endl;
    cout << "v2 len is " << v2.getLen() << endl;
    cout << "\n\n";

    cout << "v = v1 + v2\n";
    v = v1 + v2;
    v.printVect();
    cout << "\n\n";

    cout << "v = v1 * v2\n";
    v = v1 * v2;
    v.printVect();
    cout << "\n\n";

    cout << "v * const\n";
    v = v1 * 3;
    v.printVect();
    cout << "\n\n";

    cout << "v = v2 = v1\n";
    v = v2 = v1;
    v1.printVect();
    cout << endl;
    v2.printVect();
    cout << endl;
    v.printVect();
    cout << endl;

    system("pause");
    return 0;
}