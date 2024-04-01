#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <map>
#include <ctime>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

struct tmComparator {
    bool operator()(const tm& lhs, const tm& rhs) const {
        return mktime(const_cast<tm*>(&lhs)) < mktime(const_cast<tm*>(&rhs));
    }
};

class FloorScales {
private:
    map<string, map<tm, double, tmComparator>> observations;
    tm initialDate{};

public:
    void setInitialDate(const string& date) {
        initialDate = parseDate(date);
    }

    string getInitialDate() const {
        return formatDate(initialDate);
    }

    void addObservation(const string& date, const string& name, double weight) {
        tm date_tm = parseDate(date);
        observations[name][date_tm] = weight;
    }

    double getWeight(const string& date, const string& name) {
        tm date_tm = parseDate(date);
        auto nameIt = observations.find(name);
        if (nameIt != observations.end()) {
            auto dateIt = nameIt->second.find(date_tm);
            if (dateIt != nameIt->second.end()) {
                return dateIt->second;
            }
        }
        return -1;
    }

    double calculateAverageWeight(const string& name, int month = 0, int year = 0) {
        auto nameIt = observations.find(name);
        if (nameIt == observations.end()) return -1;

        double totalWeight = 0;
        int count = 0;
        for (const auto& entry : nameIt->second) {
            if ((month == 0 || entry.first.tm_mon + 1 == month) && (year == 0 || entry.first.tm_year + 1900 == year)) {
                totalWeight += entry.second;
                count++;
            }
        }
        return (count > 0) ? totalWeight / count : -1;
    }

    pair<double, string> findExtremumWeight(const string& name, bool findMin, int month = 0, int year = 0) {
        auto nameIt = observations.find(name);
        if (nameIt == observations.end()) return { -1, "" };

        double extremumWeight = findMin ? numeric_limits<double>::max() : numeric_limits<double>::lowest();
        string extremumDate;
        for (const auto& entry : nameIt->second) {
            if ((month == 0 || entry.first.tm_mon + 1 == month) && (year == 0 || entry.first.tm_year + 1900 == year)) {
                if ((findMin && entry.second < extremumWeight) || (!findMin && entry.second > extremumWeight)) {
                    extremumWeight = entry.second;
                    extremumDate = formatDate(entry.first);
                }
            }
        }
        return (extremumDate.empty()) ? make_pair(-1, "") : make_pair(extremumWeight, extremumDate);
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (const auto& nameObs : observations) {
            for (const auto& dateWeight : nameObs.second) {
                file << nameObs.first << "," << formatDate(dateWeight.first) << "," << dateWeight.second << "\n";
            }
        }
        file.close();
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        string line, name, dateStr;
        double weight;

        observations.clear();

        while (getline(file, line)) {
            stringstream iss(line);
            getline(iss, name, ',');
            getline(iss, dateStr, ',');
            iss >> weight;
            addObservation(dateStr, name, weight);
        }

        file.close();
    }

private:
    tm parseDate(const string& date) {
        tm tm{};
        stringstream ss(date);
        ss >> get_time(&tm, "%d-%m-%Y");
        return tm;
    }

    string formatDate(const tm& tm) const {
        stringstream ss;
        ss << put_time(&tm, "%d-%m-%Y");
        return ss.str();
    }
};

void clearScreen() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    system(CLEAR);
}

void printMenu() {
    cout << "1. Set initial observation date\n";
    cout << "2. Get initial observation date\n";
    cout << "3. Add observation\n";
    cout << "4. Get weight for a date\n";
    cout << "5. Save observations to file\n";
    cout << "6. Load observations from file\n";
    cout << "7. Calculate average weight\n";
    cout << "8. Find minimum weight\n";
    cout << "9. Find maximum weight\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    FloorScales scales;
    string filename = "observations.txt"; // Считывание и сохраниение и/из файла observations.txt

    while (true) {
        clearScreen();
        printMenu();
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string date, name;
        double weight;
        int month, year;

        switch (choice) {
        case 1: {
            cout << "Enter initial date (dd-mm-yyyy): "; // Формат ввода даты (dd-mm-yyyy) т.е. 17-08-2005
            cin >> date;
            scales.setInitialDate(date);
            break;
        }
        case 2: {
            cout << "Initial observation date: " << scales.getInitialDate() << endl;
            break;
        }
        case 3: {
            cout << "Enter date (dd-mm-yyyy): ";
            cin >> date;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter weight: ";
            cin >> weight;
            scales.addObservation(date, name, weight);
            break;
        }
        case 4: {
            cout << "Enter date (dd-mm-yyyy): ";
            cin >> date;
            cout << "Enter name: ";
            cin >> name;
            weight = scales.getWeight(date, name);
            if (weight != -1) {
                cout << "Weight: " << weight << " kg" << endl;
            }
            else {
                cout << "Weight not found." << endl;
            }
            break;
        }
        case 5: {
            scales.saveToFile(filename);
            cout << "Observations saved to " << filename << endl;
            break;
        }
        case 6: {
            scales.loadFromFile(filename);
            cout << "Observations loaded from " << filename << endl;
            break;
        }
        case 7: {
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter month and year (0 for all time): ";
            cin >> month >> year;
            double avgWeight = scales.calculateAverageWeight(name, month, year);
            if (avgWeight != -1) {
                cout << "Average weight: " << avgWeight << " kg" << endl;
            }
            else {
                cout << "No data found." << endl;
            }
            break;
        }
        case 8: {
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter month and year (0 for all time): ";
            cin >> month >> year;
            pair<double, string> minWeightDate = scales.findExtremumWeight(name, true, month, year);
            if (minWeightDate.first != -1) {
                cout << "Minimum weight: " << minWeightDate.first << " kg on " << minWeightDate.second << endl;
            }
            else {
                cout << "No data found." << endl;
            }
            break;
        }
        case 9: {
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter month and year (0 for all time): ";
            cin >> month >> year;
            pair<double, string> maxWeightDate = scales.findExtremumWeight(name, false, month, year);
            if (maxWeightDate.first != -1) {
                cout << "Maximum weight: " << maxWeightDate.first << " kg on " << maxWeightDate.second << endl;
            }
            else {
                cout << "No data found." << endl;
            }
            break;
        }
        case 0: {
            return 0; 
        }
        default: {
            cout << "Invalid option selected." << endl;
            break;
        }
        }
    }

    return 0;
}
