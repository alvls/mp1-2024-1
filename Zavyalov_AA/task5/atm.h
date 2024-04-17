#pragma once

#include <string>
#include <map>
#include <set>
#include <vector>
#include <iostream>

struct ClientInfo {
	std::string name = "";
	std::string surname = "";
	std::string patronymic = "";
	long long amount = 0;
	std::string pincode = "";
	ClientInfo(std::string name_ = "", std::string surname_ = "", std::string patronymic_ = "", long long amount_ = 0, std::string pincode_ = "") {
		name = name_, surname = surname_, patronymic = patronymic_, amount = amount_, pincode = pincode_;
	}
}; 

class ProcessingCenter {

	std::map<std::string, ClientInfo> database;
	std::set<std::string> existing; // consist of card numbers of clients in current processing center
public:
	void addClient(const std::string card, const ClientInfo& info) {
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
	bool checkPin(const std::string card, const std::string pin) {
		return database[card].pincode == pin;
	}
	void addCash(std::string card, long long sum) {
		database[card].amount += sum;
		std::cout << "";
	}
	ClientInfo getClientInfo(std::string card) {
		if (!existing.count(card)) {
			return ClientInfo("", "", "", 0, "");
		}
		return database[card];
	}
};

class ATM // Automated Teller Machine
{
	ProcessingCenter* database;
	std::string card = ""; // current card in atm
	short pin_tries = 0;
	std::set<std::string> blacklist; // set of blocked cards
	int cassetes[6] = { 1600,1600,1600,1600,1600,1600 }; // 100, 200, 500, 1000, 2000, 5000
public:
	ATM(ProcessingCenter* db) { // сделать конст // передумал, не надо делать конст
		database = db;
	}
	void insertCard(std::string card_) {
		if (card != "") throw "Impossible to enter a new card while the card is in the ATM";
		if (blacklist.count(card_)) throw "The card is blocked";
		card = card_;
		pin_tries = 0;
	}
	ClientInfo getClientInfo(std::string card_) {
		ClientInfo clinf = database->getClientInfo(card_);
		if (clinf.pincode == "") { // pincode = "" means that there's no such client in database yet
			throw "There is no client with that card number in the system";
		}
		return clinf;
	}
	bool checkPin(std::string pin) {
		bool ok = pin == (database->getClientInfo(card)).pincode;
		if (ok) {
			pin_tries = 0;
			return ok;
		}
		else
		{
			pin_tries++;
			if (pin_tries == 3) {
				blacklist.insert(card);
				throw "An incorrect PIN code have been entered three times in a row. The card is now blocked.";
			}
		}
	}
	void print() {
		if (blacklist.count(card)) throw "The card is blocked";
		ClientInfo clinfo = (database->getClientInfo(card));
		std::cout << "Card number: " << card << std::endl;
		std::cout << "Full name: " << clinfo.name << " " << clinfo.surname << " " << clinfo.patronymic << std::endl;
		std::cout << "Amount: " << clinfo.amount << std::endl;
	}
	std::vector<int> getCash(long long sum) {
		ClientInfo clinfo = (database->getClientInfo(card));
		if (sum > clinfo.amount) throw "Insufficient funds in the account";
		long long csum = sum;
		if (sum / 5000 > 40) throw "Cannot process an operation that requires more than 40 bills";
		std::vector<int> res(6);
		int totalbills = 0;
		int denominations[6] = { 100,200,500,1000,2000,5000 };
		int counts[6] = { 0 };
		for (int i = 5; i >= 0 && sum > 0; i--) {
			int count = sum / denominations[i];
			if (count > cassetes[i]) {
				count = cassetes[i];
			}
			sum -= count * denominations[i];
			counts[i] = count;
			res[i] = count;
			totalbills += count;
		}
		if (sum > 0) throw "There are not enough banknotes in the ATM to complete the operation";
		if (totalbills > 40) throw "Cannot process an operation that requires more than 40 bills";
		for (int i = 0; i < 6; i++) {
			cassetes[i] -= res[i];
		}
		database->addCash(card, -csum);
		return res;
	}
	void insertCash(std::vector<int> cash) { // cash.size() must be equal to 6
		long long sum = 0;
		int totalcount = 0;
		int denominations[6] = { 100,200,500,1000,2000,5000 };
		for (int i = 0; i < 6; i++) {
			sum += denominations[i] * cash[i];
			totalcount += cash[i];
		}
		if (totalcount > 40) throw "Cannot process an operation that requires more than 40 bills";
		for (int i = 0; i < 6; i++) {
			if (cassetes[i] + cash[i] > 2000) throw "The ATM has run out of space for storing banknotes";
			cassetes[i] += cash[i];
		}
		database->addCash(card, sum);
	}
	void returnCard() {
		card = "";
	}
	void changeDataBase(ProcessingCenter* db) { 
		database = db;
	}
	
};