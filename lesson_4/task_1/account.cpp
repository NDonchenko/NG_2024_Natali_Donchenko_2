#include "account.h"
#include <iostream>
#include <vector>
#include <QDate>

using namespace std;

Account::Account(int id, double bal, double loan, double dep ,double intRatLoan
                 ,double intRatDeposit)  : AccountID(id), balance(bal),
    loan(loan), deposit(dep),interestRateLoan(intRatLoan),
    interestRateDeposit(intRatDeposit){
    creationDate = QDate::currentDate();
}

void Account::displayAccount()const{

    cout<<"Account ID:"<< AccountID <<endl
         <<"balance:"<< balance<<endl
         <<"loan:"<< loan<<endl
         <<"deposit:"<< deposit<<endl
         <<"interest Rate Loan:"<< interestRateLoan<<endl
         <<"interest Rate Deposit:"<< interestRateDeposit<<endl;
            qDebug()<< "Creation Date:" << creationDate.toString("yyyy-MM-dd");

}

void Account::setbalance(double amount){
    balance = amount;
    cout<<"Your balance is: "<<balance<<endl;
}
void Account::setloan(double amount){
    loan = amount;
    cout<<"Your credit balance is: "<<loan<<endl;
}
void Account::setdeposit(double amount){
    deposit = amount;
    cout<<"Уour deposit balance is: "<<deposit<<endl;
}
void  Account::setinterestRateLoan(double interest){
    interestRateLoan = interest;
}
void Account::setInterestRateDeposit(double interest){
    interestRateDeposit = interest;
}

void Account:: Amountbalance(double newBalance){
    double AmountNewBalance = balance + newBalance;
    setbalance(AmountNewBalance);
}
void Account::withdrawAmountbalance(double amount){
    double AmountNewBalance = balance - amount;
    setbalance(AmountNewBalance);
}
void Account::adjustLoanAmount(double newloan){
    double interest = 0;
    cout<<"At what interest rate is the loan issued?"<<endl;
    cin>>interest;
    setinterestRateLoan(interest);
    double percentageToPay = (loan+newloan)*interestRateLoan/100;
    double amount = loan += newloan + percentageToPay;
    setloan(amount);

}
void  Account::amountRepayLoan(double refundAmount){
    double newLoan = loan - refundAmount;
    setloan(newLoan);
}
void Account::depositAmount(double newdeposit){
    double interest = 0;
    cout<<"At what percentage do you want to deposit money?"<<endl;
    cin>>interest;
    setInterestRateDeposit(interest);
    //double percentageToPay = (deposit+newloan)*interestRateLoan/100;
    setdeposit(newdeposit);

}
void Account::refundDepositAmount(){
    string answer;
    double percentagePay= 0;
    double AmountToPaid = 0;
    double remainder = 0;
    cout<<"The amount in your deposit account compares"<< getdeposit()<<endl;
    cout<<"you want to withdraw the entire amount, if YES then you will get interest on the amount "
            "and if NOT then you will lose the interest"<<endl;
    cin>>answer;
    if(answer== "YES"){
        percentagePay = deposit*interestRateLoan/100;
        double AmountToPaid = deposit+percentagePay;
        cout<<"great, you get sum: "<<AmountToPaid<<endl;
        remainder = deposit-deposit;
        setdeposit(remainder);
    }else if(answer== "NOT"){
        cout<<"how much do you want to withdraw?"<<endl;
        cin>>AmountToPaid;
        remainder = deposit-AmountToPaid;
        cout<<"great, you get sum: "<<AmountToPaid<<endl;
        setdeposit(remainder);
    }
}
