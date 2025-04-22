//#include<iostream>
//using namespace std;
//
//class Bank{
//	
//	public:
//		//deposit by cash
//		void depositByCash(double &balance,double amount){
//			balance += amount;
//			cout<<"Depositing rs."<<balance<<" in cash."<<endl;
//		}
//		//digital payment
//		void depositByDigital(double &balance,double amount){
//			balance += amount;
//			cout<<"Depositing "<<balance<<" via digital payment."<<endl;
//		}
//		//deposit by upi
//		void depositByUpi(double &balance,double amount){
//			balance += amount;
//			cout<<"Depositing "<<balance<<" using UPI (gpay@upi)."<<endl;
//		}
//	
//};
//class Account{
//	string acc_holder;
//	int acc_number;
//	double balance;
//	Bank deposit_handle;
//	
//	public:
//		Account(string holder,int number,int bal){
//			acc_holder = holder;
//			acc_number = number;
//			balance = bal;
//		}
//		
//		void depositByCash(double amount){
//			deposit_handle.depositByCash(balance,amount);
//		}
//		void depositByDigital(double amount){
//			deposit_handle.depositByDigital(balance,amount);
//		}
//		void depositByUpi(double amount){
//			deposit_handle.depositByUpi(balance,amount);
//		}
//			
//		//operator overloading
//		Account operator+(Account &receiver){
//			double transfer_amount;
//			cout<<"enter the transfer amount from "<<acc_holder<<" to "<<receiver.acc_holder <<endl;;
//			cin>>transfer_amount;
//			
//			if(balance >= transfer_amount){
//				balance -= transfer_amount;
//				receiver.balance += transfer_amount;
//				cout<<"Transferring "<<transfer_amount<<"from "<<acc_holder<<"to"<<receiver.acc_holder<<endl;;
//			}else{
//				cout<<"insufficient balance"<<endl;
//			}
//			return *this;
//		}
//		void display(){
//			cout<<acc_holder<<" Balance"<<balance<<endl;
//		}
//};
//int main(){
//	Account a1("alice",1234,2000);
//	Account a2("john",3456,3000);
//	
//	a1.depositByCash(5000);
//	a1.depositByDigital(1500);
//	a1.depositByUpi(2500);
//	
//	a1.display();
//	a2.display();
//	
//	//operator overloading - transfer money
//	a1 = a1 + a2;
//	
//	a1.display();
//	a2.display();
//	
//	return 0;
//	
//}
#include<iostream>
using namespace std;

class Bank{
	
	public:
		// Deposit by cash
		void depositByCash(double &balance, double amount){
			balance += amount;
			cout << "Depositing rs." << amount << " in cash." << endl;
		}
		
		// Digital payment
		void depositByDigital(double &balance, double amount){
			balance += amount;
			cout << "Depositing rs." << amount << " via digital payment." << endl;
		}
		
		// Deposit by UPI
		void depositByUpi(double &balance, double amount){
			balance += amount;
			cout << "Depositing rs." << amount << " using UPI (gpay@upi)." << endl;
		}
};

class Account {
	string acc_holder;
	int acc_number;
	double balance;
	Bank deposit_handle;
	
	public:
		// Constructor with initial values
		Account(string holder, int number, double bal) {
			acc_holder = holder;
			acc_number = number;
			balance = bal;
		}
		
		// Deposit by cash
		void depositByCash(double amount){
			deposit_handle.depositByCash(balance, amount);
		}
		
		// Deposit by digital payment
		void depositByDigital(double amount){
			deposit_handle.depositByDigital(balance, amount);
		}
		
		// Deposit by UPI
		void depositByUpi(double amount){
			deposit_handle.depositByUpi(balance, amount);
		}
			
		// Operator overloading for money transfer
		Account operator+(Account &receiver) {
			double transfer_amount;
			cout << "Enter the transfer amount from " << acc_holder << " to " << receiver.acc_holder << ": ";
			cin >> transfer_amount;
			
			// Transfer logic
			if(balance >= transfer_amount) {
				balance -= transfer_amount;
				receiver.balance += transfer_amount;
				cout << "Transferring rs." << transfer_amount << " from " << acc_holder << " to " << receiver.acc_holder << "." << endl;
			} else {
				cout << "Insufficient balance." << endl;
			}
			return *this;
		}
		
		// Display account details
		void display() {
			cout << acc_holder << " (Account No: " << acc_number << ") Balance: rs." << balance << endl;
		}
};

int main() {
	Account a1("Alice", 1234, 2000.00);
	Account a2("John", 3456, 3000.00);
	
	// Deposits into Alice's account
	a1.depositByCash(5000);
	a1.depositByDigital(1500);
	a1.depositByUpi(2500);
	
	// Display balances
	a1.display();
	a2.display();
	
	// Transfer money from Alice to John
	a1 = a1 + a2;
	
	// Display balances after transfer
	a1.display();
	a2.display();
	
	return 0;
}


