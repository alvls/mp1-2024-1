#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;


template <class T>
T* copyPtr(size_t size, T* source, T* destination) {
	destination = new T[size];
	for (size_t i = 0; i < size; i++)
		destination[i] = source[i];
	return destination;
}

const unsigned AVAIBLE_BOOK_PERIOD = 30;

const unsigned cost[3][4] = {
	{2, 0, 0, 0 },
	{0, 5, 3, 1},
	{0, 6, 4, 1}
};
/////////////////////////////////////////////////////////////////////////////////

enum KOLVO_OF_WAGONS {
	LASTOCHKA_WAGONS = 8,
	FAST_WAGONS_SV = 0, FAST_WAGONS_CP = 4, FAST_WAGONS_PL = 8,
	FIRM_WAGONS_SV = 2, FIRM_WAGONS_CP = 6, FIRM_WAGONS_PL = 4
};

const unsigned WAGONS_NUM = 4;
const string WAGONS[4] = { "LASTOCHKA WAGON", "SV", "Coupe", "platzkart" };

enum WAGON_TYPES {
	LASTOCHKA_WAGON = 0, SV_WAGON = 1, CP_WAGON = 2, PL_WAGON = 3
};


/////////////////////////////////////////////////////////////////////////////////

enum SEATS_NUM {
	SEATS_LASTOCHKA = 100,
	SEATS_SV = 18, SEATS_CP = 18 * 2, SEATS_PL = 27 * 2
};

/////////////////////////////////////////////////////////////////////////////////

const unsigned TRAINS_NUM = 3;
const string TRAINS[3] = { "LASTOCHKA", "FIRM", "FAST" };

//ORDER MUST BE AS IN STRING TRAINS[]
enum TRAIN_TYPES {
	LASTOCHKA = 0, FIRM = 1, FAST = 2
};

/////////////////////////////////////////////////////////////////////////////////

enum MONTHS { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };

class Date {
private:
	unsigned day, month, year;
	unsigned days_in_month; 
	string str_date;
public:

	Date() = default;

	Date(unsigned day_, unsigned month_, unsigned year_) {
		day = day_;
		month = month_;
		year = year_;
		str_date = to_string(day) + '.' + to_string(month) + '.' + to_string(year);
		setDaysInMonth();
	}

	Date(Date const& obj) {
		this->operator=(obj);
	}

	bool checkData() {
		if ((0 < year) && (0 < month) && (month < 13) && (0 < day) && (day <= days_in_month))
			return true;
		return false;
		// если неправильно выставлен мес€ц, то условие дл€ day имеет вид 0 < day <= 0 --> false
	}

	void setDaysInMonth() {
		switch (month) {
		case JAN: case MAR: case MAY:
		case JUL: case AUG: case OCT: case DEC:
			days_in_month = 31;
			break;
		case APR: case JUN: case SEP: case NOV:
			days_in_month = 30;
			break;
		case FEB:
			days_in_month = 29;
			break;
		default:
			days_in_month = 0;
			break;
		}
	}

	string getStringDate() {
		return str_date;
	}

	Date operator+(unsigned days_after) {
		Date obj(*this);
		obj.day += days_after;
		while (obj.day > obj.days_in_month) {

			obj.month++;
			obj.day -= days_in_month;
			obj.setDaysInMonth();
			if (obj.month == 13) { obj.month = JAN; obj.year++; obj.setDaysInMonth(); }
		}
		obj.str_date = to_string(obj.day) + '.' + to_string(obj.month) + '.' + to_string(obj.year);
		return obj;
	}

	bool operator<(const Date& right_h) {
		if (year < right_h.year)
			return true;
		if (year > right_h.year)
			return false;
		if (month < right_h.month)
			return true;
		if (month > right_h.month)
			return false;
		if (day < right_h.day)
			return true;
		return false;
	}

	bool operator>(const Date& right_h) {
		if (year < right_h.year)
			return false;
		if (year > right_h.year)
			return true;
		if (month < right_h.month)
			return false;
		if (month > right_h.month)
			return true;
		if (day < right_h.day)
			return false;
		return false;
	}

	Date& operator=(const Date& right_h) {
		day = right_h.day;
		month = right_h.month;
		year = right_h.year;
		days_in_month = right_h.days_in_month;
		str_date = right_h.str_date;
		return (*this);
	}
};

class Ticket {
public:
	Date date;
	unsigned train_num, wagon_num, place_num;
	string fio;
	string direction;
	unsigned cost;

	Ticket() = default;

