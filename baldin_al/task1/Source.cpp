#include <iostream>
#include <string>
#include <cmath>

using namespace std;

typedef unsigned int ui;

class Time
{
private:
	ui hrs;
	ui min;
	ui sec;

	int Is_Ok(ui h, ui m, ui s)
	{
		return (h > 23 || m > 59 || s > 59);
	}

public:
	Time(ui hrs_ = 0, ui min_ = 0, ui sec_ = 0)
	{
		if (Is_Ok(hrs_, min_, sec_))
		{
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

	void setTime(ui h, ui m, ui s)
	{
		if (Is_Ok(h, m, s))
		{
			hrs = 0;
			min = 0;
			sec = 0;
		}
		else
		{
			hrs = h;
			min = m;
			sec = s;
		}
	}

	Time getTime()
	{
		Time t;
		t.hrs = hrs;
		t.min = min;
		t.sec = sec;
		return t;
	}

	void print()
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

	Time getDiff(const Time& t)
	{
		ui s1 = (hrs * 3600 + min * 60 + sec);
		ui s2 = (t.hrs * 3600 + t.min * 60 + t.sec);
		ui d = std::min(abs((int)(s1 - s2)), 24 * 3600 - abs((int)(s1 - s2)));
		ui h = d / 3600;
		ui m = (d - h * 3600) / 60;
		ui s = d - h * 3600 - m * 60;
		return Time(h, m, s);
	}

	void shiftTime(ui h, ui m, ui s, bool sign = 1)
	{
		int shift = (h % 24) * 3600 + m * 60 + s;
		int t;
		if (sign)
		{
			t = hrs * 3600 + min * 60 + sec + shift;
		}
		else
		{
			t = hrs * 3600 + min * 60 + sec - shift;
			if (t < 0)
				t += 24 * 3600;
		}
		hrs = (t / 3600) % 24;
		min = t % 3600 / 60;
		sec = t % 60;
	}
};

int main()
{
	//examples
	Time t1, t2, t3(24, 10, 23);

	Time t4 = t3.getTime();
	t4.print();
	t1.setTime(1, 2, 3);
	t1.print();
	t2.setTime(12, 57, 39);
	t2.print();
	Time diff1 = t1.getDiff(t2); 
	diff1.print();
	t1.shiftTime(25, 74, 120);
	t1.print();
	t2.shiftTime(13, 36, 43, 0);
	t2.print();
	Time diff2 = t2.getDiff(t1);
	diff2.print();

	system("pause");
}