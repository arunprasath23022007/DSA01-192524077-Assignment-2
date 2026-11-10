#include <iostream>
#include <cmath>

class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};

int minutesBetween(const Time& a, const Time& b)
{
    // TODO 1: Using the private members h and m, return the absolute difference between
    // the two times in minutes
    int t1 = a.h * 60 + a.m;
    int t2 = b.h * 60 + b.m;
    return std::abs(t1 - t2);
}

bool earlier(const Time& a, const Time& b)
{
    // TODO 2: Return true if a is earlier in the day than b
    if (a.h != b.h) return a.h < b.h;
    return a.m < b.m;
}

int main()
{
    std::cout << "--- Standard Run (Expected Output Check) ---\n";
    Time departure(9, 45), arrival(13, 10);
    std::cout << minutesBetween(departure, arrival) << ' '
              << std::boolalpha << earlier(arrival, departure) << '\n';

    std::cout << "\n--- Correctness Check 1: Times on either side of noon ---\n";
    Time tMorning(11, 45), tAfternoon(12, 15);
    std::cout << "t1 = 11:45, t2 = 12:15\n";
    std::cout << "minutesBetween(11:45, 12:15) = " << minutesBetween(tMorning, tAfternoon) << " mins (Hand calc: 15m + 15m = 30m)\n";
    std::cout << "earlier(11:45, 12:15) = " << earlier(tMorning, tAfternoon) << " (Expected: true)\n";
    std::cout << "earlier(12:15, 11:45) = " << earlier(tAfternoon, tMorning) << " (Expected: false)\n";

    std::cout << "\n--- Correctness Check 2: Same time twice ---\n";
    Time tSameA(14, 30), tSameB(14, 30);
    std::cout << "t1 = 14:30, t2 = 14:30\n";
    std::cout << "minutesBetween(14:30, 14:30) = " << minutesBetween(tSameA, tSameB) << " mins (Hand calc: 0m)\n";
    std::cout << "earlier(14:30, 14:30) = " << earlier(tSameA, tSameB) << " (Expected: false, neither is earlier)\n";

    return 0;
}
