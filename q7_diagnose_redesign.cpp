#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <string>

// ============================================================================
// 1. ORIGINAL DESIGN (Q4): Fixed Array with Element Shifting O(k)
// ============================================================================
template <size_t K>
class OriginalShiftingAccount {
private:
    long accountNumber;
    double balance;
    double transactions[K];
    size_t count;
    unsigned long long shiftOperations;

public:
    OriginalShiftingAccount(long acc, double initBal)
        : accountNumber(acc), balance(initBal), count(0), shiftOperations(0) {}

    void deposit(double amount) {
        balance += amount;
        recordTransaction(+amount);
    }

    void withdraw(double amount) {
        balance -= amount;
        recordTransaction(-amount);
    }

    void recordTransaction(double amount) {
        if (count < K) {
            transactions[count++] = amount;
        } else {
            // Limitation: Left-shift all k-1 elements
            for (size_t i = 0; i < K - 1; ++i) {
                transactions[i] = transactions[i + 1];
                shiftOperations++;
            }
            transactions[K - 1] = amount;
        }
    }

    unsigned long long getShiftCount() const { return shiftOperations; }
    double getBalance() const { return balance; }
    double getChecksum() const {
        double s = balance;
        for (size_t i = 0; i < count; ++i) s += transactions[i];
        return s;
    }
};

// ============================================================================
// 2. REDESIGNED SOLUTION: Circular Ring Buffer O(1)
// ============================================================================
template <size_t K>
class RedesignedRingBufferAccount {
private:
    long accountNumber;
    double balance;
    double buffer[K];
    size_t head;  // Points to next insertion slot
    size_t count; // Active elements <= K
    unsigned long long shiftOperations;

public:
    RedesignedRingBufferAccount(long acc, double initBal)
        : accountNumber(acc), balance(initBal), head(0), count(0), shiftOperations(0) {}

    void deposit(double amount) {
        balance += amount;
        recordTransaction(+amount);
    }

    void withdraw(double amount) {
        balance -= amount;
        recordTransaction(-amount);
    }

    // O(1) Constant Time Insertion: Zero memory moves!
    void recordTransaction(double amount) {
        buffer[head] = amount;
        head = (head + 1) % K; // Modular wrap-around
        if (count < K) {
            count++;
        }
    }

    unsigned long long getShiftCount() const { return shiftOperations; }
    double getBalance() const { return balance; }
    double getChecksum() const {
        double s = balance;
        for (size_t i = 0; i < count; ++i) s += buffer[i];
        return s;
    }
};

// ============================================================================
// BENCHMARK HARNESS: Comparing Original vs Redesign across N=500,000 txns
// ============================================================================
template <size_t K>
void runBenchmark(const std::string& capacityLabel, int numTransactions) {
    std::cout << "------------------------------------------------------------\n";
    std::cout << "BENCHMARK: Capacity K = " << K << " (" << capacityLabel << "), Txns = " << numTransactions << '\n';
    std::cout << "------------------------------------------------------------\n";

    // 1. Benchmark Original Shifting
    OriginalShiftingAccount<K> originalAcc(1001, 100000.0);
    auto startOrig = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numTransactions; ++i) {
        if (i % 2 == 0) originalAcc.deposit(100.0 + (i % 50));
        else originalAcc.withdraw(50.0 + (i % 30));
    }
    auto endOrig = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> origTime = endOrig - startOrig;

    // 2. Benchmark Redesigned Ring Buffer
    RedesignedRingBufferAccount<K> redesignedAcc(1001, 100000.0);
    auto startRedesign = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numTransactions; ++i) {
        if (i % 2 == 0) redesignedAcc.deposit(100.0 + (i % 50));
        else redesignedAcc.withdraw(50.0 + (i % 30));
    }
    auto endRedesign = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> redesignTime = endRedesign - startRedesign;

    double speedup = origTime.count() / (redesignTime.count() > 0.001 ? redesignTime.count() : 0.001);

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "ORIGINAL (Shifting Array):\n";
    std::cout << "  Time Elapsed      : " << origTime.count() << " ms\n";
    std::cout << "  Shift Operations  : " << originalAcc.getShiftCount() << " element moves\n";
    std::cout << "  Checksum Check    : " << originalAcc.getChecksum() << '\n';
    std::cout << "REDESIGNED (Circular Ring Buffer):\n";
    std::cout << "  Time Elapsed      : " << redesignTime.count() << " ms\n";
    std::cout << "  Shift Operations  : " << redesignedAcc.getShiftCount() << " element moves (100% eliminated!)\n";
    std::cout << "  Checksum Check    : " << redesignedAcc.getChecksum() << '\n';
    std::cout << "SPEEDUP FACTOR      : " << speedup << "x FASTER!\n\n";
}

int main() {
    std::cout << "============================================================\n";
    std::cout << "Q7 DAY-4 DESIGN CHALLENGE: DIAGNOSE, REDESIGN & VALIDATE\n";
    std::cout << "Target: Q4 SavingsAccount Transaction History Scalability\n";
    std::cout << "============================================================\n\n";

    const int NUM_TXNS = 500000; // 500,000 Transactions

    runBenchmark<10>("Original Requirement (Last 10 Txns)", NUM_TXNS);
    runBenchmark<50>("Changed Requirement (Last 50 Txns)", NUM_TXNS);
    runBenchmark<200>("Enterprise Scale (Last 200 Txns)", NUM_TXNS);
    runBenchmark<500>("Audit Scale (Last 500 Txns)", NUM_TXNS);

    return 0;
}
