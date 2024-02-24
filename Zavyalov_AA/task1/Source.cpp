#include <iostream>
#include <iomanip>

using namespace std;

class Time {
	int hours, minutes, seconds;
public:
	Time(int hours_ = 0, int minutes_ = 0, int seconds_ = 0) {
		hours = hours_, minutes = minutes_, seconds = seconds_;
	}
	void setTime(int hours_, int minutes_, int seconds_) {
		hours = hours_, minutes = minutes_, seconds = seconds_;
	}
	void getTime(int& hours_, int& minutes_, int& seconds_) {
		hours_ = hours, minutes_ = minutes, seconds_ = seconds;
	}
	void timeDifference(int subhours, int subminutes, int subseconds, int &dsthours, int &dstminutes, int &dstseconds) {
		int difference = abs(hours * 3600 + minutes * 60 + seconds - subhours * 3600 - subminutes * 60 - subseconds);
		dsthours = difference / 3600, dstminutes = (difference % 3600) / 60, dstseconds = difference % 60;
	}
	void shiftTime(int shifthours, int shiftminutes, int shiftseconds) {
		int shift = shifthours * 3600 + shiftminutes * 60 + shiftseconds;
		int finaltime = abs(hours * 3600 + minutes * 60 + seconds + shift);
		hours = (finaltime / 3600) % 24, minutes = finaltime % 3600 / 60, seconds = finaltime % 60;
	}
	void print() {
		cout << setw(2) << setfill('0') << hours << ":" << setw(2) << setfill('0') << minutes << ":" << setw(2) << setfill('0') << seconds << endl;
		std::setw(0); std::setfill(' ');
	}
};

int main() {  // TODO вывод на консоль, проверить 4)
	// tests
	Time t;
	int hours1, minutes1, seconds1;
	t.getTime(hours1, minutes1, seconds1);
	cout << hours1 << ":" << minutes1 << ":" << seconds1 << endl;
	int hours2, minutes2, seconds2;
	t.timeDifference(12, 50, 20, hours2, minutes2, seconds2);
	cout << hours2 << ":" << minutes2 << ":" << seconds2 << endl;

	t.shiftTime(12, 19, 30);
	t.print();
	/*
	t.getTime(hours1, minutes1, seconds1);
	cout << hours1 << ":" << minutes1 << ":" << seconds1 << endl;*/
	system("pause");
	return 0;
}