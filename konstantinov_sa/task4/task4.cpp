#include<iostream>
#include<string>
#include <fstream>
using namespace std;

class Datetime {
public:
    int hour;
    int day;
    int month;
    int year;

    Datetime(int time = 0, int aday = 1, int amonth = 1, int ayear = 2000) {
        hour = time;
        day = aday;
        month = amonth;
        year = ayear;
    }

    bool operator>=(const Datetime& other) const {
        if (year > other.year) {
            return true;
        }
        else if (year == other.year) {
            if (month > other.month) {
                return true;
            }
            else if (month == other.month) {
                if (day > other.day) {
                    return true;
                }
                else if (day == other.day) {
                    if (hour >= other.hour) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool operator<=(const Datetime& other) const {
        if (year < other.year) {
            return true;
        }
        else if (year == other.year) {
            if (month < other.month) {
                return true;
            }
            else if (month == other.month) {
                if (day < other.day) {
                    return true;
                }
                else if (day == other.day) {
                    if (hour <= other.hour) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool operator==(const Datetime& other) const {
        return (year == other.year && month == other.month && day == other.day && hour == other.hour);
    }
};




int main() {
	setlocale(LC_ALL, "rus");

	//system("pause");
}