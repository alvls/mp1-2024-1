#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Time
{
private:
	int hrs;
	int min;
	int sec;

	int Is_Ok(int h, int m, int s)
	{
		return (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59);
	}

public:
	Time(int hrs_ = 0, int min_ = 0, int sec_ = 0)
	{
		if (Is_Ok(hrs_, min_, sec_))
		{
			cout << "Invalid time format. Time was automatically set to 00:00:00" << '\n';
			hrs = 0;
			min = 0;
			sec = 0;
		}
		else
		{
			hrs = hrs_;
			min = min_;
			sec = sec_;
		}
	}

	void setTime(int h, int m, int s)
	{
		if (Is_Ok(h, m, s))
			cout << "Invalid time format. This time cannot be set" << '\n';
		else
		{
			hrs = h;
			min = m;
			sec = s;
		}
	}

	void getTime()
	{
		string t;
		if (hrs < 10)
			t += "0";
		t += to_string(hrs) + ":";

		if (min < 10)
			t += "0";
		t += to_string(min) + ":";

		if (sec < 10)
			t += "0";
		t += to_string(sec);

		cout << t << '\n';
	}

	void getDiff(const Time& t)
	{
		int s1 = (hrs * 3600 + min * 60 + sec);
		int s2 = (t.hrs * 3600 + t.min * 60 + t.sec);
		int d = std::min(abs(s1 - s2), 24 * 3600 - abs(s1 - s2));
		int h = d / 3600;
		int m = (d - h * 3600) / 60;
		int s = d - h * 3600 - m * 60;
		cout << "The difference between the times is " << h << " hour(s) " << m << " minute(s) and " << s << " second(s) " << '\n';
	}

	void shiftTime(int h, int m, int s)
	{
		sec += s;
		while (sec > 59 || sec < 0)
		{
			if (sec < 0)
			{
				sec += 60;
				min--;
			}
			else
			{
				sec -= 60;
				min++;
			}
		}
		min += m;
		while (min > 59 || min < 0)
		{
			if (min < 0)
			{
				min += 60;
				hrs--;
			}
			else
			{
				min -= 60;
				hrs++;
			}
		}
		hrs += h;
		while (hrs > 23 || hrs < 0)
		{
			if (hrs < 0)
				hrs += 24;
			else
				hrs -= 24;
		}
	}

};

int main()
{
	//пример
	Time t1, t2, t3(24, 10, 23), t4;

	t3.getTime();
	t4.setTime(17, 23, -1);
	t1.setTime(1, 2, 3);
	t1.getTime();
	t2.setTime(12, 57, 39);
	t2.getTime();
	t1.getDiff(t2);
	t1.shiftTime(25, 74, 120);
	t1.getTime();
	t2.shiftTime(-13, -36, -43);
	t2.getTime();
	t2.getDiff(t1);

	system("pause");
}