#include "slte.h"

int main() {
	slte e(6, {3, 0});
	e.locate();
	e.setInput();
	string ans = e.getInput();
	cout << "ans1: \'" << ans << "\'";

	e.setPosition(5, 7);
	e.locate();
	e.setInput();
	ans = e.getInput();
	cout << "ans2: \'" << ans << "\'";
	system("pause");
	return 0;
}