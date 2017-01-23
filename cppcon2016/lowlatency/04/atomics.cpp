//
// Created by Ranga on 9/18/16.
//

#include <thread>
#include <atomic>
#include "highrestimer.h"
#include <iostream>

using namespace std;

int DoNonAtomics() {
    const int N = 100'000'000;
    int v1 = 0;
    thread th1{ [&v1](){ for( auto i = 0; i < N; ++i ) v1++; } };
    th1.join();
    return v1;
}

int DoAtomics() {
    const int N = 100'000'000;
    std::atomic<int> v2{ 0 };
    thread th2{ [&v2](){ for( auto i = 0; i < N; ++i ) v2++; } };
    th2.join();
    return v2;
}

int main() {
    auto t1 = HighResTimer( DoNonAtomics );
    cout << "Non Atomics took " << PrintMicroSecs( t1.second ) << " us\n";
    auto t2 = HighResTimer( DoAtomics );
    cout << "Atomics took " << PrintMicroSecs( t2.second ) << " us\n";
    return 0;
}