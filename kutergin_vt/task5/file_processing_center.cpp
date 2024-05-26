#include "file_processing_center.h"
#include "file_credit.h"

void Processing_Center::createAccount(int acc_num, const string& full_name, const string& password, double acc_balance)
{
    // проверка на существование аккаунта с таким номером
    for (const auto& client : clients) // range-based цикл для прохода по контейнеру vector
    {
        if (client.acc_num == acc_num)
            throw runtime_error("Account with the same number already exists");
    }
    
    if (acc_num < 1 || acc_num > 9999) // проверка на корректность номера зарплатного счета
        throw out_of_range("Account number must be from 1 to 9999");
    
    if (password.length() <= 3) // проверка длины пароля
        throw runtime_error("Password must be longer than 3 characters");
    
    if (acc_balance < 0) // проверка начальной суммы
        throw invalid_argument("The initial balance must be non-negative");
    
    Client new_client(acc_num, full_name, acc_balance, password); // создание объекта структуры Client
    clients.push_back(new_client); // добавление нового клиента в базу данных (в конец вектора clients)
}

bool Processing_Center::authorizeClient(int acc_num, const string& password)
{
    for (const auto& client : clients) // range-based цикл для прохода по контейнеру vector
    {
        if (client.acc_num == acc_num && client.password == password) // клиент успешно авторизован
        {
            return true;
        }
    }
    return false;
}

Client& Processing_Center::getClientInfo(int acc_num)
{
    for (auto& client : clients) // range-based цикл для прохода по контейнеру vector
    // используется auto& вместо const auto&, потому что мы хотим возвращать ссылку на объект, который может быть изменент (вектор как поле структуры Client)
    {
        if (client.acc_num == acc_num) // клиент существует
            return client;
    }
    throw runtime_error("Client not found");
}

bool Processing_Center::isAvailableFor(int acc_num, const Credit& credit)
{
    Client user = getClientInfo(acc_num); // создание объекта структуры Client для получения информации о клиенте из Processing Center
    double amount_2 = credit.getAmount();
    int term_2 = credit.getTerm();
    double monthlyPayment = amount_2 / (term_2 * 12);
    if (amount_2 <= 3000000 && user.acc_balance >= monthlyPayment * 6)
        return true;
    return false;
}

vector<Credit> Processing_Center::getAvailableCredits(int acc_num)
{
    vector<Credit> availableCredits; // вектор для хранения доступных клиенту кредитов
    for (const auto& credit : credits) // range-based цикл для прохода по контейнеру vector
        if (isAvailableFor(acc_num, credit))
            availableCredits.push_back(credit);
    return availableCredits;
}

void Processing_Center::addCreditToClient(int acc_num, Credit& credit)
{
    for (auto& client : clients) // range-based цикл для прохода по контейнеру vector
        if (client.acc_num == acc_num) // клиент существует
        {
            client.client_credits.push_back(credit); // добавление кредита
            return; // успешное завершение работы функции
        }
    throw runtime_error("Client not found");
}

void Processing_Center::AddCredit(const Credit& credit)
{
    credits.push_back(credit);
}

void Processing_Center::updateUserBalance(int acc_num, double newBalance) {
    for (auto& client : clients)
        if (client.acc_num == acc_num)
        {
            client.acc_balance = newBalance;
            return; // После обновления баланса выходим из цикла
        }
    throw runtime_error("Client not found");
}



