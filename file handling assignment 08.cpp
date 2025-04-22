#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class FileEncryptor {
private:
    string filename;
    int key;

public:
    FileEncryptor(string fname, int k) {
        filename = fname;
        key = k;
    }

    void encryptAndWrite(string message) {
        for (int i = 0; i < message.length(); ++i) {
            if (isalpha(message[i])) {
                char base = isupper(message[i]) ? 'A' : 'a';
                message[i] = (message[i] - base + key) % 26 + base;
            }
        }

        ofstream file(filename.c_str()); // Use .c_str() for Dev C++
        if (!file) {
            cout << "Error opening file for writing!" << endl;
            return;
        }

        file << message;
        file.close();
        cout << "Encrypted message saved to " << filename << endl;
    }

    void readAndDecrypt() {
        ifstream file(filename.c_str());
        if (!file) {
            cout << "Cannot open file: " << filename << endl;
            return;
        }

        string encrypted = "", line;
        while (getline(file, line)) {
            encrypted += line;
        }
        file.close();

        for (int i = 0; i < encrypted.length(); ++i) {
            if (isalpha(encrypted[i])) {
                char base = isupper(encrypted[i]) ? 'A' : 'a';
                encrypted[i] = (encrypted[i] - base - key + 26) % 26 + base;
            }
        }

        cout << "Decrypted Message: " << encrypted << endl;
    }
};

int main() {
    FileEncryptor fe("data.txt", 3);
    int choice;
    string message;

    while (true) {
        cout << "\n1. Encrypt and Save Message\n2. Read and Decrypt Message\n3. Exit\nChoose: ";
        cin >> choice;
        cin.ignore(); // Clear the newline character

        if (choice == 1) {
            cout << "Enter message: ";
            getline(cin, message);
            fe.encryptAndWrite(message);
        }
        else if (choice == 2) {
            fe.readAndDecrypt();
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid option!\n";
        }
    }

    return 0;
}

