#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include <fstream>
#include <sstream>

using namespace std;

struct Observation
{
    string date; // дата в формате "дд.мм.гггг".
    string familyMember; // член семьи
    double weight; // вес
};


class Floor_Scales
{
private:
    string StartDate; // дата начала отслеживания
    // вложенная структура данных
    map<string, map<string, double>> observations; // вложенная карта, где внешний ключ - это дата, а внутренний ключ - это имя члена семьи, а значение - вес
public:
    Floor_Scales() {} // конструктор по умолчанию
    
    double roundWeightTo50Grams(double weight) // функция, задающая (округляющая) вес с точностью до 50 грамм
    {
        return round(20 * weight) / 20.0;
    }
    
    void setStartDate(const string& date) // функция, устанавливающая начальную дату наблюдений
    {
        stringstream ss(date); // ss - строка, с который можно работать как с потоком ввода / вывода
        int day, month, year;
        char delimiter; // символ разделитель в дате (для проверки формата)
        if (!(ss >> day >> delimiter >> month >> delimiter >> year))
            // корректная проверка на компоненты даты, не содержащая строковые литералы
            throw invalid_argument("Invalid date format. Expected dd.mm.yyyy");
        if (delimiter != '.' || day < 1 || day > 31 || month < 1 || month > 12 || year < 1800 || year > 2100)
            throw invalid_argument("Invalid date values. Check the entered data.");
        StartDate = date;
    }
    
    string getStartDate() // функция, возвращающая начальную дату наблюдениий
    {
        return StartDate;
    }
    
    void setObservation(const string& date, const string& familyMember, double weight) // функция задающая наблюдение
    {
        stringstream ss(date);
        int day, month, year;
        char delimiter;
        if (!(ss >> day >> delimiter >> month >> delimiter >> year))
            throw invalid_argument("Invalid date format. Expected dd.mm.yyyy");
        if (delimiter != '.' || day < 1 || day > 31 || month < 1 || month > 12 || year < 1800 || year > 2100)
            throw invalid_argument("Invalid date values. Check the entered data.");
        observations[date][familyMember] = roundWeightTo50Grams(weight);
    }
    
    double getObservation(const string& date, const string& familyMember) // функция, возвращающая вес в выбранном наблюдении
    {
        if ((observations.find(date) != observations.end()) && (observations[date].find(familyMember) != observations[date].end() )) // существует ли наблюдение для даты и члена семьи
            return observations[date][familyMember];
        else
            throw out_of_range("no such observation exists"); // ключ не найден
    }
    
    double averageWeight(const string& famMem, const string& month = "") // функция, находящая средний вес члена семьи
    // параметр month имеет значение по умолчанию "" - вычисляется средний вес за всю историю наблюдений
    // строка month должна быть введена в формате "мм.гггг".
    {
        double sum = 0;
        int count = 0;
        for (const auto& obs : observations) // range-based цикл для прохода по контейнеру map
        {
            if (month.empty() || obs.first.substr(3, 7) == month) // проверка на соответствие месяца или отсутствие наблюдений в этот месяц
                if (obs.second.find(famMem) != obs.second.end()) // проверка наличия наблюдения за членом семьи в нужную дату
                {
                    sum += obs.second.at(famMem); // доступ к значению (весу) по ключу famMem в obs.second
                    count++;
                }
        }
        if (count > 0)
            return sum / count;
        else
            return 0;
    }
    
    double minWeight(const string& famMem, const string& month = "") // функция, находящая минимальный вес члена семьи
    {
        double minWeight = numeric_limits<double>::max();
        string minDate; // дата наблюдения, когда у выбранного члена семьи минимальный вес
        for (const auto& obs : observations)
        {
            if (month.empty() || obs.first.substr(3, 7) == month)
                if (obs.second.find(famMem) != obs.second.end())
                    if (obs.second.at(famMem) < minWeight)
                    {
                        minWeight = obs.second.at(famMem);
                        minDate = obs.first;
                    }
        }
        if (minWeight != numeric_limits<double>::max())
            return minWeight;
        else
            throw out_of_range("no observations found for the specified family member and month");
    }
    
    double maxWeight(const string& famMem, const string& month = "") // функция, находящая максимальный вес члена семьи
    {
        double maxWeight = numeric_limits<double>::lowest();
        string maxDate; // дата наблюдений, когда у выбранного члена семьи максимальный вес
        for (const auto& obs : observations)
        {
            if (month.empty() || obs.first.substr(3, 7) == month)
                if (obs.second.find(famMem) != obs.second.end())
                    if (obs.second.at(famMem) > maxWeight)
                    {
                        maxWeight = obs.second.at(famMem);
                        maxDate = obs.first;
                    }
        }
        if (maxWeight != numeric_limits<double>::lowest())
            return maxWeight;
        else
            throw out_of_range("no observations found for the specified family member and month");
    }
    
    void saveToFile(const string& filename) // функция,сохраняющая историю наблюдений в файл
    {
        ofstream file(filename); // конструктор для объекта типа std::ofstream (создание файла)
        if (!file.is_open()) // если файл нельзя открыть
        {
            throw runtime_error("unable to open file for writing");
        }
        
        for (const auto& obs : observations)
        {
            for (const auto& famMem : obs.second){
                file << obs.first << " " << famMem.first << " " << famMem.second << std::endl; // запись наблюдения в файл в формате "дата - имя члена семьи - вес"
            }
        }
        file.close();
    }
    
    void loadFromFile(const string& filename) // функция, считывающая историю наблюдений из файла
    {
        ifstream file(filename); // конструктор для объекта типа std::ifstream (создание файла)
        if (!file.is_open()) // если файл нельзя открыть
        {
            throw runtime_error("unable to open file for reading");
        }
        
        string line; // строка, в которую сохраняют наблюдения при чтении
        while (getline(file, line)) // пока не достигнут EOF
        {
            istringstream iss(line); // iss - строка / поток ввода
            string date, famMem;
            double weight;
            if (!(iss >> date >> famMem >> weight))
                throw runtime_error("file format error");
            setObservation(date, famMem, weight);
        }
        file.close();
    }
};


int main() {
    Floor_Scales info;
    info.setStartDate("12.06.2000");
    cout << info.getStartDate() << endl;
    info.setObservation("07.10.2018", "mom", 55.45);
    info.setObservation("24.12.2018", "mom", 55.05);
    info.setObservation("29.02.2019", "dad", 70.55);
    info.setObservation("05.05.2021", "mom", 51.026);
    cout << info.getObservation("05.05.2021", "mom") << endl;
    cout << info.averageWeight("mom") << endl;
    cout << info.minWeight("mom") << endl;
    cout << info.averageWeight("dad") << endl;
    
    info.saveToFile("/Users/vkutergi/Desktop/information_from_floor_scales.txt"); // здесь указывать свой путь
    return 0;
}


