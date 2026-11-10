#include <iostream>
#include <iomanip>
#include <string>

struct Parcel {
    double weightKg;
    bool express;
    bool insured;
};

// Rates: Base: Rs. 50/kg, Express: +Rs. 150, Insured: +Rs. 100

// 1. Weight in kilograms (double) with default arguments for optional flags
double charge(double weightKg, bool express = false, bool insured = false) {
    std::cout << "  -> [Selected: charge(double weightKg, bool express, bool insured)]\n";
    double total = weightKg * 50.0;
    if (express) total += 150.0;
    if (insured) total += 100.0;
    return total;
}

// 2. Weight in grams (int) handled by overloading
double charge(int weightGrams, bool express = false, bool insured = false) {
    std::cout << "  -> [Selected: charge(int weightGrams, bool express, bool insured)]\n";
    double weightKg = static_cast<double>(weightGrams) / 1000.0;
    double total = weightKg * 50.0;
    if (express) total += 150.0;
    if (insured) total += 100.0;
    return total;
}

// 3. Parcel object handled by overloading
double charge(const Parcel& p) {
    std::cout << "  -> [Selected: charge(const Parcel& p)]\n";
    double total = p.weightKg * 50.0;
    if (p.express) total += 150.0;
    if (p.insured) total += 100.0;
    return total;
}

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "========================================================\n";
    std::cout << "Task 03: Courier Charge Calculator (Unambiguous Redesign)\n";
    std::cout << "========================================================\n\n";

    std::cout << "Call 1: charge(2)  [literal 2 is int]\n";
    double c1 = charge(2);
    std::cout << "Result: Rs. " << c1 << "\n\n";

    std::cout << "Call 2: charge(2.0f)  [literal 2.0f is float]\n";
    double c2 = charge(2.0f);
    std::cout << "Result: Rs. " << c2 << "\n\n";

    std::cout << "Call 3: charge(3.5)  [literal 3.5 is double]\n";
    double c3 = charge(3.5);
    std::cout << "Result: Rs. " << c3 << "\n\n";

    std::cout << "Call 4: charge(3.5, true)  [double, bool]\n";
    double c4 = charge(3.5, true);
    std::cout << "Result: Rs. " << c4 << "\n\n";

    std::cout << "Call 5: charge(3.5, true, true)  [double, bool, bool]\n";
    double c5 = charge(3.5, true, true);
    std::cout << "Result: Rs. " << c5 << "\n\n";

    std::cout << "Call 6: charge(Parcel{4.2, true, false})  [Parcel struct]\n";
    double c6 = charge(Parcel{4.2, true, false});
    std::cout << "Result: Rs. " << c6 << "\n\n";

    return 0;
}
