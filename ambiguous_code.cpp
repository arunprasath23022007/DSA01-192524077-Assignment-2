// Developer's original buggy code demonstrating ambiguity
#include <iostream>

double charge(double weight) {
    return weight * 50.0;
}

double charge(double weight, bool express) {
    return weight * 50.0 + (express ? 150.0 : 0.0);
}

double charge(double weight, bool express = false, bool insured = false) {
    return weight * 50.0 + (express ? 150.0 : 0.0) + (insured ? 100.0 : 0.0);
}

int main() {
    // Both of these calls are ambiguous
    std::cout << charge(2.5) << '\n';
    std::cout << charge(2.5, true) << '\n';
    return 0;
}
