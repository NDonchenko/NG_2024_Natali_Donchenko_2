#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <QDate>

class Account
{
public:
    Account(int id, double bal, double loan, double dep ,double intRatLoan
            ,double intRatDeposit);
    void displayAccount() const;
    void Amountbalance(double newBalance);
    void withdrawAmountbalance(double amount);
    void adjustLoanAmount (double newloan);
    void amountRepayLoan(double loan);
    void depositAmount(double deposit);
    void refundDepositAmount();

    int getAccountID() const { return AccountID; };
    double getbalance() const {return balance;};
    double getloan() const {return loan;};
    double getdeposit() const {return deposit;};
    double getinterestRateLoan() const {return interestRateLoan;};
    double getinterestRateDeposit() const {return interestRateDeposit;};
    QDate getCreationDate() const {return creationDate;};

    void setbalance(double amount);
    void setloan(double amount);
    void setdeposit(double amount);
    void setinterestRateLoan(double interest);
    void setInterestRateDeposit(double interest);

private:

    int AccountID;
    double balance;
    double loan;
    double deposit;
    double interestRateLoan;
    double interestRateDeposit;
    QDate creationDate;

};

#endif // ACCOUNT_H
