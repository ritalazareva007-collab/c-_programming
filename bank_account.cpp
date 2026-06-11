#include <iostream>
#include <string>
#include <stdexcept>

class BankAccount {
public:
    BankAccount() = default; // конструктор по умолчанию
    explicit BankAccount(std::string full_name) { // конструктор
        this -> name = std::move(full_name);
        this -> current_val = 0.0;
        this -> number = 23765;
    }
    virtual ~BankAccount() = default;
    // метод снятия денежных средств со счета
    void withdraw(float summ) {
        if (current_val > summ) {
            current_val -= summ;
            std::cout << "withdrawn " << summ << " balance: " << current_val << std::endl;
        }
        else { // обработка исключений
            throw std::runtime_error{" Error: there is not enough money in account"};
        }
    }

    // метод вывода информации об аккаунте на экран
    virtual void list() const{
        std::cout << "name: " << name << std::endl;
        std::cout << "number of account: " << number << std::endl;
        std::cout << "current value: " << current_val << std::endl;

    }

    // метод пополнения денежных средств
    void deposit(float summ) {
        if (summ > 0) {
            current_val += summ;
        }
        // обработка исключений
        else {
            throw std::runtime_error {"Error: wrong sum for deposit, try again"};
        }
    }
protected:
    // поля класса
    int number;
    std::string name;
    float current_val;
};

class SavingAccount: public BankAccount {
public:
    // конструктор
    explicit SavingAccount(float percent, std::string full_name): BankAccount(std::move(full_name)) {
        this -> percent = percent;
    }
    // метод вывода процентной ставки на экран
    void applyInterest() {
        // рассчитываем процент
        float interest = current_val * (percent / 100.0f);
        // добавляем процент к счету
        if (interest > 0) {
            deposit(interest);
        }
        // бросаем исключение если пополнение на 0 или отрицательное число
        else {
            throw std::runtime_error {"Error: wrong sum for deposit, try again"};
        }
    }
    // переопределенная функция вывода для производного класса с информацией о процентной ставке
    void list() const override {
        BankAccount::list();
        std::cout << " check deposited on " <<  percent << "%" << std::endl;
        std::cout << "balance is: " << current_val << std::endl;
    }
    // поле производного класса
private:
    float percent;
};

int main() {
    // считываем имя пользователя
    std::string username;
    std::cout << "enter your name: " << std::endl;
    std::getline(std::cin, username);
    float percent {0.0f};
    std::cout << "enter percent" << std::endl;
    std::cin >> percent;
    // создаем объект класса
    SavingAccount Account(percent, username);
    // создаем указатель на объект
    SavingAccount * ptr {&Account};
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
    // кладем деньги на счет
    float num_1;
    std::cout << "if you want top up your bank account - enter sum, else enter 0: ";
    std::cin >> num_1;
    if (num_1 > 0) {
        // ловим исключения
        try {
            ptr->deposit(num_1);
        }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
    // снимаем деньги со счета
    float num_2;
    std::cout << "if you want withdraw money - enter sum, else enter 0: ";
    std::cin >> num_2;
    if (num_2 > 0) {
        // ловим исключения
        try {
            ptr->withdraw(num_2);
        }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
    // выводим всю информацию о пользователе на экран
    try {
        ptr->applyInterest();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    ptr->list();
    return 0;
}
