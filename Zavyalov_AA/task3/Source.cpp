#include "slte.h"

int main() {
	slte e(6, {3, 0});
	e.locate();
	e.setInput();
	string ans = e.getInput();
	COORD crd = e.getPosition();
	cout << "input field coordinates: " << crd.X << "," << crd.Y << "; input value: \'" << ans << "\'";

	e.setPosition(50, 7);
	e.locate();

	e.setSize(11);
	e.setInput();
	int sz = e.getSize();
	ans = e.getInput();
	cout << "input field length: " << sz << "; input value: \'" << ans << "\'" << endl;
	system("pause");
	return 0;
}