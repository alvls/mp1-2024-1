#pragma once

#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Client {
	string card_number;
	string f_name;
	string l_name;
	string m_name;
	long long sum;
	string pin_code;

	Client() : card_number(""), f_name(""), l_name(""), m_name(""), sum(0), pin_code("") {};

	Client(const string& card_number_, const string& f_name_, const string& l_name_, const string& m_name_, long long sum_, const string& pin_code_) :
		card_number(card_number_), f_name(f_name_), l_name(l_name_), m_name(m_name_), sum(sum_), pin_code(pin_code_) {};

	bool operator == (const Client& c) const;
};

class ProcessingCenter {
	map<string, Client> clients;
	map<string, bool> blockedCards;
public:

	void addClient(const string& card_number, const string& f_name, const string& l_name, 
		const string& m_name, long long sum, const string& pin_code);

	Client findClient(const string& card_number);

	string getPin(const string& card_number);

	long long getSum(const string& card_number);

	void updAcc(const string& card_number, int amount, char c);

	bool CheckCard(const string& card_number);

	void BlockCard(const string& card_number);

	void printAccountState(const string& card_number);
};

class Bankomat {
	int cst[6] = {}; // 100, 200, 500, 1000, 2000, 5000
	int nom[6] = { 100, 200, 500, 1000, 2000, 5000 };
	long long all_sum = 0;
	ProcessingCenter* PC;
	string card = "";
	int attemps = 0;
	bool isRightPin = false;

	bool CheckCard(const string& card_number);

	void BlockCard(const string& card_number);

public:
	Bankomat(ProcessingCenter* pc) : PC(pc) {
		for (int i = 0; i < 6; i++) {
			cst[i] = 2000 * 0.8;
			all_sum += cst[i] * nom[i];
		}
	}

	void addClient(const string& card_number, const string& f_name, const string& l_name, 
		const string& m_name, long long sum, const string& pin_code);

	void acceptCard(const string& card_number);

	Client findClient(const string& card_number);

	bool CheckPin(const string& pin);

	void printAccountState();

	bool giveCash(int amount);

	bool acceptCash(const vector<int>& c);

	void returnCard();
};