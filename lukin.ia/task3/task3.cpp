#include <string>
#include <iostream>
#include <windows.h>
#include <conio.h>
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
		PlaceCursor();
		string str;
		char ch;
		while (1)
		{
			ch = _getch();
			if (ch == '\r')
			{
				cout << endl;
				return str;
			}
			else if (ch == '\b')
			{
				if (!str.empty())
				{
					cout << "\b \b"; 
					str.pop_back();
				}
			}
			else if (str.size() < len)
			{
				str += ch;
				cout << ch;
			}
		}
		return str;
	}
	~TextRedactor() {};
};
void main()
{
	TextRedactor ex;
	ex.SetLen(15);
	ex.SetPos({ 10,4 });
	ex.PlaceCursor();
	COORD getter = ex.GetPos();
	string example = ex.GetString();
	cout << "String length is: " << example.size() << endl << "Cursor position is: {" << getter.X << "," << getter.Y << "}" << endl << "Your string is: " << example << endl;
	system("pause");
}
