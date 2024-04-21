#include "Storage.h"
#include <fstream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;


// ITEM DATA

// Returs items cost with discount applied
int TItemData::GetActualCost()
{
	return Cost - (Discount * Cost / 100);
}


// STORAGE

// Default constructor
CStorage::CStorage(string DataBaseFileName)
{
	LoadDataBase(DataBaseFileName);
}

// Finds item data in the list
bool CStorage::GetItemData(TItemData& OutItemData, std::string Code)
{
	if (IsValidCode(Code))
	{
		OutItemData = ItemList[Code];
		return true;
	}

	return false;
}

// Checks if Code is valid
bool CStorage::IsValidCode(string& Code)
{
	return ItemList.count(Code) > 0;
}

// Reads data base from file
void CStorage::LoadDataBase(string FileName)
{
	ItemList.clear();

	ifstream file(FileName);
	if (file.is_open())
	{
		int n = 0;
		file >> n;

		for (int i = 0; i < n; i++)
		{
			string Code;
			TItemData NewItem;

			file >> Code >> NewItem.Name >> NewItem.Cost >> NewItem.Discount;

			ItemList[Code] = NewItem;
		}

		file.close();
	}

	else
		throw (exception("No such data base file!"));

}


// JUST FOR FUN: gets a random item from the List
string CStorage::GetRandomItemCode()
{
	vector<string> Codes;

	for (auto Item : ItemList)
		Codes.push_back(Item.first);

	srand(time(0));
	int Random = rand() % Codes.size();

	return Codes[Random];
}