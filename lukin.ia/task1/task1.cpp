#include <iostream>
#include <cmath>
using namespace std;

struct getter_time
{
	int hours;
	int minutes;
	int seconds;
};
class Time
{
	int hours;
	int minutes;
	int seconds;
	int Total(int hrst, int mntst, int scndst) 
	{
		return hrst * 3600 + mntst * 60 + scndst;
	}
		
	void correct(int& hrs, int& mnts, int& scnds)
	{
		int total = Total(hrs, mnts, scnds);
		int count = total / 86400;
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
	void SetTime(int hours_, int minutes_, int seconds_)
	{
		if (hours_ >= 0 && minutes_ >= 0 && seconds_ >= 0)
		{
			hours = hours_;
			minutes = minutes_;
			seconds = seconds_;
			correct(hours, minutes, seconds);
		}
		else
			cout << "Incorrect values!" << endl;
	}
	void PrintTime()
	{
		cout << "Time is: " << hours << ":" << minutes << ":" << seconds << endl;
	}
	void count_difference(int hours_d, int minutes_d, int seconds_d)
	{
		int total_ = Total(hours_d, minutes_d, seconds_d);
		int total = hours * 3600 + minutes * 60 + seconds;
		int difference = abs(total - total_);
		int hoursd = difference / 3600;
		int minutesd = (difference - hoursd * 3600) / 60;
		int secondsd = difference - hoursd * 3600 - minutesd * 60;
		correct(hoursd, minutesd, secondsd);
		cout << "Difference is " << hoursd << ":" << minutesd << ":" << secondsd << endl;
	}
	void shift_time_up(int hours_su, int minutes_su, int seconds_su)
	{
		int total_ = Total(hours_su, minutes_su, seconds_su);
		int total = hours * 3600 + minutes * 60 + seconds;
		int result = total + total_;
		int hourss = result / 3600;
		int minutess = (result - hourss * 3600) / 60;
		int secondss = result - hourss * 3600 - minutess * 60;
		hours = hourss;
		minutes = minutess;
		seconds = secondss;
		correct(hours, minutes, seconds);
	}
	void shift_time_down(int hours_sd, int minutes_sd, int seconds_sd)
	{
		int result;
		int total_ = Total(hours_sd, minutes_sd, seconds_sd);
		int total = Total(hours, minutes, seconds);
		int pre_result = total - total_;
		if (pre_result >= 0)
			result = pre_result;
		else if (pre_result < 0)
		{
			result = 86400 - (abs(pre_result) % 86400);
		}
		int hourss = result / 3600;
		int minutess = (result - hourss * 3600) / 60;
		int secondss = result - hourss * 3600 - minutess * 60;
		hours = hourss;
		minutes = minutess;
		seconds = secondss;
		correct(hours, minutes, seconds);
	}
	Time()
	{
		hours = 0;
		minutes = 0;
		seconds = 0;
	}
	Time(int hours_, int minutes_, int seconds_)
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
	example1.SetTime(14, 56, 30);//тест сеттера
	example1.PrintTime();
	cout << endl << endl;
	getter_time example;
	example = example1.GetTime();
	cout << example.hours << ":" << example.minutes << ":" << example.seconds << endl<<endl<<endl;//тест геттера
	example1.count_difference(15, 0, 0);//тест вычисления разницы
	cout << endl << endl;
	example1.count_difference(14, 0, 23);
	cout << endl << endl;
	example1.shift_time_down(0, 26, 4);//тест на сдвиг
	example1.PrintTime();
	cout << endl << endl;
	example1.shift_time_up(3, 36, 35);
	example1.PrintTime();
	cout << endl << endl;
	example1.shift_time_up(7, 2, 30);//тест на новый день №1
	example1.PrintTime();
	cout << endl << endl;
	example1.shift_time_down(3, 5, 5);//тест на новый день №2
	example1.PrintTime();
	cout << endl << endl;
	example1.SetTime(0, 0, 0);//тест сеттера на большие значения
	example1.SetTime(48, 64, 62);
	example1.PrintTime();
	cout << endl << endl;
	system("pause");
}