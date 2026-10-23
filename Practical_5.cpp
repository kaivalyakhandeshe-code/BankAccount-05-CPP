
#include <iostream>
#include <string>
using namespace std;

class AccountAudit;

class BankAccount
{
private:
    int accountNo;
    string holderName;
    float openingBalance;
    float transaction1, transaction2, transaction3;

    static int accountCount;

public:
    // Constructor using this pointer
    BankAccount(int accountNo, string holderName,
                float openingBalance, float transaction1,
                float transaction2, float transaction3)
    {
        this->accountNo = accountNo;
        this->holderName = holderName;
        this->openingBalance = openingBalance;
        this->transaction1 = transaction1;
        this->transaction2 = transaction2;
        this->transaction3 = transaction3;

        accountCount++;
    }

    // Inline function to calculate total transactions
    inline float calculateTotal()
    {
        return transaction1 + transaction2 + transaction3;
    }

    // Inline function to calculate average transaction
    inline float calculateAverage()
    {
        return calculateTotal() / 3.0;
    }

    // Inline function to calculate current balance
    inline float calculateCurrentBalance()
    {
        return openingBalance + calculateTotal();
    }

    // Display account details
    inline void displayDetails()
    {
        cout << "\nAccount Number    : " << accountNo;
        cout << "\nAccount Holder    : " << holderName;
        cout << "\nOpening Balance   : Rs. " << openingBalance;
        cout << "\nTransaction 1     : Rs. " << transaction1;
        cout << "\nTransaction 2     : Rs. " << transaction2;
        cout << "\nTransaction 3     : Rs. " << transaction3;
        cout << "\nTotal Transactions: Rs. " << calculateTotal();
        cout << "\nAverage Transaction: Rs. " << calculateAverage();
        cout << "\nCurrent Balance   : Rs. " << calculateCurrentBalance()
             << endl;
    }

    int getAccountNo()
    {
        return accountNo;
    }

    // Static member function
    static void displayAccountCount()
    {
        cout << "\nTotal Accounts Created: "
             << accountCount << endl;
    }

    friend class AccountAudit;
};

// Initialize static data member
int BankAccount::accountCount = 0;


// Friend class for account auditing
class AccountAudit
{
public:
    void auditAccount(BankAccount &b)
    {
        float total = b.transaction1 + b.transaction2
                    + b.transaction3;

        float average = total / 3.0;

        float highest = b.transaction1;
        float lowest = b.transaction1;

        if (b.transaction2 > highest)
            highest = b.transaction2;

        if (b.transaction3 > highest)
            highest = b.transaction3;

        if (b.transaction2 < lowest)
            lowest = b.transaction2;

        if (b.transaction3 < lowest)
            lowest = b.transaction3;

        float currentBalance = b.openingBalance + total;

        cout << "\n===== ACCOUNT AUDIT REPORT =====";
        cout << "\nAccount Number     : " << b.accountNo;
        cout << "\nAccount Holder     : " << b.holderName;
        cout << "\nTotal Transactions : Rs. " << total;
        cout << "\nAverage Transaction: Rs. " << average;
        cout << "\nHighest Transaction: Rs. " << highest;
        cout << "\nLowest Transaction : Rs. " << lowest;
        cout << "\nCurrent Balance    : Rs. " << currentBalance;

        if (currentBalance >= 0)
            cout << "\nAudit Status       : PASS";
        else
            cout << "\nAudit Status       : WARNING - Negative Balance";

        cout << "\n================================\n";
    }
};


// Validate opening balance
bool validBalance(float balance)
{
    return balance >= 0;
}


int main()
{
    BankAccount *accounts[50];

    int n, accountNo, created = 0;
    string holderName;
    float openingBalance, t1, t2, t3;

    AccountAudit auditor;

    cout << "====================================";
    cout << "\n BANK ACCOUNT MANAGEMENT SYSTEM";
    cout << "\n====================================";

    cout << "\nEnter number of accounts (1-50): ";
    cin >> n;

    if (n < 1 || n > 50)
    {
        cout << "Invalid number of accounts!";
        return 0;
    }

    // Enter account records
    while (created < n)
    {
        cout << "\n\nEnter details for Account "
             << created + 1 << endl;

        cout << "Enter Account Number: ";
        cin >> accountNo;

        cout << "Enter Account Holder Name (one word): ";
        cin >> holderName;

        cout << "Enter Opening Balance: Rs. ";
        cin >> openingBalance;

        if (!validBalance(openingBalance))
        {
            cout << "Invalid opening balance! "
                 << "Balance cannot be negative.\n";
            continue;
        }

        cout << "Enter Transaction 1 "
             << "(use negative value for withdrawal): Rs. ";
        cin >> t1;

        cout << "Enter Transaction 2 "
             << "(use negative value for withdrawal): Rs. ";
        cin >> t2;

        cout << "Enter Transaction 3 "
             << "(use negative value for withdrawal): Rs. ";
        cin >> t3;

        accounts[created] = new BankAccount(
            accountNo, holderName, openingBalance, t1, t2, t3
        );

        cout << "\n----- ACCOUNT DETAILS -----";
        accounts[created]->displayDetails();

        auditor.auditAccount(*accounts[created]);

        created++;
    }

    // Display account count
    BankAccount::displayAccountCount();

    // Menu-driven operations
    int choice;

    do
    {
        cout << "\n========== MAIN MENU ==========";
        cout << "\n1. Display All Account Records";
        cout << "\n2. Audit Account by Account Number";
        cout << "\n3. Display Account Count";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                for (int i = 0; i < created; i++)
                {
                    cout << "\nAccount " << i + 1;
                    accounts[i]->displayDetails();
                }
                break;

            case 2:
            {
                int searchNo;
                bool found = false;

                cout << "Enter Account Number to audit: ";
                cin >> searchNo;

                for (int i = 0; i < created; i++)
                {
                    if (accounts[i]->getAccountNo() == searchNo)
                    {
                        auditor.auditAccount(*accounts[i]);
                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << "Account not found!\n";

                break;
            }

            case 3:
                BankAccount::displayAccountCount();
                break;

            case 4:
                cout << "Exiting Bank Account Management System...";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 4);

    // Release dynamically allocated memory
    for (int i = 0; i < created; i++)
    {
        delete accounts[i];
    }

    return 0;
}

