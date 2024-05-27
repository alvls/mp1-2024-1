#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Credit {
private:
    string accountNumber;
    string password;
    double currentBalance;
    double creditAmount;
    int creditTerm;
    double interestRate;
    double monthlyPayment;
    bool approved;
    bool hasCredit;

    // ћетод дл€ проверки, €вл€етс€ ли текуща€ сумма достаточной дл€ шести ежемес€чных выплат по кредиту
    bool checkSufficientBalanceForPayments() {
        double totalPayments = monthlyPayment * 6;
        return currentBalance >= totalPayments;
    }

    // ћетод дл€ расчета процентной ставки в зависимости от суммы и срока кредита
    void calculateInterestRate() {
        if (creditTerm <= 3) {
            if (creditAmount < 100000) interestRate = 0.1;
            else if (creditAmount < 500000) interestRate = 0.12;
            else if (creditAmount < 1000000) interestRate = 0.15;
            else interestRate = 0.2;
        }
        else {
            if (creditAmount < 100000) interestRate = 0.15;
            else if (creditAmount < 500000) interestRate = 0.17;
            else if (creditAmount < 1000000) interestRate = 0.2;
            else interestRate = 0.25;
        }
    }

    // ћетод дл€ расчета ежемес€чного платежа
    double calculateMonthlyPayment() {
        double monthlyRate = interestRate / 12.0;
        int numberOfPayments = creditTerm * 12;
        double numerator = creditAmount * monthlyRate;
        double denominator = 1 - pow(1 + monthlyRate, -numberOfPayments);
        return numerator / denominator;
    }

public:
    Credit(string accountNum, string pass, double balance)
        : accountNumber(accountNum), password(pass), currentBalance(balance), creditAmount(0),
        creditTerm(0), interestRate(0), monthlyPayment(0), approved(false), hasCredit(false) {}

    // ћетод дл€ проверки авторизации клиента
    bool authorizeClient(string accountNum, string pass) {
        return (accountNum == accountNumber && pass == password);
    }

    // ћетод дл€ показа доступных кредитов
    void showAvailableCredits() {
        cout << "Available credits:\n";
        cout << "1. 1 year\n";
        cout << "2. 2 years\n";
        cout << "3. 3 years\n";
        cout << "4. 5 years\n";
        cout << "5. 15 years\n";
    }

    // ћетод дл€ проверки наличи€ активного кредита у клиента
    bool checkExistingCredit() {
        return hasCredit;
    }

    // ћетод дл€ проверки возможности получени€ выбранного кредита
    bool checkEligibility(double requestedAmount, int requestedTerm) {
        return (requestedAmount <= currentBalance && requestedTerm >= 1 && requestedTerm <= 15);
    }

    // ћетод дл€ получени€ кредита
    bool applyForCredit(double requestedAmount, int requestedTerm) {
        if (!checkEligibility(requestedAmount, requestedTerm)) {
            cout << "Credit application denied.\n";
            return false;
        }
        approved = true;
        hasCredit = true;
        creditAmount = requestedAmount;
        creditTerm = requestedTerm;
        calculateInterestRate();
        monthlyPayment = calculateMonthlyPayment();
        currentBalance += requestedAmount;
        return true;
    }

    // ћетод дл€ показа текущего состо€ни€ кредита
    void showCreditStatus() {
        cout << "Credit status:\n";
        cout << "Credit amount: " << creditAmount << " RUB\n";
        cout << "Credit term: " << creditTerm << " years\n";
        cout << "Monthly payment: " << monthlyPayment << " RUB\n";
        cout << "Approved: " << (approved ? "Yes" : "No") << "\n";
    }

    // ћетод дл€ проведени€ ежемес€чного платежа
    bool payMonthlyInstallment(double amount) {
        if (amount < monthlyPayment || !approved || !hasCredit) {
            cout << "Payment failed.\n";
            return false;
        }
        currentBalance -= amount;
        return true;
    }

    // ћетод дл€ досрочного погашени€ кредита
    bool payOffCredit() {
        if (!approved || !hasCredit) {
            cout << "No active credit to pay off.\n";
            return false;
        }
        currentBalance -= creditAmount;
        hasCredit = false;
        return true;
    }
};

class ProcessingCenter {
private:
    struct Client {
        string accountNumber;
        string fullName;
        double balance;
        Credit* creditPtr;
        string password;
    };

    vector<Client> clients;

public:
    bool addClient(string accountNum, string fullName, double balance, string password) {
        for (const auto& client : clients) {
            if (client.accountNumber == accountNum) {
                cout << "Client with this account number already exists.\n";
                return false;
            }
        }
        Client newClient = { accountNum, fullName, balance, nullptr, password };
        clients.push_back(newClient);
        return true;
    }

    bool removeClient(string accountNum) {
        for (auto it = clients.begin(); it != clients.end(); ++it) {
            if (it->accountNumber == accountNum) {
                clients.erase(it);
                return true;
            }
        }
        cout << "Client not found.\n";
        return false;
    }

    Credit* findClient(string accountNum) {
        for (auto& client : clients) {
            if (client.accountNumber == accountNum) {
                if (client.creditPtr == nullptr) {
                    client.creditPtr = new Credit(accountNum, client.password, client.balance);
                }
                return client.creditPtr;
            }
        }
        cout << "Client not found.\n";
        return nullptr;
    }
};

int main() {
    // ѕример использовани€ классов Credit и ProcessingCenter
    ProcessingCenter bank;

    // ƒобавление клиентов в базу данных банка
    bank.addClient("0001", "John Doe", 10000, "password1");
    bank.addClient("0002", "Jane Smith", 20000, "password2");

    // ѕолучение доступа к кредитам дл€ клиента John Doe
    Credit* johnsCredit = bank.findClient("0001");
    Credit* janesCredit = bank.findClient("0002");
    if (johnsCredit != nullptr) {
        // ѕример использовани€ методов класса Credit
        if (johnsCredit->authorizeClient("0001", "password1")) {
            johnsCredit->applyForCredit(10000, 1);
            johnsCredit->showCreditStatus();
        }
    }
    // ѕолучение доступа к кредитам дл€ клиента Jane Smith
    if (janesCredit != nullptr) {
        // ѕример использовани€ методов класса Credit - пароль неверный, следовательно, результаты даже не выведутс€ на экран
        if (janesCredit->authorizeClient("0002", "password2")) {
            janesCredit->applyForCredit(10000, 1);
            janesCredit->showCreditStatus();
        }
    }
    system("pause");
    return 0;
}
