#include <iostream>
#include <locale.h>
#include <utility>
#include "atm.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	ProcessingCenter pc1;
	ProcessingCenter *pc1ptr = &pc1;
	ClientInfo ci("Иван", "Семёнов", "Богданович", 104300, "0231");
	
	std::pair<std::string, ClientInfo> clientPairs[10] = {
		std::make_pair("1337", ClientInfo("Иван", "Иванов", "Иванович", 13999000, "1234")),

		std::make_pair("2468", ClientInfo("Мария", "Петрова", "Сергеевна", 5000, "5678")),

		std::make_pair("3579", ClientInfo("Александр", "Сидоров", "Николаевич", 7500, "9012")),

		std::make_pair("4680", ClientInfo("Елена", "Козлова", "Андреевна", 3000, "3456")),

		std::make_pair("5791", ClientInfo("Дмитрий", "Павлов", "Владимирович", 20000, "7890")),

		std::make_pair("6802", ClientInfo("Ольга", "Федорова", "Александровна", 15000, "1357")),

		std::make_pair("7913", ClientInfo("Сергей", "Семенов", "Петрович", 8000, "2468")),

		std::make_pair("8024", ClientInfo("Анна", "Григорьева", "Ивановна", 12000, "3690")),

		std::make_pair("9135", ClientInfo("Павел", "Михайлов", "Алексеевич", 6000, "4826")),

		std::make_pair("0246", ClientInfo("Наталья", "Васильева", "Викторовна", 9500, "5739"))
	};

	pc1ptr->addClient("1336", ci);
	for (int i = 0; i < 10; i++)
		(*pc1ptr).addClient(clientPairs[i].first, clientPairs[i].second);

	ATM atm1(pc1ptr);
	ClientInfo f("Иван", "Семёнов", "Богданович", 100, "0231");
	atm1.insertCard("6802");
	atm1.print();
	vector<int> sf = atm1.getCash(12300);
	for (auto x : sf) {
		cout << x << " ";
	}
	cout << endl;
	atm1.print();
	vector<int> v = { 1,2,4,4,10,19 }; // 19 * 5000 + 10 * 2000 + 4 * 1000 + 4 * 500 + 2 * 200 + 1 * 100 = 121500
	atm1.insertCash(v);
	atm1.print();
	cout << atm1.checkPin("1234") << endl;
	cout << atm1.checkPin("1357") << " " << atm1.checkPin("1233") << endl;
	atm1.returnCard();
	atm1.insertCard("1337");
	try {
		atm1.getCash(200000 - 100);
	}
	catch (const char* s) {
		cout << s << endl;
	}
	try {
		cout << atm1.checkPin("1233") << " " << atm1.checkPin("1233") << " " << atm1.checkPin("1233");
	}
	catch (const char* s) {
		cout << s << endl;
	}
	system("pause");
	return 0;
}