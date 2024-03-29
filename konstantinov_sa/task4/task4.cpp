#include<iostream>
#include<string>
#include <fstream>
#include <map>
#include<string>
using namespace std;

class Datetime {
public:
    int hour;
    int day;
    int month;
    int year;

    Datetime(int time = 0, int aday = 1, int amonth = 1, int ayear = 2000) {
        hour = time;
        day = aday;
        month = amonth;
        year = ayear;
    }

    /*void print() {
        cout << hour << "h " << day << "/" << month << "/" << year << endl;
    }*/

    friend std::ostream& operator<<(std::ostream& os, const Datetime& dt) {
        os << dt.hour << "h " << dt.day << "/" << dt.month << "/" << dt.year;
        return os;
    }

    Datetime shifted(int dtime = 0, int dday = 0, int dmonth = 0, int dyear = 0) {
        Datetime d = *this;
        d.hour += dtime;
        d.day += dday;
        d.month += dmonth;
        d.year += dyear;
        return d;
    }

    bool isValid() const { //для невисокосного года
        if (hour < 0 || hour > 23) {
            return false;
        }
        if (month < 1 || month > 12) {
            return false;
        }
        if (day < 1 || day > 31) {
            return false;
        }
        if (month == 2 && day > 28) {
            return false;
        }
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
            return false;
        }
        return true;
    }

    bool operator>=(const Datetime& other) const {
        if (year > other.year) {
            return true;
        }
        else if (year == other.year) {
            if (month > other.month) {
                return true;
            }
            else if (month == other.month) {
                if (day > other.day) {
                    return true;
                }
                else if (day == other.day) {
                    if (hour >= other.hour) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool operator<=(const Datetime& other) const {
        if (year < other.year) {
            return true;
        }
        else if (year == other.year) {
            if (month < other.month) {
                return true;
            }
            else if (month == other.month) {
                if (day < other.day) {
                    return true;
                }
                else if (day == other.day) {
                    if (hour <= other.hour) {
                        return true;
                    }
                }
            }
        }
        return false;
    }


    bool operator<(const Datetime& other) const {
        if (year < other.year) {
            return true;
        }
        else if (year == other.year) {
            if (month < other.month) {
                return true;
            }
            else if (month == other.month) {
                if (day < other.day) {
                    return true;
                }
                else if (day == other.day) {
                    if (hour < other.hour) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool operator>(const Datetime& other) const {
        if (year > other.year) {
            return true;
        }
        else if (year == other.year) {
            if (month > other.month) {
                return true;
            }
            else if (month == other.month) {
                if (day > other.day) {
                    return true;
                }
                else if (day == other.day) {
                    if (hour > other.hour) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool operator==(const Datetime& other) const {
        return (year == other.year && month == other.month && day == other.day && hour == other.hour);
    }

    bool operator!=(const Datetime& other) const {
        return (year != other.year || month != other.month || day != other.day || hour != other.hour);
    }
};

class Thermo {
private:
    map <Datetime, float> tlog;//в прошлой лабораторной я уже реализовал класс с логикой добавления, поиска элементов, перезаписью дубликатов, поэтому думаю, что имею право использовать map
    Datetime start;
public:

    Thermo(Datetime start_ = Datetime()) {
        start = start_;
    }

    void erase(Datetime e) {
        tlog.erase(e);
    }

    void erase(Datetime from, Datetime to) {
        auto& first = tlog.lower_bound(from);
        auto& last = tlog.upper_bound(to);
        tlog.erase(first,last);
    }

    Datetime getStart() {
        return start;
    }

    void changePeriod(Datetime nstart) {
        if (nstart > start) {
            // ------
            // xx----++
            auto& first = tlog.lower_bound(start);
            auto& last = tlog.lower_bound(nstart);
            tlog.erase(first, last);
            start = nstart;  
        }
        else if (nstart != start) {
            auto& last = tlog.lower_bound(start.shifted(0,0,0,1));
            auto& first = tlog.upper_bound(nstart.shifted(0,0,0,1));
            tlog.erase(first, last);
            start = nstart;
        }
    }

    void printPeriod() {
        cout << "start " << start << " end " << start.shifted(0, 0, 0, 1) << endl;
    }

    float getSample(Datetime date) {
        return tlog[date];
    }

    static const enum class scope { day, month, alltime, monthdays, monthnights };

    float getAvgTempIn(scope sc, Datetime dt) {

        Datetime st = dt;
        st.hour = 0;
        Datetime ed;
        
            switch (sc) {
            case scope::day:
                ed = st.shifted(0, 1);
                break;
            case scope::month:
                st.day = 0;
                ed = st.shifted(0, 0, 1);
                break;
            default:
            case scope::alltime:
                st = start;
                ed = start.shifted(0, 0, 0, 1);
            }

            auto sit = tlog.lower_bound(st);
            auto eit = tlog.lower_bound(ed); 
            float s = 0.0;
            int c = 0;
            if (sc < scope::monthdays) {
                for (auto i = sit;i != eit;i++) {
                    s += i->second;
                    c++;
                }
            }
            else {
                if (sc == scope::monthnights) {
                    for (auto i = sit;i != eit;i++) {
                        Datetime e = i->first;
                        if ((e.hour < 6) || (e.hour >= 18)) {
                            s += i->second;
                            c++;
                        } 
                    }
                }
                else {
                    for (auto i = sit;i != eit;i++) {
                        Datetime e = i->first;
                        if ((e.hour>=6) && (e.hour < 18)) {
                            s += i->second;
                            c++;
                        }
                    }
                }                
            }
            return s / c;
    }

    void add(Datetime date, float temp) {
        if ((date.isValid())) {
            if ((date >= start) && (date <= start.shifted(0, 0, 0, 1)))
                tlog[date] = temp;
            else
                throw string("out of one year range");
        }else
            throw string("invalid date");
    }

    void InputSeria(Datetime serst, int samples) {//Ручной ввод серии последовательных измерений каждый час начиная с указанного часа
        if ((serst.hour + samples > 24) || !(serst.isValid())) {
            cout << "Invalid date or duration";
            return;
        }
        int i = 0;
        float t;
        while (i < samples) {
            cin >> t;
            tlog[serst.shifted(i)] = t;
            i++;
        }
    }

    void print() {
        for (const auto& pair : tlog) {
            cout<<pair.first<<":\t"<<pair.second << endl;
        }

    }

    void clear() {
        tlog.clear();
    }

    void save(string filename) {//сохранение в файл начальную дату и измерения
        ofstream fout(filename, std::ios::binary);
        if (fout.is_open()) {
            fout.write(reinterpret_cast<const char*>(&start), sizeof(Datetime));
            for (const auto& pair : tlog) {
                fout.write(reinterpret_cast<const char*>(&pair.first), sizeof(Datetime));
                fout.write(reinterpret_cast<const char*>(&pair.second), sizeof(float));
            }
            fout.close();
        }
    }

    void load(string filename) {//чтение из файла, стирает старые данные
        ifstream fin(filename, std::ios::binary);
        if (fin.is_open()) {
            clear();
            fin.read(reinterpret_cast<char*>(&start), sizeof(Datetime));
            while (true) {
                Datetime datetime;
                float value;
                fin.read(reinterpret_cast<char*>(&datetime), sizeof(Datetime));
                fin.read(reinterpret_cast<char*>(&value), sizeof(float));
                if (fin.eof()) {
                    break;
                }
                tlog[datetime] = value;
            }
            fin.close();
        }
    }
    
};


int main() {
	setlocale(LC_ALL, "rus");
    Datetime start(1, 3, 1, 2006);
    Thermo th(start);
    th.printPeriod();

    
    Datetime dt(4, 5, 6, 2006);
    th.add(dt, 10.5);
    th.add(dt.shifted(1), 20.2);
    th.add(dt.shifted(18), 33.88);
    th.add(dt.shifted(5, 1), 30.7);
    th.add(start.shifted(1, 1, 11, 0), 999.9);
    th.add(start.shifted(2, 2, 10, 0), 888.9);
    cout << "Попытка добавть несуществующую дату приводит к исключению\n";
    try {
        th.add(start.shifted(2, 2, 12, 0), 888.9);
    }
    catch (string err) {
        cout << err << endl;
    }


    th.print();
    th.save("log1.txt");
    cout << "__________________\n";
    
    //th.erase(dt, dt.shifted(2));
    cout << "Изменим дату отсчёта, измерения за пределами года автоматически стираются. Заменим результат первого измерения\n";
    th.changePeriod(start.shifted(0,0,8,-1));
    th.add(dt, 11.1111);
    th.printPeriod();
    th.print();
    cout << "__________________\n";
    cout << "Загрузим предыдущий набор из файла\n";
    th.load("log1.txt");
    th.printPeriod();
    th.print();
    th.clear();

    cout << "Введите серию из 4 измерений, вывод средней температуры за день\n";
    th.InputSeria(dt, 4);
    th.printPeriod();
    th.print();
    cout << th.getAvgTempIn(th.scope::day, dt) << endl;
	//system("pause");
}