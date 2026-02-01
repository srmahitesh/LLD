//Liskov's Substitution Principle states that any methods that use a base class should also be able to use a derived class without knowing it.
// Functionality of child class should not be narrowdown & always be extented ithout breaking the base class functionality.
#include <bits/stdc++.h>
using namespace std;

class AccountWithDepositOnly {
    protected:
    float bal;
    int accountNo;

    public:
    AccountWithDepositOnly(){
        bal = 0;
        accountNo = rand() % 100000;
    }

    void deposit(float amount){
        if(amount <= 0){
            cout<<"Invalid Deposit Amount"<<endl;
            return;
        }
        bal += amount;
        cout<<"Amount of Rs. "<<amount<<" Deposited Successfully"<<endl;
    }
};

class AccountWithWithdraw: public AccountWithDepositOnly {
    public:
    void withdraw(float amount){
        if(amount <= 0){
            cout<<"Invalid Withdraw Amount"<<endl;
            return;
        }

        if (amount > bal){
            cout<<"Insufficient Balance."<<endl;
            return;
        }

        bal -= amount;
        cout<<"Amount of Rs. "<<amount<<" Withdrawn Successfully"<<endl;
    }
};

class FD: public AccountWithDepositOnly {

};

class SavingsAccount: public AccountWithWithdraw {

};

class CurrentAccount: public AccountWithWithdraw {

};

int main() {
    AccountWithDepositOnly *a = new SavingsAccount();
    a->deposit(1200);
    AccountWithWithdraw *aw = new CurrentAccount();
    aw->withdraw(100);
    aw->deposit(200);
    aw->withdraw(150);
    return 0;
}
