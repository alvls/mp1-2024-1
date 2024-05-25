#include <iostream>
#include <clocale>
#include <string>
#include <fstream>
#include <map>

using namespace std;
class Thermometer {
	unsigned int data;
	map<unsigned, double> temperatures;
public:
	Thermometer(char day_ = 1, char month_ = 1, char hour_ = 0) {
		data = day_ * 10000 + month_ * 100 + hour_;
	}
	void set_start(char day_, char month_, char hour_) { //установить начальные дату и время наблюдений
		unsigned int data = day_ * 10000 + month_ * 100 + hour_;
	}
	unsigned int find_start() { //узнать начальные дату и время наблюдений
		return data;
	}
	void set_observation(double value_) { //задать наблюдение
		if (temperatures.count(data) == 1) {
			temperatures.erase(temperatures[data]);
		}
		temperatures[data++] = value_;
		if (data % 100 == 24) { // проверка на заполнение дневных координат
			data -= 24;
			data += 10000; // увеличение дня на один
			if (data / 10000 == 32) { // проверка на заполнение координат дней
				data -= 310000;
				data += 100;
				if (((data % 10000) / 100) == 13) {
					data -= 1200;
				}
			}
			else if (((data / 10000) == 31) && (((data % 10000) / 100 == 4) || ((data % 10000) / 100 == 6) || ((data % 10000) / 100 == 9) || ((data % 10000) / 100 == 11))) { // проверка на заполнение координат дней
				data -= 300000;
				data += 100;
			}
			else if (((data / 10000) == 29) && ((data % 10000) / 100 == 2)) {
				data -= 280000;
				data += 100;
			}
		}
	}
	int find_temperature(char day_, char month_, char hour_) { //узнать температуру в выбранном наблюдении
		if (temperatures.count(data) == 1) {
			return temperatures[day_ * 10000 + month_ * 100 + hour_];
		}
		return 0;
	}
	void set_series_of_observation(char day_, char month_, double *values, unsigned size_t) {//задать серию наблюдений для выбранной даты
		unsigned help_data = day_ * 10000 + month_ * 100;
		size_t %= 25;
		for (unsigned i = 0; i < size_t; i++) {
			if (temperatures.count(data) == 1) {
				temperatures.erase(temperatures[data]);
			}
			temperatures[help_data + i] = values[i];
		}
	}
	double find_mean_day(char day_, char month_) { //найти среднюю температуру для выбранной даты
		double average_value = 0;
		double count = 0;
		unsigned help_data = day_ * 10000 + month_ * 100;
		for (int i = 0; i < 24; i++) {
			if (temperatures.count(help_data + i) == 1) {
				average_value += temperatures[help_data + i];
				count++;
			}
		}
		return average_value / count;
	}
	double find_mean_month(char month_) { //найти среднюю температуру для выбранного выбранного месяца
		double average_value = 0;
		double count = 0;
		for (int j = 1; j < 32; j++)
			for (int i = 0; i < 24; i++) {
				unsigned help_data = j * 10000 + month_ * 100 + i;
				if (temperatures.count(help_data) == 1) {
					average_value += temperatures[help_data];
					count++;
				}
			}
		return average_value / count;
	}
	double find_mean_all_time() { //найти среднюю температуру за всю историю наблюдений
		double average_value = 0;
		double count = 0;
		for (const auto& element : temperatures)
		{
			average_value += element.second;
			count++;
		}
		return average_value / count;
	}
	double find_mean_all_day_or_night(string d, char month_) { //найти среднюю дневную или ночную температуру для выбранного месяца
		double average_value = 0;
		double count = 0;
		if (d == "day") {
			for (int i = 1; i < 32; i++) {
				for (int j = 6; j < 22; j++) {
					unsigned help_data = i * 10000 + month_ * 100 + j;
					if (temperatures.count(help_data) == 1) {
						average_value += temperatures[help_data + j];
						count++;
					}
				}
			}
		}
		else {
			for (int i = 1; i < 32; i++) {
				for (int j : {22, 23, 0, 1, 2, 3, 4, 5}) {
					unsigned help_data = i * 10000 + month_ * 100 + j;
					if (temperatures.count(help_data) == 1) {
						average_value += temperatures[help_data + j];
						count++;
					}
				}
			}
		}
		return average_value / count;
	}
	void save_to_file(string way) {//сохранить словарь в файл
		ofstream fout(way, ios::app);
		if (fout.is_open()) {
			for (const auto& element : temperatures)
			{
				fout << element.first / 10000 << " " << (element.first % 10000) / 100 << " " << element.first % 100 << " - " << element.second << endl;
			}
			fout.close();
		}
	}
	void read_file(string way) {//считать словарь из файла
		ifstream fin(way);
		if (fin.is_open()) {
			char buff[5];
			int day, month, hour;
			double value;
			while (!(fin.eof()))
			{		
				fin >> buff; day = stoi(buff);
				fin >> buff; month = stoi(buff);
				fin >> buff; hour = stoi(buff);
				fin >> buff; 
				fin >> buff; value = stod(buff);
				unsigned help_data = day * 10000 + month * 100 + hour;
				if (temperatures.count(help_data) == 1) {
					temperatures.erase(temperatures[help_data]);
				}
				temperatures[help_data] = value;
			}
			fin.close();
		}
	}
};

void main() {
	Thermometer A(31, 12, 22);
	A.set_observation(-30); // задаём наблюдение
	A.set_observation(-35);
	A.set_observation(-32);
	A.set_observation(-35);
	// далее представлены поиски среднего для разных случаев
	cout << A.find_mean_all_time() << endl; 
	cout << A.find_mean_day(31, 12) << endl;
	cout << A.find_mean_month(12) << endl;
	cout << A.find_temperature(1, 1, 2) << endl;
	double values[24] { -25.0, -20.0, -20.0, -23.0, -24.0, -21.0, -22.0, -24.0 };
	A.set_series_of_observation(1, 1, values, 8);
	cout << A.find_temperature(1, 1, 2) << endl;
	cout << A.find_mean_all_day_or_night("day", 1) << endl;
	cout << A.find_mean_all_day_or_night("night", 1) << endl;
	cout << A.find_temperature(1, 1, 2) << endl;
	cout << A.find_temperature(1, 1, 8) << endl;
	A.save_to_file("C:\\prov\\yu.txt");
	Thermometer B(10);
	B.read_file("C:\\prov\\yu.txt");
	cout << B.find_temperature(1, 1, 1) << endl;
	cout << B.find_temperature(1, 1, 2) << endl;
	B.save_to_file("C:\\prov\\yu.txt");
	system("pause");
}