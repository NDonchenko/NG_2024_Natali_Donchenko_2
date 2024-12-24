#include <iostream>
#include "bank.h"
#include "account.h"

using namespace std;

int main()
{
    bank myBank;
    int choice = 0;
    int choiceAD = 0;
    double amountLoan = 0;
    double refundAmount = 0;
    double amountDeposit =0;
    double amountBalance = 0;

    while(true){

        cout<<"1.Create Account"<<endl;
        cout<<"2.Display Account"<<endl;
        cout<<"3.Put money on the balance"<<endl;
        cout<<"4.Withdraw money from the balance"<<endl;
        cout<<"5.Take a loan"<<endl;
        cout<<"6.Repay a loan"<<endl;
        cout<<"7.Put money on deposit"<<endl;
        cout<<"8.Withdraw money from the deposit"<<endl;
        cout<<"9.Delete Account"<<endl;
        cout<<"10.Exit"<<endl;
        cin>>choice;

        switch (choice) {
        case 1:
            myBank.createAccount();
            break;
        case 2:
            myBank.displayAccounts();
            break;
        case 3:
            cout<<"enter the number of the account to which you want to put money on the balance "<<endl;
            cin>> choiceAD;
            cout<<"what amount you want to put on the balance? "<<endl;
            cin>> amountBalance;
            myBank.putMoneybalance(choiceAD,amountBalance);
            break;
        case 4:
            cout<<"enter the account number to which you want to withdraw money "<<endl;
            cin>> choiceAD;
            cout<<"what amount you want to withdraw? "<<endl;
            cin>> amountBalance;
            myBank.withdrawMoneyBalance(choiceAD,amountBalance);
            break;
        case 5:
            cout<<"enter the account number from which you want to take a loan "<<endl;
            cin>> choiceAD;
            cout<<"enter the amount you want to borrow "<<endl;
            cin>> amountLoan;
            myBank.takeLoan(choiceAD,amountLoan);
            break;
        case 6:
            cout<<"enter the account number from which you want to repay a loan "<<endl;
            cin>> choiceAD;
            cout<<"enter the amount you want to return "<<endl;
            cin>> refundAmount;
            myBank.repayLoan(choiceAD,refundAmount);
            break;
        case 7:
            cout<<"enter the account number to which you want to deposit money"<<endl;
            cin>>choiceAD;
            cout<<"enter the amount you want to deposit on the account"<<endl;
            cin>>amountDeposit;
            myBank.deposit(choiceAD,amountDeposit);
            break;
        case 8:
            cout<<"enter the account number from which you want to withdraw funds"<<endl;
            cin>>choiceAD;
            myBank.withdrawDeposit(choiceAD);
            break;
        case 9:
            cout<<"enter the account number from which you want to delete "<<endl;
            cin>> choiceAD;
            myBank.deleteAccount(choiceAD);
            break;
        default:
            break;
        }
        if(choice==10){
            break;
        }
    }

    return 0;
}
