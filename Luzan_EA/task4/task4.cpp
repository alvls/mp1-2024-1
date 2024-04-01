#define _CRT_SECURE_NO_WARNINGS
#include <iostream>  
#include <string>  
#include <fstream> 
#include <vector> 
#include <locale> 

/*
*	������ id ����������� ����� ������ ��� ������ � �������� � ��������� Fast
*   ���������� ��� ��� ����� ���� ���������� id
*/

using namespace std;

class TSong {
public:

	string songName;
	string albumName;

	string singerName;
	size_t singerID;

	string poetName;

	string kompName;

	string day; 
	string month; 
	string year;

	TSong() = default;

	TSong( const string songName_, const string albumName_, const  string singerName_, const string poetName_,
		const string kompName_, const string day_, const string month_, const string year_) {

		songName = songName_;

		albumName = albumName_;

		singerName = singerName_;
		singerID = -1;

		poetName = poetName_;

		kompName = kompName_;

		day = day_;
		month = month_;
		year = year_;
	}

	TSong(const TSong& obj) {
		songName =obj.songName;

		albumName = obj.albumName;

		singerName = obj.singerName;
		singerID = obj.singerID;

		poetName = obj.poetName;

		kompName = obj.kompName;

		day = obj.day;
		month = obj.month;
		year = obj.year;
	}
	
	~TSong() = default;
	
	void printSong() {
		cout << songName << " " << albumName << " " << singerName << "  " << poetName
			 << "  " << kompName << "  " << day << '/' << month << '/' << year << endl;
	}

	TSong& operator= (const TSong& obj) {
		songName = obj.songName;

		albumName = obj.albumName;

		singerName = obj.singerName;
		singerID = obj.singerID;

		poetName = obj.poetName;

		kompName = obj.kompName;

		day = obj.day;
		month = obj.month;
		year = obj.year;

		return *this;
	}
};


class  Tpair {
public:
	string Name;
	size_t ID;

	Tpair() = default;

	Tpair(const string Name_, const size_t ID_) {
		Name = Name_;
		ID = ID_;
	}

	Tpair(const Tpair& obj) {
		Name = obj.Name;
		ID = obj.ID;
	}
	
	~Tpair() = default;

};


class TSongLib {
private:	
	vector <TSong> list;
	vector <Tpair> singersIDList;

	void sort_() {
		size_t i = list.size() - 1;
		while (list[i].songName < list[i - 1].songName) {
			TSong tmp;
			tmp = list[i - 1];
			list[i - 1] = list[i];
			list[i] = tmp;
			i--;
			if (i == 1) { break; }
		}
		while ((list[i].songName <= list[i - 1].songName) && (list[i].singerName < list[i - 1].singerName)) {
			TSong tmp;
			tmp = list[i - 1];
			list[i - 1] = list[i];
			list[i] = tmp;
			i--;
			if (i == 1) { break; }
		}
	}

public:
	TSongLib () {
		TSong tmp("\n", "\n", "\n", "\n", "\n", "\n", "\n", "\n");
		list.resize(0);
		list.push_back(tmp);

		Tpair tmp_("\n", 0);
		singersIDList.resize(0);
		singersIDList.push_back(tmp_);
	}
	
	~TSongLib() = default;

	bool addSongFast(const TSong& obj) {
		list.push_back(obj);
		return true;
	}
	
	bool addSongNoId(TSong obj) {
		//� ID ����� ������ ��� ������
		size_t tmp_size = singersIDList.size();

		if (findSong(obj.songName, obj.singerName) > 0) {
			return false; //Error: dublicate song
		}

		size_t ID = -1;
		for (size_t i = 1; i < tmp_size; i++) 
			if (obj.singerName == singersIDList[i].Name)
				ID = singersIDList[i].ID;

		
		if (ID == -1) {
			ID = singersIDList.size();
			Tpair tmp_obj(obj.singerName, ID);
			singersIDList.push_back(tmp_obj);
		}
		obj.singerID = ID;
		list.push_back(obj);
		sort_();
		return true;
	}

	bool addSong(const string songName, const string albumName, const  string singerName, const string poetName,
		const string kompName, const string day, const string month, const string year) {

		TSong new_song(songName, albumName, singerName, poetName, kompName, day, month, year);
		
		return addSongNoId(new_song);
	}

	size_t findSong(const string sngNm, const string sngrNm) {
		size_t sngrID = 0;
		size_t tmp_size = singersIDList.size();

		for (size_t i = 1; i < tmp_size; i++) {
			if (sngrNm == singersIDList[i].Name) {
				sngrID = singersIDList[i].ID;
				break;
			}
		}

		if (sngrID == 0) {
				//cout << "NO SUCH SINGER\n";
				return 0; // Error
			}

		tmp_size = list.size();
		for (size_t i = 1; i < tmp_size; i++) 
			if (sngrID == list[i].singerID) 
				if (sngNm == list[i].songName) 
					return i;

		//cout << "NO SUCH SONG\n";
		return 0; // Error
		
	}
	
	TSong getSong(size_t songNum) {
		return list[songNum];
	}

	bool editSongFast(size_t songNum, const TSong& edited_song) {
		// !doesnt check if new author exist in the list
		if (songNum < 0)
			return false;

		list[songNum] = edited_song;
		return true;
	}
	
