#include "CashRegister.h"
#include <iostream>

using namespace std;

int main()
{
	CStorage* Storage = new CStorage();
	CCashRegister CashRegister(Storage);

	cout << "CASH REGISTER PROGRAM:" << endl;
	cout << "Commands:" << endl << "1) '_Print_' to print out the check;" << endl
		<< "2) '_End_' to exit;" << endl
		<< "3) '_Random_' to add a random item to the check (just for fun!);" << endl
		<< "4) '_Remove_*Code*' to remove item from the check;" << endl << endl;

	bool Running = true;

	while (Running)
	{
		string Code;

		bool Removing = false;

		bool Inputing = true;
		do
		{
			cout << "Scan Code/Command: ";
			cin >> Code;

			Inputing = !(Storage->IsValidCode(Code) || Code == "_Print_" || Code == "_End_" || Code == "_Random_");

			// Checking for _Remove_ Command
			if (Inputing && Code.length() > 8 && Code.substr(0, 8) == "_Remove_")
			{
				Code = Code.erase(0, 8);
				Inputing = !Storage->IsValidCode(Code);
				Removing = !Inputing;
			}

			if (Inputing)
				cout << endl << "Invalid Code/Command" << endl;

		} while (Inputing);


		// Removing item from the check
		if (Removing)
		{
			if (CashRegister.RemoveItem(Code))
				CashRegister.PrintCashierInfo("Item Removed:", Code);
			else
				cout << endl << "No such item in the check" << endl;
		}

		// Printing the Check
		else if (Code == "_Print_")
		{
			if (CashRegister.PrintOutCheck())
				cout << endl << "New Customer: " << endl;

			else
				cout << endl << "No items in the check" << endl;
		}

		// Ending the program
		else if (Code == "_End_")
			Running = false;

		// Adding random items to the check
		else if (Code == "_Random_")
		{
			string RandomCode;
			CashRegister.ScanItem(RandomCode = Storage->GetRandomItemCode());
			CashRegister.PrintCashierInfo("Item Scanned:", RandomCode);
		}

		// Scanning the item
		else
		{
			CashRegister.ScanItem(Code);
			CashRegister.PrintCashierInfo("Item Scanned:", Code);
		}
	}

	delete Storage;
	return 0;
}