	Ticket(Date date_, unsigned train_num_, unsigned wagon_num_, unsigned place_num_, string fio_, string direction_) :
		train_num(train_num_), wagon_num(wagon_num_), place_num(place_num_), fio(fio_), direction(direction_) { }

	void printTicket() {
		cout << "DATE: " << date.getStringDate() << endl;
		cout << fio << endl;
		cout << "FROM - WHERE: " << direction << endl;
		cout << "TRAIN ID: " << train_num << endl;
		cout << "WAGON ID: " << wagon_num << endl;
		cout << "YOUR PLACE: " << place_num << endl;
		cout << "\n" << "cost: " << cost << " AD" << endl;
	}

	unsigned getCost() {
		return cost;
	}
};

class Wagon {
private:
	unsigned num;
	unsigned type;
	unsigned free_count;
	unsigned max_places;
public:
	Wagon() = default;

	Wagon(unsigned num, unsigned type, unsigned free_count, unsigned max_places)
		: num(num), type(type), free_count(free_count), max_places(max_places) {}

	Wagon& operator= (const Wagon& wg) {
		num = wg.num;
		type = wg.type;
		free_count = wg.free_count;
		max_places = wg.max_places;
		return *this;
	}

	unsigned getType() {
		return type;
	}

	Ticket* bookPlaces(unsigned places_num) {
		Ticket* tickets = NULL;
		if ((free_count >= places_num) && (free_count != 0)) {
			Ticket* tickets = new Ticket[places_num];
			for (int j = 0; j < places_num; j++) {
				tickets[j].place_num = max_places - free_count + 1;
				tickets[j].wagon_num = num;
				free_count--;
			}
			return tickets;
		}
		return tickets;
	}

};

class Train {
private:
	unsigned train_num, type;
	string direction;
	Wagon* wagon_list;
	unsigned wagon_list_size;
public:

	unsigned getSize() {
		return wagon_list_size;
	}

	Train() : wagon_list(NULL) {};

	// нужен дл€ push_back в вектор в классе √∆ƒ
	Train(const Train& tr) : wagon_list(NULL) {
		train_num = tr.train_num; type = tr.type; direction = tr.direction;
		wagon_list_size = tr.wagon_list_size;
		wagon_list = copyPtr(wagon_list_size, tr.wagon_list, wagon_list);
	}

	Train(unsigned num, unsigned typ, string dir) : type(typ), train_num(num), direction(dir) {
		unsigned wagon_type = 0;
		switch (type) {
		case LASTOCHKA: {
			wagon_list = new Wagon[LASTOCHKA_WAGONS];
			wagon_type = LASTOCHKA_WAGON;
			for (int i = 0; i < LASTOCHKA_WAGONS; i++) {
				Wagon wg(i, wagon_type, SEATS_LASTOCHKA, SEATS_LASTOCHKA);
				wagon_list[i] = wg;
			}
			wagon_list_size = LASTOCHKA_WAGONS;
			break;
		}
		case FIRM: {
			wagon_list = new Wagon[FIRM_WAGONS_CP + FIRM_WAGONS_PL + FIRM_WAGONS_SV];
			int i = 0;

			wagon_type = SV_WAGON;
			for (; i < FIRM_WAGONS_SV; i++) {
				Wagon wg(i, wagon_type, FIRM_WAGONS_SV, FIRM_WAGONS_SV);
				wagon_list[i] = wg;
			}

			wagon_type = CP_WAGON;
			for (; i < FIRM_WAGONS_SV + FIRM_WAGONS_CP; i++) {
				Wagon wg(i, wagon_type, FIRM_WAGONS_CP, FIRM_WAGONS_CP);
				wagon_list[i] = wg;
			}

			wagon_type = PL_WAGON;
			for (; i < FIRM_WAGONS_SV + FIRM_WAGONS_CP + FIRM_WAGONS_PL; i++) {
				Wagon wg(i, wagon_type, FIRM_WAGONS_PL, FIRM_WAGONS_PL);
				wagon_list[i] = wg;
			}
			wagon_list_size = FIRM_WAGONS_SV + FIRM_WAGONS_CP + FIRM_WAGONS_PL;
			break;
		}
		case FAST: {
			wagon_list = new Wagon[FAST_WAGONS_CP + FAST_WAGONS_PL];
			int i = 0;

			wagon_type = CP_WAGON;
			for (; i < FAST_WAGONS_CP; i++) {
				Wagon wg(i, wagon_type, FAST_WAGONS_CP, FAST_WAGONS_CP);
				wagon_list[i] = wg;
			}

			wagon_type = PL_WAGON;
			for (; i < FAST_WAGONS_CP + FAST_WAGONS_PL; i++) {
				Wagon wg(i, wagon_type, FAST_WAGONS_PL, FAST_WAGONS_PL);
				wagon_list[i] = wg;
			}
			wagon_list_size = FAST_WAGONS_CP + FAST_WAGONS_PL;
			break;
		}
		default: {
			throw "Incorrect train type";
		}
		}

	}

