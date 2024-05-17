#ifndef file_credit_h
#define file_credit_h

#include <iostream>
#include <string>

using namespace std;

class Processing_Center;

class Credit
{
private:
    int term; // срок (года в целых числах)
    double amount; // сумма кредита
    double interest_rate; // процентная ставка по кредиту (проценты - целые числа)
public:
    Credit() : term(0), amount(0.0), interest_rate(0.0) {} // конструктор по умолчанию
    Credit(int term2, double amount2, double interest_rate2) : term(term2), amount(amount2), interest_rate(interest_rate2) {} // конструктор-инициализатор
    ~Credit() {} // деструктор
    
    int getTerm() const; // функция, возвращающая приватный член term
    double getAmount() const; // функция, возвращающая приватный член amount
    double getInterest_rate() const; // функция, возвращающая приватный член interest_rate
    
    bool authorize(int acc_num, const string& password, Processing_Center& obj); // функция, авторизующая клиента
    
    void showINFO(int acc_num, Processing_Center& obj);  // функция, показывающая информацию о доступных клиенту кредитах
    
    bool checkCreditExistence(int acc_num, Processing_Center& obj); // функция, проверяющая наличие взятого в банке кредита
    
    bool checkCreditAvailability(int acc_num, Processing_Center& obj, int index); // функция, проверяющая возможность получения выбранного кредита (пользователь выбирает)

    void getCredit(int acc_num, Processing_Center& obj, int index); // функция, выдающая клиенту выбранный кредит
    
    void showCreditState(int acc_num, Processing_Center& obj) const; // функция, показывающая текущее состояние кредита
    
    void payInstallment(int acc_num, Processing_Center& obj, double payment); // функция, погашающая начисления по кредиту
    // будем считать, что клиент выплачивает часть кредита раз в месяц. Тогда каждый раз когда пользователь хочет выплатить некоторую сумму (1 раз / месяц), вызывается метод payInstallment и баланс кредита обновляется с учетом процентов
    
    void payOffCredit(int acc_num, Processing_Center& obj); // функция, досрочно погашающая кредит
    // будем считать, что клиент выплачивает часть кредита или весь кредит раз в месяц. Тогда каждый раз когда пользователь хочет выплатить некоторую сумму (1 раз / месяц) или погасить его, вызывается метод payOffCredit и баланс кредита обновляется с учетом процентов
};

#endif 

