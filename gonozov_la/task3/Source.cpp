#include <iostream>
#include <clocale>
#include <string>
#include <fstream>
using namespace std;

class Translate {
	size_t sz_array;
	size_t number_of_elem = 0;
	string* array_keys;
	string* array_value;
	void increasing_size_of_array() {
		size_t sz_array_help = sz_array * 2;
		string* array_keys_help = new string[sz_array_help];
		string* array_value_help = new string[sz_array_help];
		for (int i = 0; i < number_of_elem; i++) {
			array_keys_help[i] = array_keys[i];
			array_value_help[i] = array_value[i];
		}
		delete[] array_keys;
		delete[] array_value;
		array_keys = array_keys_help;
		array_value = array_value_help;
		sz_array = sz_array_help;
	}
public:
	Translate(size_t sz_array_ = 10) { 
		sz_array = sz_array_;
		array_keys = new string[sz_array];
		array_value = new string[sz_array];
	}
	void add(string key, string value){ // добавить в словарь слово и его перевод
		if (sz_array == number_of_elem) {
			increasing_size_of_array();
		}
		array_keys[number_of_elem] = key;
		array_value[number_of_elem++] = value;
	} 
	void change(string key, string value) {//изменить перевод указанного слова
		for (int i = 0; i < number_of_elem; i++) {
			if (array_keys[i] == key) {
				array_value[i] = value;
				break;
			}
		}
	}
	string check_translate(string key) {//узнать перевод выбранного слова
		for (int i = 0; i < number_of_elem; i++) {
			if (array_keys[i] == key)
				return array_value[i];
		}
		return "Слово не найдено";
	} 
	bool check_availability(string key) {//проверить наличие слова в словаре
		for (int i = 0; i < number_of_elem; i++) {
			if (array_keys[i] == key)
				return true;
		}
		return false;
	}
	size_t number_element() { //узнать число слов в словаре
		return number_of_elem;
	}
	void save_to_file(string way) {//сохранить словарь в файл
		ofstream fout(way, ios::app);
		if (fout.is_open()) {
			for (int i = 0; i < number_of_elem; i++) {
				fout << array_keys[i] << " - " << array_value[i] << endl;
			}
			fout.close();
		}
	}
	void read_file(string way) {//считать словарь из файла
		char buff[30];
		ifstream fin(way);
		if (fin.is_open()) {
			for (int i = 0; i < number_of_elem; i++) {
				if (sz_array == i) {
					increasing_size_of_array();
				}
				fin >> buff;
				array_keys[i] = buff;
				fin >> buff;
				fin >> buff;
				array_value[i] = buff;
			}
			fin.close();
		}
	}
	~Translate() {//декструктор
		delete[] array_keys;
		array_keys = nullptr;
		delete[] array_value;
		array_value = nullptr;
	}
};

void main() {
	setlocale(LC_ALL, "rus");
	Translate A(5);
	A.add("find", "найти");
	A.add("cat", "кошка");
	A.add("cabbage", "капуста");
	A.add("picturescue", "живописный");
	A.add("trust", "доверять");
	A.add("total", "полный");
	A.add("destruction", "разурешение");
	A.add("choice", "выбор");
	A.change("find", "Шлишел");
	cout << A.check_translate("total"); 
	cout << A.check_translate("find");
	cout << A.number_element();  
	A.save_to_file("C:\\prov\\yu.txt");
	Translate B(5);
	B.read_file("C:\\prov\\yu.txt");
	cout << A.check_translate("total");
	cout << A.check_translate("find");
	cout << A.number_element();
	system("pause");
}