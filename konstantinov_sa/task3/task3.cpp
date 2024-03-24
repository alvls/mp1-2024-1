#include<iostream>
#include<string>
#include <fstream>
using namespace std;

//Элемент связанного списка
class Wpair {
public:
	string key;
	string value;
	Wpair* nextp;

	Wpair(const string& k, const string& v) {
		key = k;
		value = v;
		nextp = nullptr;
	}


};

//В основе словаря связяанный список
class Dict {
private:
	Wpair* start;
	Wpair* end;

	Wpair* findWp(const string& key) {
		Wpair* p = start;
		while (p != nullptr) {
			//cout << p->key<<endl;
			if (p->key == key)
				return p;
			p = p->nextp;
		}
		return nullptr;
	}

	Wpair* findprevWp(const string& key) {
		Wpair* p = start;
		while (p->nextp != nullptr) {
			if (p->nextp->key == key)
				return p;
			p = p->nextp;
		}
		return nullptr;
	}

	string formatWpValue(Wpair* w) {
		string& v = w->value;
		string res;
		size_t oldf = 0;
		size_t f = 0;
		unsigned c = 1;
		while (f != string::npos) {
			f = v.find('\n', f+1);
			res = res+"\t"+to_string(c) + ") " + v.substr(oldf + (c>1), f - oldf) + "\n";
			oldf = f;
			c++;
		}
		return res;
	}

public:
	Dict() {
		start = nullptr;
		end = nullptr;
	}
	
	//Добавление в начало, допускает дубликаты.
	void add(const string& key,const string& value) {
		Wpair* newp = new Wpair(key, value);
		newp->nextp = start;
		start = newp;
		//cout <<" +added | "<< start->key << " _ " << start->value << endl;
	}


	//Потенциально более медленное добавление в конец, так как иногда потребуется найти конец. Используется для загрузки из файла
	void append(const string& key, const string& value) {
		if (end == nullptr) {
			if (start == nullptr) {
				add(key, value);
				end = start;
				return;
			}
			else {
				Wpair* p = start;
				while (p->nextp != nullptr) {
					p = p->nextp;
				}
				end = p;
			}

		}
		
		Wpair* newp = new Wpair(key, value);
		end->nextp = newp;
		end = newp;
	}

	//заменить текущие варианты перевода на новый (один)
	void replace(const string& key, const string& value) {
		Wpair* f = findWp(key);
		if (f)
			f->value = value;
	}
	//добавление в начало, не создающее дубликат (перезапись в случае дубликата)
	void addOrReplace(const string& key, const string& value) {
		Wpair* f = findWp(key);
		if (f)
			f->value = value;
		else
			add(key, value);
	}

	//дополнить ещё одним вариантом перевода (каждая новая строка - новый вариант)
	void complete(const string& key, const string& addition) {
		Wpair* f = findWp(key);
		if (f)
			f->value = f->value + "\n" + addition;
	}

	void remove(const string& key) {
		Wpair* p = findprevWp(key);
		if (p != nullptr) {
			Wpair* nn = p->nextp->nextp;
			delete p->nextp;
			p->nextp = nn;
		}
	}

	void clear() {
		Wpair* p = start;
		Wpair* n = start->nextp;
		while (n != nullptr) {
			delete p;
			p = n;
			n = p->nextp;
		}
		start = nullptr;
		end = nullptr;
	}

	bool exists(const string& key) {
		return findWp(key);
	}

	size_t count() {
		size_t ans = 0;
		Wpair* p = start;
		while (p != nullptr) {
			ans++;
			p = p->nextp;
		}
		return ans;
	}

	string get(const string& key) {
		Wpair* f = findWp(key);
		if (f)
			return formatWpValue(f);
		return "?";
	}

	void print() {
		cout << "---------------\n";
		Wpair* p = start;
		while (p != nullptr) {
			//cout << p->key <<" | next: "<<p->nextp<< endl;
			cout <<p->key << ":\n" << formatWpValue(p)<<endl;
			p = p->nextp;
		}
	}
	//сохраняет словарь в файл
	void save(const string filename) {
		ofstream file;
		file.open(filename, ofstream::out | ofstream::trunc);
		if (file.is_open()) {
			Wpair* p = start;
			while (p != nullptr) {
				file << '+' << p->key << '\n';
				file << p->value << '\n';
				p = p->nextp;
			}
			file.close();
		}	
	}
	//загружает (добавляет) в словарь содержимое из файла, не очищает
	void load(const string filename) {
		ifstream file(filename);
		string s;
		string k;
		string v;

		if (file.is_open()) {
			getline(file, k);
			k = k.substr(1);
			do {
				getline(file, s);
				if (s[0] == '+') {
					append(k, v.substr(0, v.size() - 1));
					v.clear();
					k = s.substr(1);
				}
				else {
					v = v + s + '\n';
				}
				//cout << "load: s: " << s << endl << "k: " << k << endl << "v:-" << v << endl;
			} while (s != "");
			append(k, v.substr(0, v.size()-2));
			file.close();
		}
	}

	~Dict() {
		clear();
	}
};

int main() {
	setlocale(LC_ALL, "rus");

	Dict d;
	d.add("qeue","очередь");
	d.complete("qeue", "хвост");
	d.add("cat", "кот");
	d.add("impostor", "самозванец");
	d.complete("impostor", "мошенник");
	d.add("nuclear", "ядрёный");

	d.print();
	cout << "Исправим nuclear\n";
	d.replace("nuclear", "ядерный");
	cout << "Ищем\n";
	string f = "nuclear";
	cout << f << " - " << d.get(f)<<endl;
	cout << "Слов всего: " << d.count() << endl<<"удалим impostor и сохраним. Загрузим другой словарь\n";

	d.remove("impostor");

	d.save("ddd.txt");
	
	d.clear();
	d.load("premade.txt");
	d.print();

	cout << "Вернём сохранённый\n";
	d.clear();
	d.load("ddd.txt");
	d.print();
	

	system("pause");
}