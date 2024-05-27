#include "Bankomat.h"

bool Client::operator == (const Client& c) const {
	return (f_name == c.f_name && l_name == c.l_name && m_name == c.m_name && sum == c.sum && pin_code == c.pin_code);
}

void ProcessingCenter::addClient(const string& card_number, const string& f_name, const string& l_name, const string& m_name,
	long long sum, const string& pin_code) {
	clients[card_number] = Client(card_number, f_name, l_name, m_name, sum, pin_code);
	blockedCards[card_number] = false;
}

Client ProcessingCenter::findClient(const string& card_number) {
	Client d;
	if (clients[card_number] == d) throw string("Failed find");
	else return clients[card_number];
}

string ProcessingCenter::getPin(const string& card_number) {
	return clients[card_number].pin_code;
}

long long ProcessingCenter::getSum(const string& card_number) {
	return clients[card_number].sum;
}

void ProcessingCenter::updAcc(const string& card_number, int amount, char c) {
	if (c == '-') clients[card_number].sum -= amount;
	else clients[card_number].sum += amount;
}

bool ProcessingCenter::CheckCard(const string& card_number) {
	return blockedCards[card_number];
}

void ProcessingCenter::BlockCard(const string& card_number) {
	blockedCards[card_number] = true;
}

void ProcessingCenter::printAccountState(const string& card_number) {
	Client x = clients[card_number];
	cout << x.f_name << ' ' << x.l_name << ' ' << x.m_name << ' ' << x.sum << '\n';
}

bool Bankomat::CheckCard(const string& card_number) {
	return PC->CheckCard(card_number);
}

void Bankomat::BlockCard(const string& card_number) {
	PC->BlockCard(card_number);
}

void Bankomat::addClient(const string& card_number, const string& f_name, const string& l_name, const string& m_name,
	long long sum, const string& pin_code) {
	PC->addClient(card_number, f_name, l_name, m_name, sum, pin_code);
}

void Bankomat::acceptCard(const string& card_number) {
	if (card != "") throw string("Access error");
	if (CheckCard(card_number)) throw string("Blocked card");
	card = card_number;
}

Client Bankomat::findClient(const string& card_number) {
	return PC->findClient(card_number);
}

bool Bankomat::CheckPin(const string& pin) {
	if (card == "") throw string("PIN verification error 1");
	if (pin.size() != 4) throw string("PIN verification error 2");
	if (CheckCard(card)) throw string("Blocked card");

	if (PC->getPin(card) == pin) {
		isRightPin = true;
		return true;
	}
	else {
		attemps++;
		if (attemps == 3) {
			BlockCard(card);
		}
		return false;
	}
}

void Bankomat::printAccountState() {
	if (card == "") throw string("Print error 1");
	if (!isRightPin) throw string("Print error 2");
	PC->printAccountState(card);
}

bool Bankomat::giveCash(int amount) {
	if ((!isRightPin) || (amount % 100 != 0) || (amount > PC->getSum(card))
		|| (amount > all_sum)) return false;

	int num_bills = 0;
	int amt = amount;
	int s[6] = {}; // 100, 200, 500, 1000, 2000, 5000
	for (int i = 0; i < 6; i++) s[i] = cst[i];

	for (int i = 5; i >= 0 && amount > 0; i--) {
		int cnt = amount / nom[i];
		if (cst[i] < cnt) {
			cnt = cst[i];
		}
		amount -= cnt * nom[i];
		s[i] -= cnt;
		num_bills += cnt;
	}
	if (num_bills > 40) return false;
	for (int i = 0; i < 6; i++) cst[i] = s[i];
	PC->updAcc(card, amt, '-');
	all_sum -= amt;
	return true;
}

bool Bankomat::acceptCash(const vector<int>& c) {
	if (!isRightPin || c.size() != 6) return false;
	int num_b = 0;
	long long sum = 0;
	for (int i = 0; i < 6; i++) {
		num_b += c[i];
		sum += c[i] * nom[i];
		if ((2000 - cst[i] < c[i]) || (num_b > 40)) return false;
	}

	for (int i = 0; i < 6; i++) {
		cst[i] += c[i];
	}

	PC->updAcc(card, sum, '+');
	all_sum += sum;
	return true;
}

void Bankomat::returnCard() {
	if (card == "") throw string("Return error");
	card = "";
	attemps = 0;
	isRightPin = false;
}