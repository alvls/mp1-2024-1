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
	system("pause");
	return 0;
}