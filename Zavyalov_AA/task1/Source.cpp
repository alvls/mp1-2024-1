#include <iostream>
#include <iomanip>

using namespace std;

class Time {
	unsigned int hours, minutes, seconds;
public:
	Time(unsigned int hours_ = 0, unsigned int minutes_ = 0, unsigned int seconds_ = 0) {
		hours = hours_, minutes = minutes_, seconds = seconds_;
	}
	void setTime(unsigned int hours_, unsigned int minutes_, unsigned int seconds_) {
		hours = hours_, minutes = minutes_, seconds = seconds_;
	}
	Time getTime() {
		Time t;
		t.hours = hours, t.minutes = minutes, t.seconds = seconds;
		return t;
	}
	Time timeDifference(unsigned int subhours, unsigned int subminutes, unsigned int subseconds) {
		Time t;
		unsigned int time = hours * 3600 + minutes * 60 + seconds;
		unsigned int subtime = subhours * 3600 + subminutes * 60 + subseconds;
		unsigned int mintime = min(time, subtime), maxtime = max(time, subtime);
		unsigned int difference1 = maxtime - mintime;
		unsigned int difference2 = mintime + 3600 * 24 - maxtime;
		unsigned int difference = min(difference1, difference2);

		unsigned int dsthours = difference / 3600, dstminutes = (difference % 3600) / 60, dstseconds = difference % 60;
		t.hours = dsthours;
		t.minutes = dstminutes;
		t.seconds = dstseconds;
		return t;
	}
	void shiftTime(unsigned int shifthours, unsigned int shiftminutes, unsigned int shiftseconds, bool add = 1) {
		unsigned int shift = (shifthours % 24) * 3600 + shiftminutes * 60 + shiftseconds;
		unsigned int finaltime;
		if (add) {
			finaltime = hours * 3600 + minutes * 60 + seconds + shift;
		}
		else {
			finaltime = abs((int)(hours * 3600 + minutes * 60 + seconds) - (int)shift);
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

	Time gt = t1.getTime();
	gt.print();

	int hours2, minutes2, seconds2;
	Time dif = t.timeDifference(12, 50, 20);
	dif.print();

	t.shiftTime(12, 45, 54);
	t.print();
	t.shiftTime(12, 45, 54);
	t.print();
	system("pause");
	return 0;
}