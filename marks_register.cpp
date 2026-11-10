#include <iostream>
#include <vector>
#include <iomanip>

// 1. Return by Reference: Returns alias to the element inside array
int& findHighestMark(int marks[], int n) {
    int maxIdx = 0;
    for (int i = 1; i < n; ++i) {
        if (marks[i] > marks[maxIdx]) {
            maxIdx = i;
        }
    }
    return marks[maxIdx]; // Returning lvalue reference to existing array element
}

// 2. Return by Const Reference: Read-only access, cannot be on LHS of =
const int& findHighestConst(const int marks[], int n) {
    int maxIdx = 0;
    for (int i = 1; i < n; ++i) {
        if (marks[i] > marks[maxIdx]) {
            maxIdx = i;
        }
    }
    return marks[maxIdx];
}

// 3. Return by Copy (Value): Returns temporary rvalue
int findHighestCopy(const int marks[], int n) {
    int maxVal = marks[0];
    for (int i = 1; i < n; ++i) {
        if (marks[i] > maxVal) {
            maxVal = marks[i];
        }
    }
    return maxVal;
}

// Alternatives: Index and Pointer
int findHighestIndex(const int marks[], int n) {
    int maxIdx = 0;
    for (int i = 1; i < n; ++i) {
        if (marks[i] > marks[maxIdx]) maxIdx = i;
    }
    return maxIdx;
}

int* findHighestPointer(int marks[], int n) {
    if (n <= 0) return nullptr;
    int maxIdx = 0;
    for (int i = 1; i < n; ++i) {
        if (marks[i] > marks[maxIdx]) maxIdx = i;
    }
    return &marks[maxIdx];
}

void printMarks(const int marks[], int n, const std::string& label) {
    std::cout << label << ": [ ";
    for (int i = 0; i < n; ++i) std::cout << marks[i] << " ";
    std::cout << "]\n";
}

int main() {
    std::cout << "====================================================\n";
    std::cout << "Task 02: Return by Reference - Examination Register\n";
    std::cout << "====================================================\n\n";

    const int N = 5;
    int marks[N] = {78, 85, 92, 64, 89};

    printMarks(marks, N, "Initial Marks");

    // Moderation: +2 applied directly to the return by reference!
    std::cout << "\n--- Applying Moderation (+2) directly using L-Value Reference ---\n";
    std::cout << "Calling: findHighestMark(marks, N) += 2;\n";
    findHighestMark(marks, N) += 2;
    printMarks(marks, N, "Marks after moderation (+2 to 92)");

    // Using return by reference on the left of assignment operator '='
    std::cout << "\n--- Direct Assignment to Function Call (L-Value on Left of '=') ---\n";
    std::cout << "Calling: findHighestMark(marks, N) = 100;\n";
    findHighestMark(marks, N) = 100;
    printMarks(marks, N, "Marks after direct assignment (100)");

    // Demonstrating Alternative: Index vs Pointer vs Reference
    std::cout << "\n--- Comparison of Access Paradigms ---\n";
    int idx = findHighestIndex(marks, N);
    std::cout << "Index approach  : Highest mark at index " << idx << " = " << marks[idx] << '\n';

    int* ptr = findHighestPointer(marks, N);
    if (ptr) {
        std::cout << "Pointer approach: Pointer to highest mark = " << *ptr << " at address " << ptr << '\n';
    }

    // Changed Condition: Growing std::vector and Reference Invalidation
    std::cout << "\n--- Changed Condition: Growing std::vector Reference Invalidation ---\n";
    std::vector<int> vecMarks = {88, 91, 79};
    std::cout << "Vector initial size: " << vecMarks.size() << ", capacity: " << vecMarks.capacity() << '\n';
    
    int& refToFirst = vecMarks[1]; // 91
    int savedIdx = 1;
    std::cout << "Obtained reference to vecMarks[1]: " << refToFirst << " at " << &refToFirst << '\n';

    std::cout << "Forcing reallocation by pushing 10 elements...\n";
    const int* oldBuffer = vecMarks.data();
    for (int i = 0; i < 10; ++i) {
        vecMarks.push_back(70 + i);
    }
    const int* newBuffer = vecMarks.data();
    std::cout << "Vector new size: " << vecMarks.size() << ", capacity: " << vecMarks.capacity() << '\n';
    std::cout << "Old buffer address: " << oldBuffer << "\nNew buffer address: " << newBuffer << '\n';
    
    if (oldBuffer != newBuffer) {
        std::cout << ">> BUFFER REALLOCATION CONFIRMED: Memory block moved!\n";
        std::cout << ">> Any raw reference or pointer to old buffer is now DANGLING / INVALID!\n";
        std::cout << ">> However, index approach remains SAFE: vecMarks[" << savedIdx << "] = " << vecMarks[savedIdx] << '\n';
    }

    return 0;
}
