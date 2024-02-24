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
	void shiftTime(int shifthours, int shiftminutes, int shiftseconds, bool add = 1) {
		int shift = (shifthours % 24) * 3600 + shiftminutes * 60 + shiftseconds;
		int finaltime;
		if (add) {
			finaltime = abs(hours * 3600 + minutes * 60 + seconds + shift);
		}
		else {
			finaltime = abs(hours * 3600 + minutes * 60 + seconds - shift);
		}
		hours = (finaltime / 3600) % 24, minutes = finaltime % 3600 / 60, seconds = finaltime % 60;
	}
	void print() {
		cout << setw(2) << setfill('0') << hours << ":" << setw(2) << setfill('0') << minutes << ":" << setw(2) << setfill('0') << seconds << endl;
	}
};

int main() {
	// examples of methods' usage, initializaton values must be in range from 00:00:00 to 23:59:59
	Time t, t1(13, 37, 25);

	int hours1, minutes1, seconds1;
	t.getTime(hours1, minutes1, seconds1);
	cout << hours1 << ":" << minutes1 << ":" << seconds1 << endl;
	t.print();

	int hours2, minutes2, seconds2;
	t.timeDifference(12, 50, 20, hours2, minutes2, seconds2);
	cout << hours2 << ":" << minutes2 << ":" << seconds2 << endl;

	t.shiftTime(23, 19, 30);
	t.timeDifference(6, 41, 59, hours2, minutes2, seconds2);
	cout << hours2 << ":" << minutes2 << ":" << seconds2 << endl;

	cout << "t1 initial time: "; t1.print();
	t1.setTime(10, 33, 20);
	t1.timeDifference(12, 36, 24, hours2, minutes2, seconds2);
	cout << hours2 << ":" << minutes2 << ":" << seconds2 << endl;

	t.shiftTime(15, 21, 28, 0);
	t.print();
	system("pause");
	return 0;
}