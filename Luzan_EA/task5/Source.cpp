#include "Header.h"

using namespace std;


int main() {
	try {
	Date today(21, 4, 2024);
	GRW grw;
	grw.addTrain(1, LASTOCHKA, string("MSK_NN"));
	grw.addTrain(2, LASTOCHKA, string("MSK_NN"));
	grw.addTrain(3, LASTOCHKA, string("MSK_NN"));
	grw.addTrain(4, FIRM, string("MSK_NN"));
	grw.addTrain(5, FAST, string("MSK_NN"));
	grw.addTrain(1, LASTOCHKA, string("NN_MSK"));
	grw.addTrain(2, LASTOCHKA, string("NN_MSK"));
	grw.addTrain(3, LASTOCHKA, string("NN_MSK"));
	grw.addTrain(4, FIRM, string("NN_MSK"));
	grw.addTrain(5, FAST, string("NN_MSK"));
	TicketOffice office(today, grw);
	office.bookTickets();
	}
	catch (char* exp) {
		cout << exp;
	}

	system("pause");
	return 0;
}