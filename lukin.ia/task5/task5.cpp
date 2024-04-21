#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
using namespace std;
void clear_c()
{
	Sleep(2000);
	system("cls");
}
struct output
{
	int count_of_bnk[6] = {0};
	int status = 1;//все нормально
	int the_wh_am;
};
struct cartridge
{
	int count;
	int denomination;
};
struct client//class -> struct
{
	unsigned long int account;
	unsigned int PIN;
	string card_number;
	string full_name;
	bool is_banned;
	int wrong_attempts;
};
class processing_center
{
public:
	vector<client> database;
	void add_client(string name, unsigned long int account_, unsigned int pin, string card)
	{
		if (card.size() != 4)
		{
			throw 4;
			return;
		}
		if (pin < 0 || pin > 9999)
		{
			throw 5;
			return;
		}
		client tmp;
		tmp.account = account_;
		tmp.card_number = card;
		tmp.full_name = name;
		tmp.is_banned = false;
		tmp.wrong_attempts = 0;
		tmp.PIN = pin;
		database.push_back(tmp);
	}
};
class ATM
{
	static processing_center clients; //получается одна база данных на все банкоматы этого банка (надеюсь)
	cartridge banknotes[6] = { {1600,5000},{1600,2000},{1600,1000},{1600,500},{1600,200},{1600,100} };
	bool is_card_inside = false;
	client user;//временная копия пользователя
	client find_user(string card)
	{
		for (int i = 0; i < clients.database.size(); i++)
			if (clients.database[i].card_number == card)
				return clients.database[i];
		throw 3;
	}
	void data_ban()//для блока карты на сервере
	{
		for (int i = 0; i < clients.database.size(); i++)
			if (clients.database[i].card_number == user.card_number)
				clients.database[i].is_banned = true;
	}
	void upd_acc()
	{
		for (int i = 0; i < clients.database.size(); i++)
			if (clients.database[i].card_number == user.card_number)
				clients.database[i].account = user.account;
	}
public:
	void accept_card(string card)
	{
		user = find_user(card);
		if (user.is_banned)
		{
			throw 1;
			return;
		}
		is_card_inside = true;
		return;
	}
	void card_off()
	{
		is_card_inside = false;
	}
	bool enter_the_pin(int input)
	{
		if (!is_card_inside)
		{
			throw 2;
			return false;
		}
		if (input == user.PIN)
			return true;
		else
		{
			user.wrong_attempts++;
			return false;
		}
	}
	void check_ban_user()
	{
		if (!is_card_inside)
			return;
		if (user.wrong_attempts == 3)
		{
			user.is_banned = true;
			data_ban();
		}	
	}
	bool Get_user_status()
	{
		return user.is_banned;
	}
	client GetUser()
	{
		return user;
	}
	void add_client(string name, unsigned long int account_, unsigned int pin, string card)
	{
		clients.add_client(name, account_, pin, card);
	}
	output wdr_cash(int sum)
	{
		int tmp = sum;
		if (!is_card_inside)
			throw 2;
		if (sum > user.account)
			throw 7;
		output issuance;
		int count = 0;
		for (int i = 0; i < 6 && count < 40;)
		{
			if (banknotes[i].count > 0 && tmp / banknotes[i].denomination > 0)
			{
				tmp = tmp - banknotes[i].denomination;
				banknotes[i].count--;
				issuance.count_of_bnk[i]++;
				count++;
				continue;
			}
			i++;
		}
		if (tmp != 0)
		{
			sum = sum - tmp;
			if (count == 40)
				issuance.status = 2;//лимит по купюрам
			else
				issuance.status = 3;//пустые картриджи
		}
		issuance.the_wh_am = sum;
		user.account = user.account - sum;
		upd_acc();
		return issuance;
	}
	output put_cash(int sum)
	{
		int tmp = sum;
		if (!is_card_inside)
			throw 2;
		int count = 0;
		output deposit;
		for (int i = 0; i < 6 && count < 40;)
		{
			if (banknotes[i].count < 2000 && tmp / banknotes[i].denomination > 0)
			{
				tmp = tmp - banknotes[i].denomination;
				banknotes[i].count++;
				deposit.count_of_bnk[i]++;
				count++;
				continue;
			}
			i++;
		}
		if (tmp != 0)
		{
			sum = sum - tmp;;
			if (count == 40)
				deposit.status = 2;//лимит по купюрам
			else
				deposit.status = 3;//полные картриджи
		}
		deposit.the_wh_am = sum;
		user.account = user.account + sum;
		upd_acc();
		return deposit;
	}
};
processing_center ATM::clients;
void check_pin(ATM& tmp)
{
	
	int pin;
	for (int flag = 0; flag == 0;)
	{
		cout << "Input your PIN, please!" << endl;
		cin >> pin;
		if (!tmp.enter_the_pin(pin))
		{
			cout << "Incorrect PIN, remained attempts: " << 3 - tmp.GetUser().wrong_attempts << endl;
			tmp.check_ban_user();
			if (tmp.Get_user_status())
				throw 1;
		}
		else if (tmp.enter_the_pin(pin))
			flag = 1;
		cin.clear();
		clear_c();
	}
}
void ATM_menu()
{
	ATM example;
	try 
	{
		example.add_client("Paul", 1000000000, 3467, "0012");
		example.add_client("Bob", 54000, 2234, "1200");
		example.add_client("Alex", 1000, 2908, "2200");
	}
	catch (int excep)
	{
		if (excep == 4)
		{
			cout << "DB_ERR#4: Invalid card_num!" << endl;
			return;
		}
		if (excep == 5)
		{
			cout << "DB_ERR#5: Invalid pin!" << endl;
			return;
		}
	}
	int choice;
start:
	string card = "";
	for (int flag = 0; flag == 0;)
	{
		cout << "Insert your card, please!" << endl;
		cin >> card;
		if (card.size() == 4)
			flag = 1;
		else
		{
			cout << "Incorrect card number!"<<endl;	
		}	
		clear_c();
	}
	try 
	{
		example.accept_card(card);
	}
	catch (int excep)
	{
		if (excep == 1)
		{
			cout << "ATM_ERR#1:Your card is banned!" << endl;
			clear_c();
			goto start;
		}
		if (excep == 2)
			cout << "ATM_ERR#2: There is no card in ATM!" << endl;
		if (excep == 3)
		{
			cout << "ATM_ERR#3: Card isn't found!" << endl;
			clear_c();
			goto start;
		}
	}
	do
	{	
		try
		{
			int choice;
			for (int flag = 0; flag == 0;)
			{
				cout << "Hello, " << example.GetUser().full_name << endl;
				cout << "ATM options:" << endl << "1.Print my account" << endl << "2.Withdraw cash" << endl << "3.Put cash" << endl << "4.Exit" << endl;
				cin >> choice;
				if (choice >= 1 && choice <= 4)
					flag = 1;
				else
				{
					cout << "Incorrect input, try again!" << endl;
					clear_c();
				}
			}
			if (choice == 1)
			{
				clear_c();
				check_pin(example);
				ofstream tmp;
				tmp.open("account_status.txt");
				if (!tmp.is_open())
					throw 6;
				tmp << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;;
				tmp << "card account statement: " << example.GetUser().card_number << endl;
				tmp << "Full name: " << example.GetUser().full_name << endl;
				tmp << "Account: " << example.GetUser().account << "$"<<endl;
				tmp << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;;
				tmp << "Always your 'FI-1 Bank'!" << endl;
				tmp.close();
				cout << "Take your account status!" << endl;
				clear_c();
			}
			else if (choice == 2)
			{
				clear_c();
				check_pin(example);
				int sum;
				for (int flag = 0; flag == 0;)
				{
					cout << "How much money do you want to withdraw? The amount must be a multiple of one hundred.The amount must not exceed 200,000\nIf you want to exit - enter '1'" << endl;
					cin >> sum;
					if (sum == 1)
						throw 9;
					if (sum > 200000)
					{
						cout << "The amount must not exceed 200,000!\nIf you want to exit - enter '1'" << endl;
						clear_c();
					}
					else
					{
						if (sum % 100 != 0)
						{
							cout << "The amount must be a multiple of one hundred.\nIf you want to exit - enter '1'" << endl;
							clear_c();
						}
						else
							flag = 1;
					}
				}
				output tmp;
				tmp = example.wdr_cash(sum);
				if (tmp.status == 2)
					cout << "Could not withdraw the entire amount: the banknote limit has been reached (40)!" << endl;
				else if (tmp.status == 3)
					cout << "It was not possible to withdraw the entire amount: the banknote cartridge is empty!" << endl;
				cout << "money withdrawn " << tmp.the_wh_am<< "\nCount of 5000 banknotes " << tmp.count_of_bnk[0] << "\nCount of 2000 banknotes " << tmp.count_of_bnk[1] << "\nCount of 1000 banknotes " << tmp.count_of_bnk[2] << "\nCount of 500 banknotes " << tmp.count_of_bnk[3] << "\nCount of 200 banknotes " << tmp.count_of_bnk[4] << "\nCount of 100 banknotes " << tmp.count_of_bnk[5] << endl;
				system("pause");
				clear_c();
			}
			else if (choice == 3)
			{
				int sum;
				for (int flag = 0; flag == 0;)
				{
					cout << "How much money do you want to put? The amount must be a multiple of one hundred.The amount must not exceed 200,000\nIf you want to exit - enter '1'" << endl;
					cin >> sum;
					if (sum == 1)
						throw 9;
					if (sum > 200000)
					{
						cout << "The amount must not exceed 200,000!\nIf you want to exit - enter '1'" << endl;
						clear_c();
					}	
					else
					{
						if (sum % 100 != 0)
						{
							cout << "The amount must be a multiple of one hundred.\nIf you want to exit - enter '1'" << endl;
							clear_c();
						}
						else
							flag = 1;
					}
				}
				output tmp;
				tmp = example.put_cash(sum);
				if (tmp.status == 2)
					cout << "Could not put the entire amount: the banknote limit has been reached (40)!" << endl;
				else if (tmp.status == 3)
					cout << "It was not possible to put the entire amount: the banknote cartridge is full!" << endl;
				cout << "allotted money " << tmp.the_wh_am << "\nCount of 5000 banknotes " << tmp.count_of_bnk[0] << "\nCount of 2000 banknotes " << tmp.count_of_bnk[1] << "\nCount of 1000 banknotes " << tmp.count_of_bnk[2] << "\nCount of 500 banknotes " << tmp.count_of_bnk[3] << "\nCount of 200 banknotes " << tmp.count_of_bnk[4] << "\nCount of 100 banknotes " << tmp.count_of_bnk[5] << endl;
				system("pause");
				clear_c();
			}
			else if (choice == 4)
				;
		}
		catch (int excep)
		{
			if (excep == 1)
			{
				cout << "ATM_ERR#1:Your card is banned!" << endl;
				clear_c();
				goto start;
			}
			if (excep == 2)
			{
				cout << "ATM_ERR#2: There is no card in ATM!" << endl;
				clear_c();
			}
			if (excep == 3)
			{
				cout << "ATM_ERR#3: Card isn't found!" << endl;
				clear_c();
				goto start;
			}
			if (excep == 6)
			{
				cout << "DB_ERR#6: The receipt tape has run out!" << endl;
				clear_c();
			}
			if (excep == 7)
			{
				cout << "DB_ERR#7: No money in account!" << endl;
				clear_c();
			}
			if (excep == 8)
			{
				cout << "ATM_ERR#8: Сartridge is empty" << endl;
				clear_c();
				return;//банкомат отключается и ждет, пока его пополнят
			}
			if (excep == 9)
				;
		}
		for (int flag = 0; flag == 0;)
		{
			cout << "Would you like to countinue work?\n1.Yes\n2.No" << endl;
			cin >> choice;
			if (choice != 1 && choice != 2 && choice != 1111)
			{
				cout << "Incorrect input!" << endl;
				clear_c();
			}
			if (choice == 1111)
				return;
			else if (choice == 2)
			{
				example.card_off();
				goto start;
			}
			flag = 1;
			clear_c();
		}
	} while (choice == 1);
}
int main()
{
	ATM_menu();
	system("Pause");
}