#include <iostream>
#include <string>
#include <limits>

using std::string;
using std::cout;
using std::cin;
using std::endl;

class BankAccount {
private:
    string accountHolderName;
    string accountNumber;
    double balance;

public:
    // Constructor
    BankAccount(string name, string accNumber, double initialBalance) 
        : accountHolderName(name), accountNumber(accNumber), balance(initialBalance) {}

    // Deposit function
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful. New balance: " << balance << endl;
        } else {
            cout << "Invalid deposit amount. Amount must be positive." << endl;
        }
    }

    // Withdraw function
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. Remaining balance: " << balance << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient funds." << endl;
        }
    }

    // Function to get balance
    double getBalance() const {
        return balance;
    }
};

// Function to display menu
void displayMenu() {
    cout << "\nBank Account Menu:" << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Check Balance" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to safely get a numeric input
double getValidAmount() {
    double amount;
    while (true) {
        cin >> amount;
        if (cin.fail() || amount < 0) {
            cin.clear(); // Clear error flag
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a positive numeric value: ";
        } else {
            break;
        }
    }
    return amount;
}

// Function to create an account
BankAccount* createAccount() {
    string name, accNumber;
    double amount;
    cout << "Enter account holder name: ";
    cin.ignore();
    std::getline(cin, name);
    cout << "Enter account number: ";
    cin >> accNumber;
    cout << "Enter initial balance: ";
    amount = getValidAmount();
    cout << "Account created successfully!" << endl;
    return new BankAccount(name, accNumber, amount);
}

// Function to handle deposit
void handleDeposit(BankAccount* account) {
    if (account) {
        cout << "Enter deposit amount: ";
        double amount = getValidAmount();
        account->deposit(amount);
    } else {
        cout << "No account found. Create an account first." << endl;
    }
}

// Function to handle withdrawal
void handleWithdraw(BankAccount* account) {
    if (account) {
        cout << "Enter withdrawal amount: ";
        double amount = getValidAmount();
        account->withdraw(amount);
    } else {
        cout << "No account found. Create an account first." << endl;
    }
}

// Function to display balance
void displayBalance(BankAccount* account) {
    if (account) {
        cout << "Current balance: " << account->getBalance() << endl;
    } else {
        cout << "No account found. Create an account first." << endl;
    }
}

int main() {
    BankAccount *myAccount = nullptr;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); // Clear error flag
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid choice. Please enter a valid option." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                if (myAccount) {
                    cout << "Account already exists." << endl;
                } else {
                    myAccount = createAccount();
                }
                break;
            case 2:
                handleDeposit(myAccount);
                break;
            case 3:
                handleWithdraw(myAccount);
                break;
            case 4:
                displayBalance(myAccount);
                break;
            case 5:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    delete myAccount; // Clean up dynamically allocated memory
    return 0;
}
