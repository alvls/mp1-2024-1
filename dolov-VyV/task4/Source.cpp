#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <locale.h>

struct Birthday {
	int day, month, year;
};

class Contact {
public:
	std::string surname, name, patronymic, phone;
	Birthday birthday;
	bool isFavorite;

	Contact() : surname(""), name(""), patronymic(""), phone(""), birthday({ 0, 0, 0 }), isFavorite(false) {}
	Contact(std::string surname, std::string name, std::string patronymic, std::string phone, Birthday birthday, bool isFavorite = false) :
		surname(surname), name(name), patronymic(patronymic), phone(phone), birthday(birthday), isFavorite(isFavorite) {}
};

class Contacts {
	std::map<std::string, Contact> contacts;

public:
	void addContact(const Contact& contact) {
		std::string key = contact.surname + " " + contact.name + " " + contact.patronymic;
		contacts[key] = contact;
	}

	bool modifyContact(const std::string& key, const Contact& updatedContact) {
		if (contacts.find(key) != contacts.end()) {
			contacts.erase(key);  // ������� ������ ������
			addContact(updatedContact);  // ��������� ����������� �������
			return true;
		}
		return false;
	}

	Contact* findContactByFio(const std::string& fio) {
		if (contacts.find(fio) != contacts.end()) {
			return &contacts[fio];
		}
		return nullptr;
	}

	std::vector<Contact> findContactByPhone(const std::string& phone) {
		std::vector<Contact> result;
		for (const auto& pair : contacts) {
			if (pair.second.phone == phone) {
				result.push_back(pair.second);
			}
		}
		return result;
	}

	std::vector<Contact> getContactsByFirstLetter(char letter) {
		std::vector<Contact> result;
		for (const auto& pair : contacts) {
			if (pair.second.surname[0] == letter) {
				result.push_back(pair.second);
			}
		}
		return result;
	}

	size_t getContactsCount() const {
		return contacts.size();
	}

	void setFavorite(const std::string& key, bool isFavorite) {
		if (contacts.find(key) != contacts.end()) {
			contacts[key].isFavorite = isFavorite;
		}
	}

	std::vector<Contact> getAllFavorites() {
		std::vector<Contact> favorites;
		for (const auto& pair : contacts) {
			if (pair.second.isFavorite) {
				favorites.push_back(pair.second);
			}
		}
		return favorites;
	}

	bool removeContact(const std::string& key) {
		return contacts.erase(key) > 0;
	}

	void saveToFile(const std::string& filename) {
		std::ofstream file(filename, std::ios::app);
		if (file.is_open()) {
			for (const auto& pair : contacts) {
				const auto& contact = pair.second;
				file << contact.surname << ";" << contact.name << ";" << contact.patronymic << ";"
					<< contact.phone << ";" << contact.birthday.day << ";" << contact.birthday.month << ";"
					<< contact.birthday.year << ";" << contact.isFavorite << "\n";
			}
			file.close();
		}
		else {
			std::cerr << "������ ��� �������� ����� ��� ���������� ������." << std::endl;
		}
	}

	void loadFromFile(const std::string& filename) {
		std::ifstream file(filename);
		if (file.is_open()) {
			std::string line;
			while (std::getline(file, line)) {
				std::stringstream ss(line); // ������ ��� ��������, ������ ��� ��������� <sstream>
				std::string item;
				std::vector<std::string> tokens;

				while (std::getline(ss, item, ';')) {
					tokens.push_back(item);
				}

				if (tokens.size() >= 7) {
					Birthday birthday = { std::stoi(tokens[4]), std::stoi(tokens[5]), std::stoi(tokens[6]) };
					bool isFavorite = tokens.size() == 8 && tokens[7] == "1";
					Contact contact(tokens[0], tokens[1], tokens[2], tokens[3], birthday, isFavorite);
					addContact(contact);
				}
			}
			file.close();
		}
	}
};

int main() {
	setlocale(LC_ALL, "rus");
	Contacts myContacts;

	// ��������� ����� ��������
	Birthday bd1 = { 1, 1, 1990 };
	myContacts.addContact(Contact("������", "����", "��������", "1234567890", bd1, false));
	Birthday bd3 = { 2, 2, 2000 };
	myContacts.addContact(Contact("��������", "�����", "�������", "7890127845", bd3, false));
	Birthday bd2 = { 12, 12, 1992 };
	myContacts.addContact(Contact("������", "����", "��������", "0987654321", bd2, true));

	std::cout << "����� ���������� ���������: " << myContacts.getContactsCount() << std::endl;

	// ����� �������� �� ���
	std::string fio = "������ ���� ��������";
	Contact* foundContact = myContacts.findContactByFio(fio);
	if (foundContact != nullptr)
		std::cout << "������ ������� �� ���: " << foundContact->surname << " " << foundContact->name << " " << foundContact->patronymic << std::endl;
	else
		std::cout << "������� �� ������." << std::endl;

	// ����� ������� �� ������ ��������
	auto foundContactsByPhone = myContacts.findContactByPhone("1234567890");
	std::cout << "������(�) �������(�) �� ������ ��������: ";
	auto it = foundContactsByPhone.begin();
	for (; it != foundContactsByPhone.end(); ) {
		std::cout << it->surname << " " << it->name << " " << it->patronymic;
		++it;
		if (it != foundContactsByPhone.end()) {
			std::cout << ", ";
		}
	}
	std::cout << std::endl;

	// ������ ��� �������� �� �������� �����
	auto contactsByLetter = myContacts.getContactsByFirstLetter('�');
	std::cout << "�������� �� ����� '�':" << std::endl;
	for (auto& contact : contactsByLetter) {
		std::cout << contact.surname << " " << contact.name << " " << contact.patronymic << std::endl;
	}

	// ��������� ��������
	Birthday bdUpdate = { 2, 2, 1991 };
	myContacts.modifyContact(fio, Contact("������", "����", "���������", "1234567890", bdUpdate, false));

	// ������ ������� � ������ ���������
	myContacts.setFavorite("�������� ����� �������", true);

	// ������� ������� �� ������ ���������
	myContacts.setFavorite("������ ���� ��������", false);

	// ��������� ���� ��������� ���������
	auto favorites = myContacts.getAllFavorites();
	std::cout << "��������� �������� (" << favorites.size() << "):" << std::endl;
	for (auto& contact : favorites) {
		std::cout << contact.surname << " " << contact.name << " " << contact.patronymic << std::endl;
	}

	// �������� ��������
	myContacts.removeContact("������ ���� ���������");
	std::cout << "����� ���������� ��������� ����� ��������: " << myContacts.getContactsCount() << std::endl;

	// ���������� � ����
	myContacts.saveToFile("contacts.txt");

	// �������� �� �����
	myContacts.loadFromFile("contacts.txt");
	std::cout << "�������� ������� ��������� �� �����. ������� ���������� ���������: " << myContacts.getContactsCount() << std::endl;

	std::cin.get();
	return 0;
}