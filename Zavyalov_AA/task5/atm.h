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
	void addClient(const std::string card, const ClientInfo& info);
	void deleteClient(const std::string card);
	bool checkPin(const std::string card, const std::string pin);
	void addCash(std::string card, long long sum);
	ClientInfo getClientInfo(std::string card);
};

class ATM // Automated Teller Machine
{
	ProcessingCenter* database;
	std::string card = ""; // current card in atm
	short pin_tries = 0;
	std::set<std::string> blacklist; // set of blocked cards
	int cassetes[6] = { 1600,1600,1600,1600,1600,1600 }; // 100, 200, 500, 1000, 2000, 5000 
public:
	ATM(ProcessingCenter* db);
	void insertCard(std::string card_);
	ClientInfo getClientInfo(std::string card_);
	bool checkPin(std::string pin);
	void print();
	std::vector<int> getCash(long long sum);
	void insertCash(std::vector<int> cash);
	void returnCard();
	void changeDataBase(ProcessingCenter* db);
};