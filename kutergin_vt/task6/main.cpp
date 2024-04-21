#include "file_credit.h"
#include "file_processing_center.h"

using namespace std;

int main(int argc, const char * argv[]) {
    try {
        Credit CRDT;
        Processing_Center PC;
        // заполним базу клиентов
        PC.createAccount(2343, "Иванов Иван Иванович", "qwerty123", 200000);
        PC.createAccount(3857, "Валентинов Валентин Валентинович", "123456789", 2500000);
        PC.createAccount(9999, "Андреев Андрей Андреевич", "secret_password999", 1000000);
        PC.createAccount(0001, "Ильин Илья Ильич", "1990_Ilyin_Ilya", 4050000);
        // заполним базу кредитов
        Credit CR1(1, 100000.0, 12.0);
        Credit CR2(1, 450000.0, 15.0);
        Credit CR3(2, 750000.0, 15.0);
        Credit CR4(3, 800000.0, 12.0);
        Credit CR5(3, 1000000.0, 18.0);
        Credit CR6(5, 1500000.0, 20.0);
        Credit CR7(5, 2000000.0, 22.0);
        Credit CR8(15, 3000000.0, 24.0);
        PC.addCreditToClient(3857, CR4);
        PC.AddCredit(CR1);
        PC.AddCredit(CR2);
        PC.AddCredit(CR3);
        PC.AddCredit(CR4);
        PC.AddCredit(CR5);
        PC.AddCredit(CR6);
        PC.AddCredit(CR7);
        PC.AddCredit(CR8);
        
        cout << "Welcome to Internet Bank" << endl;
        cout << "Please enter your account number: " << endl;
        int acc_num;
        cin >> acc_num;
        cout << "Please enter your password: " << endl;
        string password;
        cin >> password;
        if (!CRDT.authorize(acc_num, password, PC))
            throw invalid_argument("Authorization error");
        
        CRDT.showINFO(acc_num, PC);
        
        cout << "Select a credit from the Available credits menu (enter index):" << endl;
        int choice;
        cin >> choice;
        if (!CRDT.checkCreditExistence(acc_num, PC) && CRDT.checkCreditAvailability(acc_num, PC, choice)) // если у клиента нет кредитов и выбранный кредит пользователю доступен
        {
            CRDT.getCredit(acc_num, PC, choice);
            cout << "You have a credit " << choice << " approved" << endl;
        }
        else
            throw runtime_error("You can't get credit");
        CRDT.showCreditState(acc_num, PC);
        cout << "What part of the credit would you like to pay? " << endl;
        cout << "Enter the payment amount: " << endl;
        double payment;
        cin >> payment;
        CRDT.payInstallment(acc_num, PC, payment);
        CRDT.showCreditState(acc_num, PC);
        CRDT.payOffCredit(acc_num, PC);
        CRDT.showCreditState(acc_num, PC);
    } catch (const out_of_range& e) { // значение выходит за пределы допустимого диапазона
        cerr << "Error: " << e.what() << endl;
    } catch (const invalid_argument& e) { // аргумент недопустимого типа или значения
        cerr << "Error: " << e.what() << endl;
    } catch (const runtime_error& e) { // ошибка, возникающая во время выполнения программы
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}

