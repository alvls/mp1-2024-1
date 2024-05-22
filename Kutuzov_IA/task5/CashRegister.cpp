#include "CashRegister.h"
#include <iostream>

using namespace std;

// Constructor
CCashRegister::CCashRegister(CStorage* InStorage)
{
	if (InStorage)
		Storage = InStorage;

	else
		throw (exception("Invalid Storage Pointer!"));
}

// Destructor
CCashRegister::~CCashRegister()
{
	delete CurrentCheck;
}

// Scannes item and adds it to the check, returns "true" if successful
bool CCashRegister::ScanItem(std::string& Code)
{
	if (!Storage)
		throw (exception("Invalid Storage Pointer!"));

	if (!Storage->IsValidCode(Code))
		return false;

	// Creating new check, if needed
	if (!CurrentCheck)
		CurrentCheck = new CCheck(Storage);

	return CurrentCheck->AddItem(Code);
}

// Remove item from the check, returns "true" if successful
bool CCashRegister::RemoveItem(string& Code)
{
	if (!Storage)
		throw (exception("Invalid Storage Pointer!"));

	if (!CurrentCheck || !Storage->IsValidCode(Code))
		return false;

	return CurrentCheck->RemoveItem(Code);
}

// Finishes the current check and prints it out, also resetting the CashRegister for the next cusomer
bool CCashRegister::PrintOutCheck()
{
	if (!Storage)
		throw (exception("Invalid Storage Pointer!"));

	if (!CurrentCheck || CurrentCheck->GetItemCount() == 0)
		return false;

	CurrentCheck->Print();

	delete CurrentCheck;
	CurrentCheck = nullptr;
}

// Prints scanned item data to the console (for the cashier)
void CCashRegister::PrintCashierInfo(string OperationName, string& Code)
{
	if (!Storage)
		throw (exception("Invalid Storage Pointer!"));

	TItemData ItemData;
	if (CurrentCheck && Storage->GetItemData(ItemData, Code))
	{
		cout << OperationName << " " << Code << ":" << ItemData.Name << ": " << ItemData.Cost << " rub -" << ItemData.Discount << "% => " << ItemData.GetActualCost() << " rub." << endl;
		cout << "Total cost: " << CurrentCheck->GetTotalCost() << " rub, " << endl << "With discount: " << CurrentCheck->GetToPay() << " rub." << endl << endl;
	}
}