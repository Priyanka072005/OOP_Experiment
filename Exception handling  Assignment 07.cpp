#include <iostream>
#include <stdexcept>
using namespace std;


class InsufficientFundsException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: Insufficient funds!";
    }
};

class InvalidTransactionException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: Invalid transaction!";
    }
};

class DivideByZeroException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: Cannot divide by zero!";
    }
};

// BankAccount Class
class BankAccount {
private:
    string ownerName;
    double balance;

public:
    // Constructor
    BankAccount(const string& name, double initialDeposit) {
        if (initialDeposit < 0)
            throw InvalidTransactionException();
        ownerName = name;
        balance = initialDeposit;
        cout << "Creating Account for " << ownerName << " with Initial Deposit: " << balance << endl;
    }

    // Deposit Function
    void deposit(double amount) {
        if (amount < 0)
            throw InvalidTransactionException();
        balance += amount;
        cout << "Depositing " << amount << " into " << ownerName << "'s Account" << endl;
    }

    // Withdraw Function
    void withdraw(double amount) {
        if (amount < 0)
            throw InvalidTransactionException();
        if (amount > balance)
            throw InsufficientFundsException();
        balance -= amount;
        cout << "Withdrawing " << amount << " from " << ownerName << "'s Account" << endl;
    }

    // Transfer Function
    void transfer(BankAccount& to, double amount) {
        if (amount < 0)
            throw InvalidTransactionException();
        if (amount > balance)
            throw InsufficientFundsException();
        withdraw(amount); 
        to.deposit(amount); 
        cout << "Transferring " << amount << " from " << ownerName << " to " << to.ownerName << endl;
    }

    // Divide Balance
    void divideBalance(double divisor) {
        if (divisor == 0)
            throw DivideByZeroException();
        balance /= divisor;
        cout << "Balance of " << ownerName << " after division: " << balance << endl;
    }

    // Display Function
    void display() const {
        cout << "Account Holder: " << ownerName << ", Balance: " << balance << endl;
    }
};


int main() {
    try {
        BankAccount rahul("Rahul Sharma", 5000);
        rahul.deposit(1000);
        rahul.display();

        try {
            rahul.withdraw(7000); 
        } catch (const exception& e) {
            cout << e.what() << endl;
        }

        BankAccount priya("Priya Verma", 0);
        rahul.transfer(priya, 3000);
        rahul.display();
        priya.display();

        try {
            rahul.divideBalance(0); 
        } catch (const exception& e) {
            cout << e.what() << endl;
        }

    } catch (const exception& e) {
        cout << "Unhandled Exception: " << e.what() << endl;
    }

    return 0;
}

