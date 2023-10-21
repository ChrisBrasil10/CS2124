/*
  Chris Brasil
  rec03.cpp
  September 24, 2023
  Implements Account Struct and Account Class
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct StructAccount {
    string name;
    int accountNumber;
};

// Task 2
// Define an Account class (use a different name than in Task 1)
class ClassAccount{
    friend ostream& operator<<(ostream& os, const ClassAccount& account);

public:
    ClassAccount(const string& name, int accountNumber)
            : name(name), accountNumber(accountNumber) {}

    const string& getName() const {return name;}
    int getAccountNumber() const {return accountNumber;}

private:
    string name;
    int accountNumber;
};

// ostream& operator<<(ostream& os, ClassAccount& account){
//   cout << "Name: " << account.getName() << "     " << account.getAccountNumber() << endl;
//   return os;
// }

ostream& operator<<(ostream& os, const ClassAccount& account){
    cout << "Name: " << account.name << "    " << account.accountNumber << endl;
    return os;
}

// Task 3
// Define an Account (use a different name than in Task 1&2) and
// Transaction classes

class Transaction {
    friend ostream& operator<<(ostream& os, const Transaction& transaction);
public:
    Transaction(const string& transactionType, int transactionAmount)
            : type(transactionType), amount(transactionAmount) {}

private:
    string type;
    int amount;
};

ostream& operator<<(ostream& os, const Transaction& transaction){
    cout << transaction.type << " " << transaction.amount << endl;
    return os;
}

class TransactionAccountClass{
    friend ostream& operator<<(ostream& os, const TransactionAccountClass& account);

public:
    TransactionAccountClass(const string& name, int accountNumber)
            : name(name), account_number(accountNumber) {}

    void deposit(int amount){
        transactionHistory.emplace_back("deposit", amount);
        accountBalance += amount;
    }

    void withdraw(int amount){
        if (amount > accountBalance){
            cout << "Account# " << account_number << " only has "
                 << accountBalance << ". Insufficient for withdrawal of "
                 << amount << endl;
        } else {
            transactionHistory.emplace_back("withdraw", amount);
            accountBalance -= amount;
        }
    }

    int getAccountNumber() const {return account_number;}

private:
    string name;
    int account_number;
    vector<Transaction> transactionHistory;
    int accountBalance{};
};

ostream& operator<<(ostream& os, const TransactionAccountClass& account){
    cout << account.name << " " << account.account_number << endl;
    for (const Transaction& transaction: account.transactionHistory){
        cout << '\t' << transaction;
    }
    return os;
}


// Task 4
// Define an Account with a nested public Transaction class
// (use different names than in the previous Tasks)


class Account4{
    friend ostream& operator<<(ostream& os, const Account4& account);

public:
    class Transaction2 {
        friend ostream& operator<<(ostream& os, const Transaction2& transaction);
    public:
        Transaction2(const string& type, int quantity)
                : type(type), quantity(quantity) {}

    private:
        string type;
        int quantity;
    };

    Account4(const string& aName, int some_account_number)
            : name(aName), account_number(some_account_number) {}

    void deposit(int amount){
        history.emplace_back("deposit", amount);
        balance += amount;
    }

    void withdraw(int amount){
        if (amount > balance){
            cout << "Account# " << account_number << " only has "
                 << balance << ". Insufficient for withdrawal of "
                 << amount << endl;
        } else {
            history.emplace_back("withdraw", amount);
            balance -= amount;
        }
    }

    int getAccountNumber() const {return account_number;}

private:
    string name;
    int account_number;
    vector<Transaction2> history;
    int balance{};
};

ostream& operator<<(ostream& os, const Account4& account){
    cout << account.name << " " << account.account_number << endl;
    for (const Account4::Transaction2& transaction: account.history){
        cout << '\t' << transaction;
    }
    return os;
}

ostream& operator<<(ostream& os, const Account4::Transaction2& transaction){
    cout << transaction.type << " " << transaction.quantity << endl;
    return os;
}

// Task 5
// Define an Account with a nested private Transaction class
// (use different names than in the previous Tasks)

class Account5{
    class Transaction3 {
        friend ostream& operator<<(ostream& os, const Transaction3& transaction);
    public:
        Transaction3(const string& aType, int aQuantity)
                : type(aType), quantity(aQuantity) {}

    private:
        string type;
        int quantity;
    };

    friend ostream& operator<<(ostream& os, const Account5& account);
    friend ostream& operator<<(ostream& os, const Transaction3& transaction);

public:

    Account5(const string& aName, int some_account_number)
            : name(aName), accountNumber(some_account_number) {}

    void deposit(int amount){
        transactionHistory.emplace_back("deposit", amount);
        balance += amount;
    }

    void withdraw(int amount){
        if (amount > balance){
            cout << "Account# " << accountNumber << " only has "
                 << balance << ". Insufficient for withdrawal of "
                 << amount << endl;
        } else {
            transactionHistory.emplace_back("withdraw", amount);
            balance -= amount;
        }
    }

    int getAccountNumber() const
    {return accountNumber;}

private:
    string name;
    int accountNumber;
    vector<Transaction3> transactionHistory;
    int balance{};
};

ostream& operator<<(ostream& os, const Account5& account){
    cout << account.name << " " << account.accountNumber << endl;
    for (const Account5::Transaction3& transaction: account.transactionHistory){
        cout << '\t' << transaction;
    }
    return os;
}

ostream& operator<<(ostream& os, const Account5::Transaction3& transaction){
    cout << transaction.type << " " << transaction.quantity << endl;
    return os;
}

void fileOpener(ifstream bankFiles, const string fileName);

int main() {

    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n";
    ifstream bankFiles;
    bankFiles.open("accounts.txt");
    if (!bankFiles){
        cout << "File didn't open" << endl;
        exit(1);
    }

    string name;
    int account_number;
    vector<StructAccount> accounts;

    while (bankFiles >> name >> account_number){
        StructAccount new_account;
        new_account.name = name;
        new_account.accountNumber = account_number;
        accounts.push_back(new_account);
    }

    bankFiles.close();

    for (const StructAccount& account: accounts){
        cout << "Name: " << account.name << "     " << account.accountNumber << endl;
    }

    //      1b
    cout << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";

    accounts.clear();

    bankFiles.open("accounts.txt");
    if (!bankFiles){
        cout << "File didn't open" << endl;
        exit(1);
    }

    while (bankFiles >> name >> account_number){
        StructAccount new_account{name, account_number};
        accounts.push_back(new_account);
    }

    bankFiles.close();

    for (const StructAccount& account: accounts){
        cout << "Name: " << account.name << "    " << account.accountNumber << endl;
    }

    accounts.clear();

    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:";
    cout << "\nFilling vector of class objects, using local class object:\n";

    vector<ClassAccount> newAccountVector;

    bankFiles.open("accounts.txt");
    if (!bankFiles){
        cout << "File didn't open" << endl;
        exit(1);
    }

    while (bankFiles >> name >> account_number){
        ClassAccount new_account(name, account_number);
        newAccountVector.push_back(new_account);
    }

    bankFiles.close();

    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";

    for (ClassAccount& account: newAccountVector){
        cout << "Name: " << account.getName() << "     " << account.getAccountNumber() << endl;
    }

    cout << "\nTask2c:\n";
    cout << "output using output operator as friend without getters\n";

    for (ClassAccount& account: newAccountVector){
        cout << account;
    }

    bankFiles.close();
    newAccountVector.clear();

    cout << "\nTask2d:\n";
    cout << "Filling vector of class objects, using temporary class object:\n";

    bankFiles.open("accounts.txt");
    if (!bankFiles){
        cout << "File didn't open" << endl;
        exit(1);
    }

    while (bankFiles >> name >> account_number){
        newAccountVector.push_back(ClassAccount(name, account_number));
    }

    for (ClassAccount& account: newAccountVector){
        cout << account;
    }

    bankFiles.close();
    newAccountVector.clear();

    cout << "\nTask2e:\n";
    cout << "Filling vector of class objects, using emplace_back:\n";

    bankFiles.open("accounts.txt");
    if (!bankFiles){
        cout << "File didn't open" << endl;
        exit(1);
    }

    while (bankFiles >> name >> account_number){
        newAccountVector.emplace_back(name, account_number);
    }

    for (const ClassAccount& account: newAccountVector){
        cout << account;
    }

    bankFiles.close();
    newAccountVector.clear();

    cout << "==============\n";
    cout << "\nTask 3:\nAccounts and Transaction:\n";

    bankFiles.open("transactions.txt");
    if (!bankFiles){
        cout << "File didn't open" << endl;
        exit(1);
    }

    vector<TransactionAccountClass> accounts3;
    string command;
    int quantity;

    while (bankFiles >> command){
        if (command == "Account"){
            bankFiles >> name >> account_number;
            accounts3.emplace_back(name, account_number);
            continue;
        } else {
            bankFiles >> account_number >> quantity;
            for (size_t i{}; i < accounts3.size(); i++){
                if (accounts3[i].getAccountNumber() == account_number){
                    if (command == "Deposit"){
                        accounts3[i].deposit(quantity);
                    } else {
                        accounts3[i].withdraw(quantity);
                    }
                }
            }
        }
    }

    for (const TransactionAccountClass& account: accounts3){
        cout << account << endl;
    }


    cout << "==============\n";
    cout << "\nTask 4:\nTransaction nested in public section of Account:\n";

    bankFiles.close();

    bankFiles.open("transactions.txt");
    if (!bankFiles){
        cout << "File didn't open" << endl;
        exit(1);
    }

    vector<Account4> accounts4;

    while (bankFiles >> command){
        if (command == "Account"){
            bankFiles >> name >> account_number;
            accounts4.emplace_back(name, account_number);
            continue;
        } else {
            bankFiles >> account_number >> quantity;
            for (size_t i{}; i < accounts4.size(); i++){
                if (accounts4[i].getAccountNumber() == account_number){
                    if (command == "Deposit"){
                        accounts4[i].deposit(quantity);
                    } else {
                        accounts4[i].withdraw(quantity);
                    }
                }
            }
        }
    }

    for (const Account4& account: accounts4){
        cout << account << endl;
    }

    cout << "==============\n";
    cout << "\nTask 5:\nTransaction nested in private section of Account:\n";

    bankFiles.close();

    bankFiles.open("transactions.txt");
    if (!bankFiles){
        cout << "File didn't open" << endl;
        exit(1);
    }

    vector<Account5> accounts5;

    while (bankFiles >> command){
        if (command == "Account"){
            bankFiles >> name >> account_number;
            accounts5.emplace_back(name, account_number);
            continue;
        } else {
            bankFiles >> account_number >> quantity;
            for (size_t i{}; i < accounts5.size(); i++){
                if (accounts5[i].getAccountNumber() == account_number){
                    if (command == "Deposit"){
                        accounts5[i].deposit(quantity);
                    } else {
                        accounts5[i].withdraw(quantity);
                    }
                }
            }
        }
    }

    for (const Account5& account: accounts5){
        cout << account << endl;
    }

    return 0;
}

void fileOpener(ifstream& bankFiles, const string fileName){
    bankFiles.open(fileName);
    if (!bankFiles.is_open()){
        cerr << "File could not be found" << endl;
        exit(1);
    }
}
