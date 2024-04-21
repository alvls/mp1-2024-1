#include "file_credit.h"
#include "file_processing_center.h"

int Credit::getTerm() const
{
    return term;
}

double Credit::getAmount() const
{
    return amount;
}

double Credit::getInterest_rate() const
{
    return interest_rate;
}

bool Credit::authorize(int acc_num, const string& password, Processing_Center& obj)
{
    return obj.authorizeClient(acc_num, password);
}

void Credit::showINFO(int acc_num, Processing_Center& obj)
{
    vector<Credit> availableCredits = obj.getAvailableCredits(acc_num); // создание вектора доступных клиенту кредитов
    cout << "Available credits for account " << acc_num << ":" << endl;
    int index = 1;
    for (const auto& credit : availableCredits) // range-based цикл для прохода по контейнеру vector
    {
        cout << index << ". Term: " << credit.term << " years, Amount: " << credit.amount << " rubles, Interest rate: " << credit.interest_rate << "%" << endl;
        index++;
    }
}

bool Credit::checkCreditExistence(int acc_num, Processing_Center& obj)
{
    Client user = obj.getClientInfo(acc_num); // создание объекта структуры Client для получения информации о клиенте из Processing Center
    if (!user.client_credits.empty()) // проверка на наличие кредитов (вектор не пустой)
        return true;
    else
        return false;
}

bool Credit::checkCreditAvailability(int acc_num, Processing_Center& obj, int index)
{
    vector<Credit> availableCredits = obj.getAvailableCredits(acc_num); // создание вектора доступных клиенту кредитов
    if (index >= 1 && index <= availableCredits.size()) // если индекс введен верно
    {
            Credit selectedCredit = availableCredits[index - 1]; // создание объекта класса Credit (выбранный кредит)
            Client user = obj.getClientInfo(acc_num); // создание объекта структуры Client для получения информации о клиенте из Processing Center
            double monthlyPayment = selectedCredit.amount / (selectedCredit.term * 12); // расчет ежемесячной выплаты (без учета процентов, т.к. рассматривается первый платеж)
            if (selectedCredit.amount <= 3000000 && user.acc_balance >= monthlyPayment * 6)
                return true;
            return false;
    }
    else
        throw out_of_range("Invalid index");
}

void Credit::getCredit(int acc_num, Processing_Center& obj, int index)
{
    vector<Credit> availableCredits = obj.getAvailableCredits(acc_num); // создание вектора доступных клиенту кредитов
    if (checkCreditAvailability(acc_num, obj, index)) // если кредит доступен для пользователя
    {
        Credit& selectedCredit = availableCredits[index - 1];
        obj.addCreditToClient(acc_num, selectedCredit); // добавляем ссылку на кредит
        
    }
}

void Credit::showCreditState(int acc_num, Processing_Center& obj) const
{
    Client user = obj.getClientInfo(acc_num); // создание объекта структуры Client для получения информации о клиенте из Processing Center
    Credit current_credit = user.client_credits[0]; // у клиента есть только один кредит (для простоты)
    cout << "Term: " << current_credit.term << " years, Amount: " << current_credit.amount << " rubles, Interest rate: " << current_credit.interest_rate << "%" << endl;
}

void Credit::payInstallment(int acc_num, Processing_Center& obj, double payment)
{
    Client& user = obj.getClientInfo(acc_num); // создание ссылки на объект структуры Client для получения информации о клиенте из Processing Center
    Credit& current_credit = user.client_credits[0]; // у клиента есть только один кредит (для простоты)
    if (payment < 0)
        throw invalid_argument("Payment amount must be non-negative");
    double monthlyInterestRate = current_credit.interest_rate / 100 / 12; // расчет процентов за месяц
    double newBalance = current_credit.amount * (1 + monthlyInterestRate); // новый баланс кредита
    double accruedAmount = newBalance - current_credit.amount; // начисленная на кредит сумма
    if (payment >= accruedAmount)
    {
        current_credit.amount = newBalance - payment; // часть кредита выплачена
        double balance_2 = user.acc_balance - payment; // сумма снята со счета пользователя
        obj.updateUserBalance(acc_num, balance_2);
    }
    else
        throw invalid_argument("Payment amount must not be less than the accrued amount");
    if (current_credit.amount < 0)
        current_credit.amount = 0; // кредит полностью погашен
}

void Credit::payOffCredit(int acc_num, Processing_Center& obj)
{
    Client& user = obj.getClientInfo(acc_num); // создание ссылки на объект структуры Client для получения информации о клиенте из Processing Center
    Credit& current_credit = user.client_credits[0]; // у клиента есть только один кредит (для простоты)
    double monthlyInterestRate = current_credit.interest_rate / 100 / 12; // расчет процентов за месяц
    double newBalance = current_credit.amount * (1 + monthlyInterestRate); // новый баланс кредита
    if (user.acc_balance >= newBalance)
    {
        current_credit.amount = 0;
        double balance_2 = user.acc_balance - newBalance; // сумма снята со счета пользователя
        obj.updateUserBalance(acc_num, balance_2);
    }
    else
        throw runtime_error("Insufficient funds to pay off credit");
}


