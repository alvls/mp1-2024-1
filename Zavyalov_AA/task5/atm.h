#pragma once
#include <string>
#include <map>
#include <set>
// сделать проверку на 1 переполненность касеты; 2 на то что сумму нельзя выдать за 40 купюр; 3 карта уже вставлена; 
struct ClientInfo {
	std::string name;
	std::string surname;
	std::string patronymic;
	long long amount;
	std::string pincode;
};

class ProcessingCenter {

	std::map<std::string, ClientInfo> database;
	std::set<std::string> existing;
public:
	// это удалить можно, хз лучше оставлю
	void addClient(const std::string card,const ClientInfo& info) {
		if (!existing.count(card)) {
			database[card] = info;
			existing.insert(card);
		}
		else
		{
			throw "Client with this card already exists in this processing center";
		}
	}
	void deleteClient(const std::string card) {
		if (existing.count(card)) {
			existing.erase(card);
		}
	}
	// конец это удалить можно
	bool checkPin(const std::string card, const std::string pin) {
		return database[card].pincode == pin; // мб скобки
	}
};

class ATM
{
	ProcessingCenter pcenter;
};