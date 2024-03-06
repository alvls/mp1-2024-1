#include <iostream>
#include <math.h>
using namespace std;

struct getter_time
{
	unsigned int hours;
	unsigned int minutes;
	unsigned int seconds;
};
struct getter_dif
{
	unsigned int hours;
	unsigned int minutes;
	unsigned int seconds;
};

class Time
{
	unsigned int hours;
	unsigned int minutes;
	unsigned int seconds;
	unsigned int Total(unsigned int hrst, unsigned int mntst, unsigned int scndst)
	{
		return hrst * 3600 + mntst * 60 + scndst;
	}
		
	void correct(unsigned int& hrs, unsigned int& mnts, unsigned int& scnds)
	{
		unsigned int total = Total(hrs, mnts, scnds);
		unsigned int count = total / 86400;
		if (count == 0)
			return;
		else
		{
			total = total - 86400 * count;
			hrs = total / 3600;
			mnts = (total - hrs * 3600) / 60;
			scnds = total - hrs * 3600 - mnts * 60;
		}
	}
public:
	getter_time GetTime()//я больше ничего не придумал, сначала хотел массивом, но структурой мне больше понравилось
	{
		getter_time A;
		A.hours = hours;
		A.minutes = minutes;
		A.seconds = seconds;
		return A;
	}
	void SetTime(unsigned int hours_, unsigned int minutes_, unsigned int seconds_)
	{
		if (hours_<=23 && minutes_ <=59 && seconds_ <= 59)
		{
			hours = hours_;
			minutes = minutes_;
			seconds = seconds_;
			correct(hours, minutes, seconds);
		}
		else
			return;
	}
	void PrintTime()
	{
		cout << "Time is: " << hours << ":" << minutes << ":" << seconds << endl;
	}
	getter_dif count_difference(unsigned int hours_d, unsigned int minutes_d, unsigned int seconds_d)
	{
		int total_ = Total(hours_d, minutes_d, seconds_d);
		int total = Total(hours, minutes, seconds);
		unsigned int difference = abs(total - total_);
		unsigned int hoursd = difference / 3600;
		unsigned int minutesd = (difference - hoursd * 3600) / 60;
		unsigned int secondsd = difference - hoursd * 3600 - minutesd * 60;
		correct(hoursd, minutesd, secondsd);
		getter_dif tmp;
		tmp.hours = hoursd;
		tmp.minutes = minutesd;
		tmp.seconds = secondsd;
		return tmp;
	}
	void shift_time(unsigned int hours_s, unsigned int minutes_s, unsigned int seconds_s, unsigned int mode)
	{
		if (mode == 1)
		{
			unsigned int total_ = Total(hours_s, minutes_s, seconds_s);
			unsigned int total = Total(hours, minutes, seconds);
			unsigned int result = total + total_;
			unsigned int hourss = result / 3600;
			unsigned int minutess = (result - hourss * 3600) / 60;
			unsigned int secondss = result - hourss * 3600 - minutess * 60;
			hours = hourss;
			minutes = minutess;
			seconds = secondss;
			correct(hours, minutes, seconds);
		}
		else if (mode == 0)
		{
			unsigned int result;
			unsigned int total_ = Total(hours_s, minutes_s, seconds_s);
			unsigned int total = Total(hours, minutes, seconds);
			int pre_result = total - total_;
			if (pre_result >= 0)
				result = pre_result;
			else if (pre_result < 0)
			{
				result = 86400 - (abs(pre_result) % 86400);
			}
			unsigned int hourss = result / 3600;
			unsigned int minutess = (result - hourss * 3600) / 60;
			unsigned int secondss = result - hourss * 3600 - minutess * 60;
			hours = hourss;
			minutes = minutess;
			seconds = secondss;
			correct(hours, minutes, seconds);
		}
		else
			return;
	}
	Time()
	{
		hours = 0;
		minutes = 0;
		seconds = 0;
	}
	Time(unsigned int hours_, unsigned int minutes_, unsigned int seconds_)
	{
		hours = hours_;
		minutes = minutes_;
		seconds = seconds_;
		correct(hours_, minutes_, seconds_);
	}
	Time(const Time& copy)
	{
		hours = copy.hours;
		minutes = copy.minutes;
		seconds = copy.seconds;
	}
};

int main()
{
	Time example1, example2(13, 37, 00), example3(example2);//тест конструкторов
	example1.PrintTime();
	example2.PrintTime();
	example3.PrintTime();
	cout << endl << endl;
	example1.SetTime(1, 56, 30);//тест сеттера
	example1.PrintTime();
	cout << endl << endl;
	getter_time example;
	example = example1.GetTime();
	cout << example.hours << ":" << example.minutes << ":" << example.seconds << endl<<endl<<endl;//тест геттера
	//тест вычисления разницы
	cout << endl << endl;
	getter_dif example_d;
	example_d = example1.count_difference(14, 0, 23);
	cout << example_d.hours << ":" << example_d.minutes << ":" << example_d.seconds << endl << endl << endl;
	cout << endl << endl;
	example1.shift_time(0, 26, 4,0);//тест на сдвиг
	example1.PrintTime();
	cout << endl << endl;
	example1.shift_time(3, 36, 35, 1);
	example1.PrintTime();
	cout << endl << endl;
	example1.shift_time(7, 2, 30, 0);//тест на новый день №1
	example1.PrintTime();
	cout << endl << endl;
	example1.shift_time(3, 5, 5,1);//тест на новый день №2
	example1.PrintTime();
	cout << endl << endl;
	example1.SetTime(0, 0, 0);//тест сеттера на большие значения
	example1.SetTime(48, 64, 62);
	example1.PrintTime();
	cout << endl << endl;
	system("pause");
}