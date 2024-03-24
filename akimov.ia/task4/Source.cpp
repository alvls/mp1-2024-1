#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Contact
{
private:
	string lastName;
	string firstName;
	string middleName;
	string phoneNumber;
	int day;
	int month;
	int year;
	bool isFavorite;
public:
	Contact(string last, string first, string middle, string phone, int d, int m, int y, bool favorite)
	{
		lastName = last;
		firstName = first;
		middleName = middle;
		phoneNumber = phone;
		day = d;
		month = m;
		year = y;
		isFavorite = favorite;
	}
	string getLastName() const { return lastName; }
	string getFirstName() const { return firstName; }
	string getMiddleName() const { return middleName; }
	string getPhone() const { return phoneNumber; }
	int getDay() const { return day; }
	int getMonth() const { return month; }
	int getYear() const { return year; }
	bool getIsFavorite() const { return isFavorite; }
    void setLastName(string last) { lastName = last; }
    void setFirstName(string first) { firstName = first; }
    void setMiddleName(string middle) { middleName = middle; }
    void setPhone(string phone) { phoneNumber = phone; }
    void setDay(int d) { day = d; }
    void setMonth(int m) { month = m; }
    void setYear(int y) { year = y; }
	void setIsFavorite(bool favorite) { isFavorite = favorite; }
};

class Contacts
{
private:
	vector<Contact> contacts;
public:
	void addContact(Contact contact)
	{
		contacts.push_back(contact);
		sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b)
			{
				if (a.getLastName() != b.getLastName())
					return a.getLastName() < b.getLastName();
				if (a.getFirstName() != b.getFirstName())
					return a.getFirstName() < b.getFirstName();
				return a.getMiddleName() < b.getMiddleName();
			});
	}

    void changeContact(const string& lastName, const string& firstName, const string& middleName, const string& newPhone, int newDay, int newMonth, int newYear)
    {
        for (Contact& contact : contacts)
            if (contact.getLastName() == lastName && contact.getFirstName() == firstName && contact.getMiddleName() == middleName)
            {
                contact.setPhone(newPhone);
                contact.setDay(newDay);
                contact.setMonth(newMonth);
                contact.setYear(newYear);
                return;
            }
        throw invalid_argument("Контакт не найден");
    }

    Contact findContactByFullName(string lastName, string firstName, string middleName)
    {
        for (const Contact& contact : contacts)
            if (contact.getLastName() == lastName && contact.getFirstName() == firstName && contact.getMiddleName() == middleName)
                return contact;
        throw invalid_argument("Контакт не найден");
    }

    Contact findContactByPhone(string phone)
    {
        for (const Contact& contact : contacts)
            if (contact.getPhone() == phone)
                return contact;
        throw invalid_argument("Контакт не найден");
    }

    vector<Contact> getContactsByLetter(char letter)
    {
        vector<Contact> filteredContacts;
        for (const Contact& contact : contacts)
            if (contact.getLastName().front() == letter)
                filteredContacts.push_back(contact);
        return filteredContacts;
    }

    int getTotalContacts()
    {
        return contacts.size();
    }

    void addFavoriteContact(const string& lastName, const string& firstName, const string& middleName)
    {
        for (Contact& contact : contacts)
            if (contact.getLastName() == lastName && contact.getFirstName() == firstName && contact.getMiddleName() == middleName)
            {
                contact.setIsFavorite(true);
                return;
            }
        throw invalid_argument("Контакт не найден");
    }

    void removeFavoriteContact(const string& lastName, const string& firstName, const string& middleName)
    {
        for (Contact& contact : contacts)
            if (contact.getLastName() == lastName && contact.getFirstName() == firstName && contact.getMiddleName() == middleName)
            {
                contact.setIsFavorite(false);
                return;
            }
        throw invalid_argument("Контакт не найден");
    }

    vector<Contact> getFavoriteContacts()
    {
        vector<Contact> favoriteContacts;
        for (const Contact& contact : contacts)
            if (contact.getIsFavorite())
                favoriteContacts.push_back(contact);
        return favoriteContacts;
    }

    void deleteContact(Contact& contact)
    {
        contacts.erase(remove_if(contacts.begin(), contacts.end(), [&contact](const Contact& c) {
            return c.getLastName() == contact.getLastName() && c.getFirstName() == contact.getFirstName() && c.getMiddleName() == contact.getMiddleName(); }), contacts.end());
    }

    void saveContactsToFile(string filename)
    {
        ofstream file;
        file.open(filename);
        if (file.is_open())
        {
            for (const Contact& contact : contacts)
                file << contact.getLastName() << " " << contact.getFirstName() << " " << contact.getMiddleName() << " "
                << contact.getPhone() << " " << contact.getDay() << " " << contact.getMonth() << " " << contact.getYear() << " " << contact.getIsFavorite() << endl;
        }
        file.close();
    }   

    void readContactsFromFile(string filename)
    {
        ifstream file(filename);
        if (file.is_open()) 
        {
            string lastName, firstName, middleName, phone;
            int day, month, year;
            bool favorite;
            while (file >> lastName >> firstName >> middleName >> phone >> day >> month >> year >> favorite)
            {
                Contact newContact(lastName, firstName, middleName, phone, day, month, year, favorite);
                addContact(newContact);
            }
        }
        file.close();
    }
};

