#include<iostream>
#include<string>
#include <map>
#include <chrono> //C++20 нужен

using namespace std;
using namespace chrono;

const year_month_day PAST{ year(1999), month(0), day(0) };

// Только данные отдельного депозита
class DepositData {
	friend class DepositManager;
	friend class ProcessingCenter;
private:
	//string number;
	//string password;
	bool active = false;
	int initial=0;
	int accrued=0;
	double percent=0;
	year_month_day startdate = PAST;
	year_month_day nextdate = PAST;
	int duration=0;
	int elapsed = 0;
//public:
	//Deposit(string number_, string password_) 
	void init(year_month_day date, int sum, int duration_, double percent_) {
		startdate = date;
		nextdate = date + months(1);
		initial = sum;
		accrued = 0;
		elapsed = 0;
		duration = duration_;
		percent = percent_;
		active = true;
	}

	void update(year_month_day date) {
		if (active) {
			while (date >= nextdate) {
				elapsed += 1;
				accrued += initial * percent/100;
				nextdate += months(1);
				if(elapsed >= duration) {
					active = false;
					break;
				}
			}
			
		}
	}
};

struct Client {
	string password;
	string name;
	int balance = 0;
	DepositData deposit;
	Client() {}
	Client(string password_, string name_) {
		name = name_;
		password = password_;
	}
};

// Процессинговый центр
class ProcessingCenter {
	friend class DepositManager;
private:
	map<string, Client> Data;
	year_month_day actual = PAST;

	Client* GetClient(string number) {
		auto it = Data.find(number);
		if (it != Data.end()) {
			return &(it->second);
		}
		else {
			return nullptr;
		}
	}
public:
	bool AddClient(string number, string password, string name) {
		if (password.length() < 3)
			return false;
		Data[number] = Client(password, name);
		return true;
	}

	bool CreditSalary(string number, int salary) {
		Client* client = GetClient(number);
		if (client) {
			client->balance += salary;
			return true;
		}
		return false;
	}

	bool Update(year_month_day today) {
		if (today <= actual)
			return 0;
		for (auto& i : Data) {
			i.second.deposit.update(today);
		}
		actual = today;
		return 1;
	}
};

double rates[5][4] = { //month / balancecategory
		{14, 14.5, 15, 16},
		{14.5, 15, 15.5, 16.5},
		{15, 15.5, 16, 17},
		{15.5, 16, 17, 17.5},
		{16, 17, 17.5, 18}
};

string periods[5]{ "3 месяца","6 месяцев","1 год","2 года","3 года" };
int periodsinmonths[5]{3,6,12,24,36};
string categories[4]{ "меньше 100тыс.","100тыс. - 500тыс.","500тыс. - 1млн.","больше 1млн." };

int BalanceCategory(int balance) {
	int c = -1;
	if (balance > 0)
		c++;
	if (balance > 100000)
		c++;
	if (balance > 500000)
		c++;
	if (balance > 1000000)
		c++;
	return c;
}

// Класс Депозит, который управляет депозитами
class DepositManager {
private:
	ProcessingCenter& center;
	bool session = false;
	string savednum;
	//string savedpw;
	Client* client = 0;

	
public:
	DepositManager(ProcessingCenter& bindedCenter) : center(bindedCenter) {} //при создании обязательно привязать к проц-центру
	bool Signed() {
		return session;
	}
	bool SignIn(string number, string password) {
		if (session)
			return false;
		Client* account = center.GetClient(number);
		if (account && (account->password==password)) {
			session = true;
			client = account;
			savednum = number;
			return true;
		}
		session = false;
		client = 0;
		return false;
	}

	void SignOut() {
		session = false;
		client = 0;
	}

	void printAvailable() {
		int w = 20;
		int c = BalanceCategory(client->balance);
		if (c < 0) {
			cout << "Нет доступных депозитов" << endl;
			
		}
		cout << "Доступны следующие депозиты:\n" << endl << setw(w) << "период/сумма";
		for (int i = 0;i <= c;i++) {
			cout << setw(w) << categories[i];
		}
		cout << endl;
		for (int j = 0; j < 5;j++) {
			cout << setw(w) << periods[j];
			for (int i = 0;i <= c;i++) {
				cout << setw(w) << rates[j][i];
			}
			cout << endl;
		}
	}

	bool PrintInfo() {
		if (session) {
			cout << "_________________________________________________________" << endl;
			
			cout << savednum << " " << client->name << ", баланс: " << client->balance <<"руб." << endl;
			if (client->deposit.initial == 0) {
				cout << "У вас нет депозитов\n";
				printAvailable();
				return 1;
			}
			else {
				DepositData* dep = &client->deposit;
				cout << "Текущий депозит: ";
				if (dep->active) {
					cout << "активный" << endl;
				}
				else {
					cout << "истёк " << dep->startdate + months(dep->duration) << endl;
				}
				cout << "Начат " << dep->startdate<<endl;
				cout << "Процентная ставка " << dep->percent <<"%"<< endl;
				cout << "Начальная сумма " << dep->initial << endl;
				cout << "Накоплено процентов " << dep->accrued << endl;
				if(dep->active){
					cout << "Следующее зачисление " << dep->nextdate << endl;
					cout << "Окончание через " << dep->duration - dep->elapsed << " месяцев (" << dep->startdate + months(dep->duration) << ")\n";
				}
			}
			


			return 1;
		}
		return 0;
	}

	bool newDeposit(int sum, int periodindex, year_month_day today) {
		if (session && (client->deposit.initial == 0)&&(client->balance>=sum)&&(periodindex<=4)&&(periodindex>0)&&(sum>0)) {
			client->balance -= sum;
			int c = BalanceCategory(sum);
			client->deposit.init(today, sum, periodsinmonths[periodindex], rates[periodindex][c]);
			return 1;
		}
		return 0;
	}

	bool withdrawPercents(bool all = false, int part = 0) {
		if (session) {
			
			int available = client->deposit.accrued;
			int withdraw = part;
			if (withdraw > available)
				return 0;

			if (all) {
				withdraw = available;
			}

			if (withdraw <= 0)
				return 0;

			client->deposit.accrued -= withdraw;
			client->balance += withdraw;
			return 1;

		}
		return 0;
	}

	bool closeDeposit() {
		if (session && (client->deposit.initial != 0) && (!client->deposit.active)) {
			withdrawPercents(true);
			client->balance += client->deposit.initial;
			client->deposit.initial = 0;
			return 1;
		}
		return 0;
	}
	
};


int main() {
	setlocale(LC_ALL, "rus");

	year_month_day today{ year(2024), month(4), day(22) };

	ProcessingCenter bank;
	bank.AddClient("0000", "огурец123", "Иванов Иван Иванович");
	bank.CreditSalary("0000", 700000);

	DepositManager man(bank);
	man.SignIn("0000", "огурец123");
	man.PrintInfo();
	man.newDeposit(500000, 3, today);
	man.PrintInfo();

	bank.Update(today + months(12));
	man.PrintInfo();

	bank.Update(today + months(25));
	man.PrintInfo();
	man.closeDeposit();
	man.PrintInfo();
	man.SignOut();


	bank.AddClient("0123", "admin123", "Сырьёзный Сергей Александрович");
	bank.CreditSalary("0123", 1230000);

	man.SignIn("0123", "admin123");
	man.PrintInfo();
	man.newDeposit(1000000, 4, today);
	man.PrintInfo();

	bank.Update(today + months(15));
	man.PrintInfo();

	bank.Update(today + months(37));
	man.PrintInfo();
	man.closeDeposit();
	man.PrintInfo();
	man.SignOut();
	
	system("pause");
}