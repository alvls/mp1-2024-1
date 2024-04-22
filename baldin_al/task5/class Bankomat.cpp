#include "Bankomat.h"

ProcessingCenter globalProcessingCenter;

int main()
{
	Bankomat ATM1(&globalProcessingCenter);
	Bankomat ATM2(&globalProcessingCenter);
	ATM1.addClient("0001", "Ivan", "Ivanov", "Ivanovich", 1000, "1234");
	ATM2.addClient("0002", "Petr", "Petrov", "Petrovich", 5000, "4321");

	try {
		ATM1.acceptCard("0001");
		bool f1 = ATM1.CheckPin("1111");
		bool f2 = ATM1.CheckPin("2222");
		ATM1.returnCard();
		ATM1.acceptCard("0001");
		bool f3 = ATM1.CheckPin("3333");
		bool f4 = ATM1.CheckPin("1234");
		bool f5 = ATM1.giveCash(1000);
		cout << (f5 == true ? "Operation completed" : "Operation failed") << '\n';
		ATM1.printAccountState();
		ATM1.returnCard();

		ATM2.acceptCard("0002");
		bool f6 = ATM2.CheckPin("4321");
		bool f7 = ATM2.acceptCash({ 3, 1, 0, 2, 0, 1 });
		cout << (f7 == true ? "Operation completed" : "Operation failed") << '\n';
		ATM2.printAccountState();
		ATM2.returnCard();

		Client x = ATM2.findClient("0001");
		cout << x.l_name << ' ' << x.f_name << ' ' << x.m_name << ' ' << x.sum << ' ' << '\n';

	}
	catch (string s) {
		if (s == "Access error") cout << "Card has already been accepted" << '\n';
		else if (s == "Blocked card") cout << "Your card has been blocked" << '\n';
		else if (s == "Return error") cout << "Card has not been accapted yet" << '\n';
		else if (s == "Failed find") cout << "There is no such client" << '\n';
		else if (s == "PIN verification error 1") cout << "Card has not been accapted yet" << '\n';
		else if (s == "PIN verification error 2") cout << "Incorrect pincode format" << '\n';
		else if (s == "Print error 1") cout << "To print the account state, you must first insert the card" << '\n';
		else if (s == "Print error 2") cout << "To print the account state, you must first enter the pincode" << '\n';
	}

	system("pause");
}