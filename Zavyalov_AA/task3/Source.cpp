#include "slte.h"

int main() {
	slte e(15, {3, 0});
	e.locate();
	e.start();
	string ans = e.getInput();
	cout << endl << ans << "." << endl;
	system("pause");
	return 0;
}