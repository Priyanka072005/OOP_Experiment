#include <iostream>
#include<string>
#include<iomanip>
using namespace std;

int main() {
    int balance = 1000;
    int choice, amount;

    do {
        cout << "\nBank Menu" << endl;
        cout << "1. Check Balance" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

       switch (choice) {
            case 1:
                cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
                break;

            case 2:
                cout << "Enter deposit amount: $";
                cin >> amount;
                if (amount > 0) {
                    balance += amount;
                    cout << "Deposit successful. New balance: $" << fixed << setprecision(2) << balance << endl;
                } else {
                    cout << "Invalid amount. Please enter a positive number.\n";
                }
                break;

            case 3:
                cout << "Enter withdrawal amount: $";
                cin >> amount;
                if (amount > 0) {
                    if (balance >= amount) {
                        balance -= amount;
                        cout << "Withdrawal successful. New balance: $" << fixed << setprecision(2) << balance << endl;
                    } else {
                        cout << "Insufficient balance!\n";
                    }
                } else {
                    cout << "Invalid amount. Please enter a positive number.\n";
                }
                break;

            case 4:
                cout << "Exiting... Thank you for using our bank system.\n";
                break;

            default:
                cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }
    } while (choice != 4);

    return 0;
}

