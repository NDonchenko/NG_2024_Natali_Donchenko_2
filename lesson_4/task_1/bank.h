#ifndef BANK_H
#define BANK_H
#include<string>
#include<vector>
#include "Account.h"

using namespace std;

class bank
{
public:
    bank();
    void createAccount();
    void displayAccounts();
    void takeLoan(int AccountID,double loan);
    void repayLoan(int AccountID,double loan);
    void deposit(int AccountID,double deposit);
    void withdrawDeposit(int AccountID);
    void putMoneybalance(int AccountID,double newBalans);
    void withdrawMoneyBalance(int AccountID,double newBalans);
    void deleteAccount(int AccountID);

private:
    vector<Account>accounts;
    double percentToReturn;
    double percentageToPay;
};

#endif // BANK_H