	~Train() {
		delete[] wagon_list;
	}

	unsigned getTrainNum() {
		return train_num;
	}

	unsigned getWagonListSize() {
		return wagon_list_size;
	}

	unsigned getTrainType() {
		return type;
	}

	string getTrainDirection() {
		return direction;
	}

	Ticket* bookPlaces(unsigned places_num, unsigned wagon_type) {
		Ticket* tickets = NULL;
		for (int i = 0; i < wagon_list_size; i++) {
			if (wagon_list[i].getType() == wagon_type) {
				tickets = wagon_list[i].bookPlaces(places_num);
				if (tickets != NULL) { break; }
			}
		}
		if (tickets != NULL) {
			for (int i = 0; i < places_num; i++) {
				tickets[i].direction = direction;
				tickets[i].train_num = train_num;
				tickets[i].cost = cost[type][wagon_type];
			}
		}
		return tickets;
	}

	Train& operator= (const Train& tr) {
		train_num = tr.train_num;
		type = tr.type;
		direction = tr.direction;
		wagon_list_size = tr.wagon_list_size;

		wagon_list = new Wagon[wagon_list_size];
		wagon_list = copyPtr(wagon_list_size, tr.wagon_list, wagon_list);
		return *this;
	}


};

class GRW {
	vector <Ticket> ticket_list;
	vector <Train> train_list;
	unsigned train_list_size;
public:
	GRW() : train_list_size(0), train_list(NULL) {};

	~GRW() {}
	
	void addTrain(unsigned train_num, unsigned type, string direction) {
		if ((direction != string("NN_MSK")) && (direction != string("MSK_NN")))
			throw "Incorrect train direction, while adding the train";
		if ((train_num < 0) || (train_num > 10))
			throw "Incorrect train number, while adding the train";
		if ((type < 0) || (type > 2))
			throw "Incorrect train type, while adding the train";
		Train another_train(train_num, type, direction);
		train_list.push_back(another_train);
		train_list_size++;
	}
	

	void addTicket(const Ticket& another_ticket) {
		// вс€ проверка происходит на кассе
		ticket_list.push_back(another_ticket);
	}

	Ticket* bookTicket(string direction, unsigned train_t, unsigned wagon_t, unsigned places_num, vector <string > fio_s) {
		Ticket* tickets = NULL;
		for (int i = 0; i < train_list_size; i++) {
			if ((train_list[i].getTrainDirection() == direction)) {
				if (train_list[i].getTrainType() == train_t) {
					tickets = train_list[i].bookPlaces(places_num, wagon_t);
					if (tickets != NULL) { break; }
				}
			}
		}
		if (tickets != NULL) {
			for (int i = 0; i < places_num; i++) {
				tickets[i].fio = fio_s[i];
				this->addTicket(tickets[i]);
			}
		}

		return tickets;
	}

};

class TicketOffice
{
private:
	GRW calendar[AVAIBLE_BOOK_PERIOD];
	Date today;


public:
	TicketOffice(Date today_, GRW grw) : today(today_) {
		for (int i = 0; i < AVAIBLE_BOOK_PERIOD; i++) {
			calendar[i] = grw;
		}
	}

