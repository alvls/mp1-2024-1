#include "Check.h"
#include <iostream>

using namespace std;

// Constructor
CCheck::CCheck(CStorage* InStorage)
{
	if (InStorage)
		Storage = InStorage;

	else
		throw (exception("Invalid Storage Pointer!"));
}

// Adds an item to check
bool CCheck::AddItem(string& Code)
{
	if (!Storage)
		throw (exception("Invalid Storage Pointer!"));

	TItemData ItemData;
	if (Storage->GetItemData(ItemData, Code))
	{
		if (Items.count(Code) > 0)
			Items[Code] += 1;

		else
			Items[Code] = 1;

		int ActualCost = ItemData.GetActualCost();

		TotalCost += ItemData.Cost;
		TotalDiscount += ItemData.Cost - ActualCost;
		ToPay += ActualCost;

		return true;
	}

	return false;
}

// Removes an item to check
bool CCheck::RemoveItem(std::string& Code)
{
	if (!Storage)
		throw (exception("Invalid Storage Pointer!"));

	TItemData ItemData;
	if (Storage->GetItemData(ItemData, Code))
	{
		int ItemCount = Items.count(Code);

		if (ItemCount == 0)
			return false;

		else if (Items[Code] > 1)
			Items[Code] -= 1;

		else
			Items.erase(Code);

		int ActualCost = ItemData.GetActualCost();

		TotalCost -= ItemData.Cost;
		TotalDiscount -= ItemData.Cost - ActualCost;
		ToPay -= ActualCost;

		return true;
	}

	return false;
}

// Returns total cost of all items in the check
int CCheck::GetTotalCost() { return TotalCost; }

// Returns total discount of all items in the check
int CCheck::GetTotalDiscount() { return TotalDiscount; }

// Returns the ammount of money the customer has to pay 
int CCheck::GetToPay() { return ToPay; }

// Returns the number of different items in the check
int CCheck::GetItemCount() { return Items.size(); }


// Prints the check into the console
void CCheck::Print()
{
	if (!Storage)
		throw (exception("Invalid Storage Pointer!"));

	cout << endl << "List of Items:" << endl;

	for (auto Item : Items)
	{
		TItemData ItemData;
		Storage->GetItemData(ItemData, Item.first);

		cout << Item.second << " x " << ItemData.Name << " : " << ItemData.Cost << " rub" << " -" << ItemData.Discount << "% => " << ItemData.GetActualCost() << " rub;" << endl;
	}

	cout << endl << "Total Cost: " << TotalCost << " rub" << endl << "Total Discount: " << TotalDiscount << " rub" << endl << "To Pay: " << ToPay << " rub" << endl;
	cout << "Thank you for choosing us!" << endl << endl;
}