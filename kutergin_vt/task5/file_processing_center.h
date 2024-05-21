#ifndef file_processing_center_h
#define file_processing_center_h

#include <string>
#include <vector>
#include <stdexcept>
#include "file_credit.h"

using namespace std;

class Credit;

struct Client {
    int acc_num; // номер зарплатного счета
    string full_name; // ФИО
    double acc_balance; // сумма на счету
    vector<Credit> client_credits; // вектор кредитов, связанных с клиентом
    string password; // пароль
    
    Client(int acc_num2, const string& full_name2, double acc_balance2, const string& password2) : acc_num(acc_num2), full_name(full_name2), acc_balance(acc_balance2), password(password2) {} // конструктор-инициализатор
};

class Processing_Center
{
private:
    vector<Client> clients; // база клиентов
    vector<Credit> credits; // база кредитов, предоставляемых банков
public:
    void createAccount(int acc_num, const string& full_name, const string& password, double acc_balance); // функция, создающая аккаунт клиента в базе клиентов
    
    bool authorizeClient(int acc_num, const string& password); // функция, допускающая возможность авторизации клиента
    
    Client& getClientInfo(int acc_num); // функция (абстрактного типа Client), вовзращающая информацию о клиенте по его номеру зарплатного счета
    
    bool isAvailableFor(int acc_num, const Credit& credit);  // функция, проверяющая доступен ли кредит для конкректного клиента (пользователь не выбирает - формируется вектор доступных кредитов)
    
    vector<Credit> getAvailableCredits(int acc_num); // функция, возвращающая доступные клиенту кредиты
    
    void addCreditToClient(int acc_num, Credit& credit); // функция, добавляющая кредит в вектор кредитов client_credits
    
    void AddCredit(const Credit& credit); // функция, добавляющая кредит в вектор credits
    
    void updateUserBalance(int acc_num, double newBalance); // функция, обновляющая баланс пользователя
};

#endif

