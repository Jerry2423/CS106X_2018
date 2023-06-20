#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <string>
#include <iostream>
using namespace std;


class BankAccount
{
public:
    BankAccount(string name, double balance);
    ~BankAccount();

    void withdraw(double amount);
    void deposit(double amount);
    double getBalance() const;
    string getName() const;

    //friend:访问private元素；you can touch my private...
    friend ostream& operator <<(ostream& out, const BankAccount& ba);

private:
    string name;
    double balance;
    static const double INTEREST_RATE;

};

bool operator ==(const BankAccount& ba1, const BankAccount& ba2);
//#include "bankaccount.cpp";
#endif // BANKACCOUNT_H