int main()
{
    system("chcp 1251");
    system("cls");
    Contacts myContacts;
    int choice;
    do {
        cout << "Выберите операцию:" << endl;
        cout << "1. Создать новый контакт" << endl;
        cout << "2. Изменить выбранный контакт" << endl;
        cout << "3. Найти контакт по ФИО" << endl;
        cout << "4. Найти контакт по телефону" << endl;
        cout << "5. Получить все контакты на заданную букву" << endl;
        cout << "6. Узнать текущее число контактов" << endl;
        cout << "7. Добавить контакт в список избранных" << endl;
        cout << "8. Удалить контакт из списка избранных" << endl;
        cout << "9. Получить все избранные контакты" << endl;
        cout << "10. Удалить контакт" << endl;
        cout << "11. Сохранить контакты в файл" << endl;
        cout << "12. Считать контакты из файла" << endl;
        cout << "0. Выход" << endl;
        cout << "Выбор: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            system("cls");
            string lastName, firstName, middleName, phone;
            int day, month, year;
            bool favorite;
            cout << "Введите фамилию: ";
            cin >> lastName;
            cout << "Введите имя: ";
            cin >> firstName;
            cout << "Введите отчество: ";
            cin >> middleName;
            cout << "Введите телефон: ";
            cin >> phone;
            cout << "Введите день рождения (день месяц год): ";
            cin >> day >> month >> year;
            cout << "Добавить этот контакт в избранное (0 - нет, 1 - да): ";
            cin >> favorite;
            Contact newContact(lastName, firstName, middleName, phone, day, month, year, favorite);
            myContacts.addContact(newContact);
            system("cls");
            cout << "Контакт успешно добавлен" << endl << endl;
            break;
        }
        case 2:
        {
            system("cls");
            string lastName, firstName, middleName;
            cout << "Введите фамилию нужного контакта: ";
            cin >> lastName;
            cout << "Введите имя нужного контакта: ";
            cin >> firstName;
            cout << "Введите отчество нужного контакта: ";
            cin >> middleName;
            try
            {
                myContacts.findContactByFullName(lastName, firstName, middleName);
                string newPhone;
                int newDay, newMonth, newYear;
                cout << "Введите новый телефон: ";
                cin >> newPhone;
                cout << "Введите новый день рождения (день месяц год): ";
                cin >> newDay >> newMonth >> newYear;
                myContacts.changeContact(lastName, firstName, middleName, newPhone, newDay, newMonth, newYear);
                system("cls");
                cout << "Контакт успешно изменен" << endl << endl;
            }
            catch (...)
            {
                system("cls");
                cout << "Контакт не найден" << endl << endl;
            }
            break;
        }
        case 3:
        {
            system("cls");
            string lastName, firstName, middleName;
            cout << "Введите фамилию нужного контакта: ";
            cin >> lastName;
            cout << "Введите имя нужного контакта: ";
            cin >> firstName;
            cout << "Введите отчество нужного контакта: ";
            cin >> middleName;
            try
            {
                system("cls");
                Contact foundContact = myContacts.findContactByFullName(lastName, firstName, middleName);
                cout << "Найден контакт:" << endl;
                cout << "Фамилия: " << foundContact.getLastName() << endl;
                cout << "Имя: " << foundContact.getFirstName() << endl;
                cout << "Отчество: " << foundContact.getMiddleName() << endl;
                cout << "Телефон: " << foundContact.getPhone() << endl;
                cout << "Дата рождения: " << foundContact.getDay() << "." << foundContact.getMonth() << "." << foundContact.getYear() << endl << endl;
            }
            catch (...)
            {
                system("cls");
                cout << "Контакт не найден" << endl << endl;
            }
            break;
        }
        case 4:
        {
            system("cls");
            string phone;
            cout << "Введите телефон нужного контакта: ";
            cin >> phone;
            try
            {
                system("cls");
                Contact foundContact = myContacts.findContactByPhone(phone);
                cout << "Найден контакт:" << endl;
                cout << "Фамилия: " << foundContact.getLastName() << endl;
                cout << "Имя: " << foundContact.getFirstName() << endl;
                cout << "Отчество: " << foundContact.getMiddleName() << endl;
                cout << "Телефон: " << foundContact.getPhone() << endl;
                cout << "Дата рождения: " << foundContact.getDay() << "." << foundContact.getMonth() << "." << foundContact.getYear() << endl << endl;
            }
            catch (...)
            {
                system("cls");
                cout << "Контакт не найден" << endl << endl;
            }
            break;
        }
        case 5:
        {
            system("cls");
            char letter;
            cout << "Введите букву: ";
            cin >> letter;
            vector<Contact> contactsByLetter = myContacts.getContactsByLetter(letter);
            if (contactsByLetter.empty())
            {
                system("cls");
                cout << "Контактов на заданную букву не найдено" << endl << endl;
            }
            else
            {
                system("cls");
                cout << "Контакты на букву '" << letter << "':" << endl;
                for (const Contact& contact : contactsByLetter)
                    cout << contact.getLastName() << " " << contact.getFirstName() << " " << contact.getMiddleName() << endl;
                cout << endl;
            }
            break;
        }
        case 6:
            system("cls");
            cout << "Текущее чисо контактов:" << myContacts.getTotalContacts() << endl << endl;
            break;
        case 7:
        {
            system("cls");
            string lastName, firstName, middleName;
            cout << "Введите фамилию нужного контакта: ";
            cin >> lastName;
            cout << "Введите имя нужного контакта: ";
            cin >> firstName;
            cout << "Введите отчество нужного контакта: ";
            cin >> middleName;
            try
            {
                myContacts.addFavoriteContact(lastName, firstName, middleName);
                system("cls");
                cout << "Контакт успешно добавлен в список избранных" << endl << endl;
            }
            catch (...)
            {
                system("cls");
                cout << "Контакт не найден" << endl << endl;
            }
            break;
        }
        case 8:
        {
            system("cls");
            string lastName, firstName, middleName;
            cout << "Введите фамилию нужного контакта: ";
            cin >> lastName;
            cout << "Введите имя нужного контакта: ";
            cin >> firstName;
            cout << "Введите отчество нужного контакта: ";
            cin >> middleName;
            try
            {
                myContacts.removeFavoriteContact(lastName, firstName, middleName);
                system("cls");
                cout << "Контакт успешно удален из списка избранных" << endl << endl;
            }
            catch (...)
            {
                system("cls");
                cout << "Контакт не найден" << endl << endl;
            }
            break;
        }
        case 9:
        {
            system("cls");
            vector<Contact> favoriteContacts = myContacts.getFavoriteContacts();
            if (favoriteContacts.empty())
                cout << "Нет избранных контактов" << endl << endl;
            else
            {
                cout << "Избранные контакты:" << endl;
                for (const Contact& contact : favoriteContacts)
                    cout << contact.getLastName() << " " << contact.getFirstName() << " " << contact.getMiddleName() << endl;
                cout << endl;
            }
            break;
        }
        case 10:
        {
            system("cls");
            string lastName, firstName, middleName;
            cout << "Введите фамилию нужного контакта: ";
            cin >> lastName;
            cout << "Введите имя нужного контакта: ";
            cin >> firstName;
            cout << "Введите отчество нужного контакта: ";
            cin >> middleName;
            try
            {
                Contact contactToDelete = myContacts.findContactByFullName(lastName, firstName, middleName);
                myContacts.deleteContact(contactToDelete);
                system("cls");
                cout << "Контакт успешно удален" << endl << endl;
            }
            catch (...)
            {
                system("cls");
                cout << "Контакт не найден" << endl << endl;
            }
            break;
        }
        case 11:
        {
            system("cls");
            string path;
            cout << "Введите путь к файлу для сохранения контактов: ";
            cin.ignore();
            getline(cin, path);
            myContacts.saveContactsToFile(path);
            system("cls");
            cout << "Контакты успешно сохранены в " << path << endl << endl;
            break;
        }
        case 12:
        {
            system("cls");
            string path;
            cout << "Введите путь к файлу для считывания контактов: ";
            cin.ignore();
            getline(cin, path);
            myContacts.readContactsFromFile(path);
            system("cls");
            cout << "Контакты успешно считаны из " << path << endl << endl;
            break;
        }
        case 0:
            system("cls");
            cout << "Выход из программы" << endl << endl;
            break;
        default:
            system("cls");
            cout << "Некорректный ввод" << endl << endl;
        }
    } while (choice != 0);
    system("pause");
    return 0;
}