	bool bookTickets() {
		bool canceled = false;

		// Date block
		cout << "enter the date in the format DD.MM.YYYY (now avaible from " << today.getStringDate()
			<< " till " << (today + (AVAIBLE_BOOK_PERIOD - 1)).getStringDate() << "): ";
		unsigned day = 100, month = 0, year = 0;
		Date book_day;
		unsigned train_type = UINT_MAX;
		unsigned wagon_type = UINT_MAX;
		unsigned ticket_num = 0;
		unsigned shift = 0;
		string direction = "";

		while (!canceled) { // while cancelled != True
			if (scanf_s("%u.%u.%u", &day, &month, &year) != 3) {
				cout << "Incorrect date format, try again\n";
				cin.ignore(INT_MAX, '\n');
				continue;
			}
			Date tmp(day, month, year);
			book_day = tmp;
			if (!(book_day.checkData())) {
				cout << "Incorrect date, try again\n";
				continue;
			}
			if (book_day < today) {
				cout << "Sorry, we can't go in the past, try again\n";
				cout << "Do you want to cancell? [y/n]: ";
				char tmp = getchar();
				canceled = (tmp == 'y') ? true : false;
				cin.ignore(INT_MAX, '\n');
				continue;
			}
			if (book_day > (today + (AVAIBLE_BOOK_PERIOD - 1))) {
				cout << "Sorry, it's too far in future, try again\n";
				cout << "Do you want to cancell? [y/n]: ";
				canceled = (getchar() == 'y') ? true : false;
				continue;
			}

			for (shift = 0; ((tmp > book_day) || (tmp < book_day)) && (shift != 33); shift++) {
				tmp = tmp + 1;
			}
			if (shift == 33) throw "Incorrect date!!!";

			//booking_block
			//Direction block
			cout << "Where do you want to go? (MSK_NN or NN_MSK): ";
			cin >> direction;
			while ((direction != "MSK_NN") && (direction != "NN_MSK") && (direction != "***")) {
				cout << "Sorry, but we have nosuch trains. Please enter MSK_NN or NN_MSK or cancell your order"
					<< " by printing [***]: ";
				cin >> direction;
			}
			if (direction == "***") {
				canceled = true;
				continue;
			}

			// train block
			cout << "Which train do you want? (Enter the number) \n";
			for (unsigned its11pmtrightnow = 0U; its11pmtrightnow < TRAINS_NUM; its11pmtrightnow++) {
				cout << TRAINS[its11pmtrightnow] << " - " << its11pmtrightnow << endl;
			}
			while ((scanf_s("%u", &train_type) != 1) && (train_type < 0) && (TRAINS_NUM - 1 < train_type)) {
				cout << "Sorry, we don't have such trains. Choose another one \n";
				cin.ignore(INT_MAX, '\n');
			}

			// wagon block
			cout << "Which wagon do you want? (Enter the number)\n";
			unsigned max_wagon = 0, min_wagon = UINT_MAX;
			switch (train_type) {
			case LASTOCHKA:
				cout << WAGONS[LASTOCHKA_WAGON] << " - " << LASTOCHKA_WAGON << endl;
				min_wagon = max_wagon = 0;
				break;
			case FIRM: case FAST:
				cout << WAGONS[SV_WAGON] << " - " << SV_WAGON << endl;
				cout << WAGONS[CP_WAGON] << " - " << CP_WAGON << endl;
				cout << WAGONS[PL_WAGON] << " - " << PL_WAGON << endl;
				max_wagon = 3; min_wagon = 1;
				break;
			default:
				cout << "SOMETHING WENT WRONG\n";
				throw "ERROR IN TicketOffice/bookTickets/wagonblock";
			}
			while ((scanf_s("%u", &wagon_type) != 1) && (wagon_type < min_wagon) && (wagon_type > max_wagon)) {
				cout << "Sorry, we don't have such wagons in your train\n";
				cout << "Do you want to cancell? [y/n]: ";
				canceled = (getchar() == 'y') ? true : false;
				cin.ignore(INT_MAX, '\n');
				continue;
			}

			// Tickets block
			//Num block
			cout << "How many tickets do you need?: ";
			cin >> ticket_num;
			if (ticket_num < 1) {
				canceled = true;
				cout << "You've booked 0 places. Have a nice day";
				continue;
			}

			//fios block !!!! cin lj пробела работает
			vector <string> fio_s;
			fio_s.resize(ticket_num);
			cout << "Please, enter fio of each person: (One persone - one string, use spaces to separate words \n";
			for (int i = 0; i < ticket_num; i++) {
				string tmp_fio;
				cin >> tmp_fio;
				fio_s[i] = tmp_fio;
			}

			//print block
			Ticket* tickets = calendar[shift].bookTicket(direction, train_type, wagon_type, ticket_num, fio_s);
			if (tickets == NULL) {
				cout << "Sorry, but there is no free places for you. Please, try next time";
				return false;
			}

			unsigned sum_cost = 0;
			cout << "Your Tickets: \n\n";
			cout << "-------------------------------------------------------------\n";
			for (int tick = 0; tick < ticket_num; tick++) {
				tickets[tick].date = book_day;
				calendar[shift].addTicket(tickets[tick]);
				tickets[tick].printTicket();
				sum_cost += tickets[tick].getCost();
				cout << "-------------------------------------------------------------\n";
			}

			cout << "It will cost you: " << sum_cost << " Altair Dollars \n\n";
			break;
		}

		if (canceled) { cout << "GoodBye\n\n";  return false; }
		return true;
	}
};