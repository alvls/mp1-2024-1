#include <string>
#include <iostream>
#include <windows.h>
using namespace std;

class TextRedactor
{
	int len;
	COORD position;
public:
	TextRedactor()
	{
		len = 15;
		position.X = 0;
		position.Y = 0;
	}
	TextRedactor(COORD input, int len_)
	{
		len = len_;
		position.X = input.X;
		position.Y = input.Y;
	}
	void SetLen(int len_)
	{
		len = len_;
	}
	int GetLen()
	{
		return len;
	}
	void SetPos(COORD input)
	{
		position.X = input.X;
		position.Y = input.Y;
	}
	COORD GetPos()
	{
		COORD tmp;
		tmp.X = position.X;
		tmp.Y = position.Y;
		return tmp;
	}
	void PlaceCursor() 
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { position.X, position.Y });
	}
	string GetString()
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { position.X, position.Y });
		string tmp;
		getline(cin, tmp);
		if (tmp.length() > len)
			throw runtime_error("ERROR:Input string exceeds input length!");//можно просто return, но так есть возможность как то обработать ошибку: вывести на экран, что не так и тд.
		return tmp;
	}
	~TextRedactor() {};
};
void main()
{
	try
	{
		TextRedactor ex;
		ex.SetLen(15);
		ex.SetPos({ 10,4 });
		ex.PlaceCursor();
		COORD getter = ex.GetPos();
		string example = ex.GetString();
		cout << "String length is: " << ex.GetLen() << endl << "Cursor position is: {" << getter.X << "," << getter.Y << "}" << endl << "Your string is: " << example << endl;
		system("pause");
	}
	catch (const runtime_error& exc)
	{
		;
	}
}
