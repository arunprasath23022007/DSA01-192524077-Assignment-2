#include <iostream>
#include <chrono>
#include <cmath>

#ifndef INLINE_MODE
#define INLINE_MODE 0
#endif

class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};

#if INLINE_MODE == 1
inline int minutesBetween(const Time& a, const Time& b) {
    return std::abs((a.h * 60 + a.m) - (b.h * 60 + b.m));
}
inline bool earlier(const Time& a, const Time& b) {
    return (a.h < b.h) || (a.h == b.h && a.m < b.m);
}
#else
// __attribute__((noinline)) ensures the compiler does not inline even at -O2
__attribute__((noinline)) int minutesBetween(const Time& a, const Time& b) {
    return std::abs((a.h * 60 + a.m) - (b.h * 60 + b.m));
}
__attribute__((noinline)) bool earlier(const Time& a, const Time& b) {
    return (a.h < b.h) || (a.h == b.h && a.m < b.m);
}
#endif

int main(int argc, char* argv[]) {
    const long long ITERATIONS = 10000000LL; // 10 Million Calls
    Time t1(9, 45);
    Time t2(13, 10);

    volatile long long dummySum = 0; // Prevent compiler from eliminating loop

    auto start = std::chrono::high_resolution_clock::now();
    for (long long i = 0; i < ITERATIONS; ++i) {
        dummySum += minutesBetween(t1, t2);
        dummySum += earlier(t1, t2) ? 1 : 0;
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Mode: " << (INLINE_MODE ? "WITH INLINE" : "WITHOUT INLINE")
              << " | Time for 10M calls: " << elapsed.count() << " ms"
              << " (Checksum: " << dummySum << ")\n";
    return 0;
}
