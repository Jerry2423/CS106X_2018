#include "bankaccount.h"

BankAccount::BankAccount(string name, double balance = 0)
{
    this->name = name;
    if (balance < 0) {
        throw "invalid behavior";
    }
    this->balance = balance;
}

//~ClassName: destructor内存管理
BankAccount::~BankAccount() {
    cout << "delete for " << *this << endl;
}

//void,returnType放在BankAccount::前面
void BankAccount::deposit(double amount) {
    if (amount <= 0) {
        throw amount;
    }
    this->balance += amount;
}

void BankAccount::withdraw(double amount) {
    if (amount > this->balance) {
        throw "invalid behavior";
    }
    this->balance -= amount;
}

double BankAccount::getBalance() const //函数后面加const确保不改变函数值
{
    return this->balance;
}

string BankAccount::getName() const
{
    return this->name;
}

//外面初始化static变量，不能用constructor
const double BankAccount::INTEREST_RATE = 0.25;

//operator无需ClasName::
bool operator ==(const BankAccount& ba1, const BankAccount& ba2) { //const pass by reference;区分参数const和函数后面加const（只适用于class内部函数）
    return ba1.getBalance() == ba2.getBalance() && ba1.getName() == ba2.getName();
}

ostream& operator <<(ostream& out, const BankAccount& ba) {
    out << "Name: " << ba.name << ";Balance: " << ba.balance;
    return out;
}