	bool editSong(size_t songNum, const TSong& edited_song) {
		if (songNum < 0)
			return false;

		//if new singer check
		if (( edited_song.singerName == list[songNum].singerName) || 
			(edited_song.singerID != list[songNum].singerID) ) { 
			size_t tmp_size = singersIDList.size();
			size_t ID = -1;
			for (size_t i = 0; i < tmp_size; i++)
				if (edited_song.singerName == singersIDList[i].Name)
					ID = singersIDList[i].ID;

			if (ID == -1) {
				ID = singersIDList.size();
				Tpair tmp_obj(edited_song.singerName, ID);
				singersIDList.push_back(tmp_obj);
			}

			list[songNum] = edited_song;
			list[songNum].singerID = ID;
			return true;
		}

		list[songNum] = edited_song;
		return true;
	}

	void printLib() {
		for (int i = 1; i < list.size(); i++) {
			list[i].printSong();
		}
	}

	bool printBySinger(const string singer) {
		size_t tmp = singersIDList.size();
		size_t tmpID = -1;
		for (size_t i = 0; i < tmp; i++) {
			if (singer == singersIDList[i].Name) 
				tmpID = singersIDList[i].ID;
		}
		if (tmpID == -1)
			return false;

		tmp = list.size();
		for (size_t i = 1; i < tmp; i++)
			if (list[i].singerID == tmpID)
				list[i].printSong();

		return true;
	}

	bool printByPoet(const string poet ){
		size_t tmp = list.size();
		for (size_t i = 1; i < tmp; i++)
			if (list[i].poetName == poet)
				list[i].printSong();
		return true;
	}

	bool printByKomp(const string komp) {
		size_t tmp = list.size();
		for (size_t i = 1; i < tmp; i++)
			if (list[i].kompName == komp)
				list[i].printSong();
		return true;
	}

	size_t getSize() {
		return list.size() - 1;
	}

	bool libExport (const string& path) { 
		ofstream fout(path);
		if (!fout.is_open())
			return false;

		size_t lib_size = getSize();
		for (int i = 1; i < lib_size + 1; i++) {
			fout << list[i].songName << " # " << list[i].albumName << " # " << list[i].singerName
				<< " # " << list[i].poetName << " # " << list[i].kompName << " # " << list[i].day
				<< " # " << list[i].month << " # " << list[i].year << " # " << endl;
		}

		fout.close();
		return true;
	}

	bool libImport(const string& path) {
		ifstream fin(path);
		string line; 
		
		list.clear();
		singersIDList.clear();
		TSong tmp("\n", "\n", "\n", "\n", "\n", "\n", "\n", "\n");
		list.push_back(tmp);
		Tpair tmp_("\n", 0);
		singersIDList.push_back(tmp_);

		if (!fin.is_open())
			return false;
		
		while (getline(fin, line)) {
			line += " # ";
			TSong song;
			string tmp = "";
			size_t i = 0;
			while ( (line[i] != ' ') || (line[i + 1] != '#') || (line[i + 2] != ' ') ) {
				tmp += line[i];
				i++;
			}
			song.songName = tmp; 
			 i+=3;
			tmp = "";

			while ((line[i] != ' ') || (line[i + 1] != '#') || (line[i + 2] != ' ')) {
				tmp += line[i];
				i++;
			}
			song.albumName = tmp;
			tmp = ""; i+=3;

			while ((line[i] != ' ') || (line[i + 1] != '#') || (line[i + 2] != ' ')) {
				tmp += line[i];
				i++;
			}
			song.singerName = tmp;
			tmp = ""; i+=3;

			while ((line[i] != ' ') || (line[i + 1] != '#') || (line[i + 2] != ' ')) {
				tmp += line[i];
				i++;
			}
			song.poetName= tmp;
			tmp = ""; i+=3;

			while ((line[i] != ' ') || (line[i + 1] != '#') || (line[i + 2] != ' ')) {
				tmp += line[i];
				i++;
			}
			song.kompName = tmp;
			tmp = ""; i+=3;

			while ((line[i] != ' ') || (line[i + 1] != '#') || (line[i + 2] != ' ')) {
				tmp += line[i];
				i++;
			}
			song.day = tmp;
			tmp = ""; i+=3;

			while ((line[i] != ' ') || (line[i + 1] != '#') || (line[i + 2] != ' ')) {
				tmp += line[i]; 
				i++;
			}
			song.month = tmp;
			tmp = ""; i+=3;

			while ((line[i] != ' ') || (line[i + 1] != '#') || (line[i + 2] != ' ')) {
				tmp += line[i];
				i++;
			}
			song.year = tmp; 
			i += 3;

			addSongNoId(song);
		}

		fin.close();
		return true;
	}
};



int main() {
	setlocale(LC_ALL, "Russian");
	TSongLib lib;
	TSong song("�����1", "47", "�����1", "����1", "����������1", "10", "12", "1993");
	lib.addSongNoId(song);
	lib.addSong("�����2", "42", "�����2", "����22", "����������2", "11", "12", "1923");
	lib.addSong("�����3", "42", "�����1", "����22", "����������3", "11", "12", "2023");
	lib.addSong("�����4", "42", "�����3", "����22", "����������1", "11", "12", "2023");
	lib.addSong("�����4", "42", "�����3", "����22", "����������1", "11", "12", "2023");
	cout << lib.findSong("�����3", "�����1") << " ---- " << lib.getSong(lib.findSong("�����3", "�����1")).kompName;
	
	//lib.printBySinger("�����3");
	//cout << "\n-------------------------------------------\n";
	//lib.printLib();
	//cout << lib.getSize() << endl;

	string path = "lib.txt";
	lib.libImport(path);
	cout << "\n-------------------------------------------\n";
	lib.printLib();

	system("pause");
	return 0;
}