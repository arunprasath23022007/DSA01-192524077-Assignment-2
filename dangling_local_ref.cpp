#include <iostream>

// DANGEROUS: Returning reference to a local stack variable
int& returnLocalReference() {
    int localMark = 95;
    return localMark; // Triggers -Wreturn-local-addr warning
}

void overwriteStack() {
    // Call another function that creates a new stack frame
    volatile int garbage[16];
    for (int i = 0; i < 16; ++i) garbage[i] = 0xDEADBEEF;
}

int main() {
    std::cout << "Calling returnLocalReference()...\n";
    int& badRef = returnLocalReference();
    std::cout << "Immediately reading badRef: " << badRef << '\n';
    
    overwriteStack();
    std::cout << "After stack overwrite, badRef: " << badRef << " (CORRUPTED / UNDEFINED BEHAVIOUR)\n";
    return 0;
}
