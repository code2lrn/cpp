#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>
#include <numeric>
#include "highrestimer.h"

using namespace std;
using namespace std::chrono;

template<class It, class Pred>
auto callback_ftor(It b, It e, Pred pred) {
    return count_if(b, e, pred);
}

template<class It, class R, class A>
auto callback_fctn(It b, It e, R(*pred)(A)) {
    return count_if(b, e, pred);
}

bool is_even(int n) {
    return n % 2 == 0;
}

int main() {
    enum {
        N = 10'000'000
    };
    vector<int> v(N);
    iota(begin(v), end(v), 1);
    for( auto s = 0; s < 5; ++s ) {
        auto r0 = HighResTimer([&]() {
            return callback_fctn(begin(v), end(v), is_even);
        });
        cout << "Callback through a function\n\t"
             << "counted " << r0.first << " in "
             << duration_cast<microseconds>(r0.second).count() << " us." << endl;
    }
    for( auto s = 0; s < 5; ++s ) {
        auto r1 = HighResTimer([&]() {
            return callback_ftor(begin(v), end(v), [](int n) {
                return n % 2 == 0;
            });
        });
        cout << "Callback through a functor\n\t"
             << "counted " << r1.first << " in "
             << duration_cast<microseconds>(r1.second).count() << " us." << endl;
    }
}

