#include <iostream>
#include "bank.h"
#include<vector>

bank::bank() {}

using namespace std;

void bank::createAccount(){
    int AccountID = 0;
    double balance = 0;
    double loan = 0;
    double deposit= 0;
    double interestRateLoan=0;
    double interestRateDeposit=0;

    cout<<"Enter the account number"<<endl;
    cin>>AccountID;
    cout<<"Enter the opening balance"<<endl;
    cin>>balance;

    accounts.emplace_back(AccountID,balance,loan,deposit,interestRateLoan,interestRateDeposit);
}
void bank::displayAccounts() {

    for (vector<Account>::iterator it = accounts.begin(); it!= accounts.end(); it++){
        Account currentAccount = *it;
        currentAccount.displayAccount();
    }
}
void bank::takeLoan(int AccountID,double loan){

    for (vector<Account>::iterator it = accounts.begin(); it!= accounts.end(); it++){
        Account& currentAccount = *it;
        if (currentAccount.getAccountID()== AccountID){
            currentAccount.adjustLoanAmount(loan);
        }
    }
}
void  bank::repayLoan(int AccountID,double loan){

    for (vector<Account>::iterator it = accounts.begin(); it!= accounts.end(); it++){
        Account& currentAccount = *it;
        if (currentAccount.getAccountID()== AccountID){
            currentAccount.amountRepayLoan(loan);
        }
    }
}
void bank::deposit(int AccountID,double deposit){

    for (vector<Account>::iterator it = accounts.begin(); it!= accounts.end(); it++){
        Account& currentAccount = *it;
        if (currentAccount.getAccountID()== AccountID){
            currentAccount.depositAmount(deposit);
        }
    }
}
void bank::withdrawDeposit(int AccountID){

    for (vector<Account>::iterator it = accounts.begin(); it!= accounts.end(); it++){
        Account& currentAccount = *it;
        if (currentAccount.getAccountID()== AccountID){
            currentAccount.refundDepositAmount();
        }
    }
}
void bank::putMoneybalance(int AccountID,double newBalance){
    for (vector<Account>::iterator it = accounts.begin(); it!= accounts.end(); it++){
        Account& currentAccount = *it;
        if (currentAccount.getAccountID()== AccountID){
            currentAccount.Amountbalance(newBalance);
        }
    }
}
void bank::withdrawMoneyBalance(int AccountID,double amount){

    for (vector<Account>::iterator it = accounts.begin(); it!= accounts.end(); it++){
        Account& currentAccount = *it;
        if (currentAccount.getAccountID()== AccountID){
            currentAccount.withdrawAmountbalance(amount);
        }
    }
}

void bank::deleteAccount(int AccountID){
    for (vector<Account>::iterator it = accounts.begin(); it!= accounts.end(); it++){
        if (it ->getAccountID()== AccountID){
            if (it ->getbalance() == 0 || it ->getloan() == 0 || it ->getdeposit() == 0 ){
                accounts.erase(it);
                cout<<"Account number"<< AccountID << "has been deleted."<<endl;
            }else{
                cout<<"Account number"<< AccountID << "can't be deleted, the balance of funds is not zero"<<endl;
            }
        }
    }
}

