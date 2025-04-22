#include<iostream>
#include<string>
using namespace std;

class BankAccount{
	private:
		int accountNumber;
		string accountHolder;
		string accountType;
		double balance;
		
	public:
		//default constructor
		BankAccount(){
			accountHolder = "ram";
			accountNumber = 64537;
			accountType = "savings";
			balance = 5000;
		}
		//parameterized constructor
		BankAccount(string holder,int acNum,string acType,double bal){
			accountHolder = holder;
			accountNumber = acNum;
			accountType = acType;
			balance = bal;
		}
		
		//accessor method
		string getAccountHolder(){
			return accountHolder;
		}
		int getAccountNumber(){
			return accountNumber;
		}
		string getAccountType(){
			return accountType;
		}
		double getAccountBalance(){
			return balance;
		}
		
		//mutator method
		void setAccountType(string newType){
			accountType = newType;
		}
		
		void deposit(double amount){
			if(amount>0){
				balance = balance+amount;
				cout<<"-----------------------------------"<<endl;
				cout<<"Depositing "<<amount<<"....."<<endl;
				cout<<"New Balance: "<<balance<<endl;
			}else{
				cout<<"invalid deposit amount."<<endl;
			}
		}
		
		void withdraw(double amount){
			if(amount>0 && amount<=balance){
				balance = balance-amount;
				cout<<"Withdrawing "<<balance<<"....."<<endl;
				cout<<"New Balance: "<<balance<<endl;
				cout<<"------------------------------------"<<endl;
			}else{
				cout<<"insuffient balance or inavlid withdraw amount."<<endl;
			}
		}
		
		void displayAccountDetails(){
			cout<<"Account Details:\n";
			cout<<"Account Holder : "<<accountHolder<<endl;
			cout<<"Account Number : "<<accountNumber<<endl;
			cout<<"Account Type : "<<accountType<<endl;
			cout<<"Account Balance : "<<balance<<endl;
		}
};


int main() {
    BankAccount acc1("priyanka", 777777, "Savings", 5000.0);
    BankAccount acc2;

    acc1.displayAccountDetails();

    acc1.deposit(3000);
    acc1.withdraw(500);

    acc1.setAccountType("Current");
    cout << "Updated Account Type to " << acc1.getAccountType() << ".\n";

    cout << "Final Account Details:\n";
    acc1.displayAccountDetails();

    return 0;
}
