#include <iostream>
#include <iomanip>
#include <string>

class SavingsAccount {
private:
    long accountNumber;
    double balance;
    static const int MAX_TXN = 10;
    double transactions[MAX_TXN]; // Fixed array of 10 transactions
    int count;                    // Number of active transactions stored (<= 10)
    int head;                     // Circular buffer write index

    // Helper: Circular Buffer insertion O(1)
    void recordTransactionCircular(double amount) {
        transactions[head] = amount;
        head = (head + 1) % MAX_TXN;
        if (count < MAX_TXN) {
            count++;
        }
    }

    // Helper: Shifting Array insertion O(k)
    void recordTransactionShift(double amount) {
        if (count < MAX_TXN) {
            transactions[count++] = amount;
        } else {
            // 11th transaction arrives: shift left discarding oldest at index 0
            for (int i = 0; i < MAX_TXN - 1; ++i) {
                transactions[i] = transactions[i + 1];
            }
            transactions[MAX_TXN - 1] = amount;
        }
    }

public:
    // Constructor defined OUTSIDE the class
    SavingsAccount(long accNo, double initBalance);

    // Member function defined INSIDE class (implicit inline)
    bool deposit(double amount) {
        if (amount <= 0.0) {
            std::cout << "Error: Deposit amount must be positive.\n";
            return false;
        }
        balance += amount;
        recordTransactionCircular(+amount); // using O(1) circular design
        return true;
    }

    // Inline getter defined INSIDE class
    double getBalance() const { return balance; }
    long getAccountNumber() const { return accountNumber; }

    // Member functions defined OUTSIDE class using scope resolution operator ::
    bool withdraw(double amount);
    void miniStatement() const;
    void demonstrate11thTransactionShift();
};

// Constructor definition OUTSIDE class
SavingsAccount::SavingsAccount(long accNo, double initBalance)
    : accountNumber(accNo), balance(initBalance), count(0), head(0) {
    for (int i = 0; i < MAX_TXN; ++i) transactions[i] = 0.0;
}

// Member function withdraw defined OUTSIDE class
bool SavingsAccount::withdraw(double amount) {
    if (amount <= 0.0) {
        std::cout << "Error: Withdrawal amount must be positive.\n";
        return false;
    }
    if (amount > balance) {
        std::cout << "Error: Insufficient funds. Balance: Rs. " << balance << '\n';
        return false;
    }
    balance -= amount;
    recordTransactionCircular(-amount);
    return true;
}

// Member function miniStatement defined OUTSIDE class
void SavingsAccount::miniStatement() const {
    std::cout << "========================================\n";
    std::cout << "         ATM MINI-STATEMENT            \n";
    std::cout << "========================================\n";
    std::cout << "Account Number: " << accountNumber << '\n';
    std::cout << "Current Balance: Rs. " << std::fixed << std::setprecision(2) << balance << '\n';
    std::cout << "----------------------------------------\n";
    std::cout << "Last " << count << " Transactions (Chronological):\n";

    if (count == 0) {
        std::cout << "  No transactions recorded.\n";
    } else {
        // In circular buffer, the oldest element is at (head - count + MAX_TXN) % MAX_TXN
        int startIdx = (head - count + MAX_TXN) % MAX_TXN;
        for (int i = 0; i < count; ++i) {
            int idx = (startIdx + i) % MAX_TXN;
            double txn = transactions[idx];
            std::cout << "  " << std::setw(2) << (i + 1) << ". "
                      << (txn >= 0 ? "CR  +Rs. " : "DR  -Rs. ")
                      << std::setw(8) << (txn >= 0 ? txn : -txn) << '\n';
        }
    }
    std::cout << "========================================\n\n";
}

int main() {
    SavingsAccount acc(1002345678L, 50000.0);

    std::cout << "Initial balance: Rs. " << acc.getBalance() << "\n\n";

    std::cout << "Executing 12 transactions to observe behavior past capacity (10)...\n";
    acc.deposit(1000.0);   // Txn 1
    acc.withdraw(500.0);   // Txn 2
    acc.deposit(2500.0);   // Txn 3
    acc.withdraw(1200.0);  // Txn 4
    acc.deposit(800.0);    // Txn 5
    acc.withdraw(300.0);   // Txn 6
    acc.deposit(4000.0);   // Txn 7
    acc.withdraw(1500.0);  // Txn 8
    acc.deposit(600.0);    // Txn 9
    acc.withdraw(700.0);   // Txn 10 (buffer full)
    
    std::cout << "--- Buffer Full (10 Transactions) ---\n";
    acc.miniStatement();

    std::cout << "--- Adding 11th and 12th Transactions (Older transactions evicted) ---\n";
    acc.deposit(9999.0);   // Txn 11: Txn 1 (+1000) evicted
    acc.withdraw(450.0);   // Txn 12: Txn 2 (-500) evicted

    acc.miniStatement();

    return 0;
}
