#include <iostream>
#include "atm.h"

using namespace std;

int main() {
	ProcessingCenter pc1;
	ProcessingCenter *pc1ptr = &pc1;
	ClientInfo ci("John", "Wick", "Andreevich", 104300, "0231");
	(*pc1ptr).addClient("1337", ci);
	ATM atm1(pc1ptr);
	ClientInfo f("John", "Wick", "Andreevich", 100, "0231");
	atm1.insertCard("1337");
	atm1.print();
	vector<int> sf = atm1.getCash(12300);
	for (auto x : sf) {
		cout << x << " ";
	}
	cout << endl;
	atm1.print();
	vector<int> v = { 1,2,4,4,10,19 }; // 19 * 5000 + 10 * 2000 + 4 * 1000 + 4 * 500 + 2 * 200 + 1 * 100
	atm1.insertCash(v);
	atm1.print();
	cout << atm1.checkPin("0231") << endl;
	try {
		cout << atm1.checkPin("1233") << " " << atm1.checkPin("1233") << " " << atm1.checkPin("1233");
		
	}
	catch (string s) {

	}
	system("pause");
	return 0;
}