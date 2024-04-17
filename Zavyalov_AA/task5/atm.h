#pragma once

#include <string>
#include <map>
#include <set>
#include <vector>
#include <iostream>
// ������� �������� �� 1 ��������������� ������; 2 �� �� ��� ����� ������ ������ �� 40 �����; 3 ����� ��� ���������; 
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
	// ��� ������� �����, �� ����� �������
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
	// ����� ��� ������� �����
	bool checkPin(const std::string card, const std::string pin) {
		return database[card].pincode == pin; // �� ������
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
	std::string card; // current card in atm
	short pin_tries = 0;
	ClientInfo clinfo; // current client info
	std::set<std::string> blacklist; // set of blocked cards
	int cassetes[6] = { 1600,1600,1600,1600,1600,1600 }; // 100, 200, 500, 1000, 2000, 5000
public:
	ATM(ProcessingCenter* db) { // ������� ����� // ���������, �� ���� ������ �����
		database = db;
	}
	void insertCard(std::string card_) {
		if (blacklist.count(card_)) throw "The card is blocked";
		card = card_;
		pin_tries = 0;
		clinfo = (database->getClientInfo(card));
	}
	ClientInfo getClientInfo(std::string card_) {
		ClientInfo clinf = database->getClientInfo(card_);
		if (clinf.pincode == "") { // pincode = "" means that there's no such client in database yet
			throw "There is no client with that card number in the system";
		}
		return clinf;
	}
	bool checkPin(std::string pin) {
		bool ok = pin == clinfo.pincode;
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
		std::cout << "Card number: " << card << std::endl;
		std::cout << "Full name: " << clinfo.name << " " << clinfo.surname << " " << clinfo.patronymic << std::endl;
		std::cout << "Amount: " << clinfo.amount << std::endl;
	}
	std::vector<int> getCash(long long sum) {
		
	}

	void changeDataBase(ProcessingCenter* db) { 
		database = db;
	}
	
};