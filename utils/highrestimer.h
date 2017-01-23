//
// Created by Ranga  on 9/17/16.
//

#ifndef PROJECT_HIGHRESTIMER_H
#define PROJECT_HIGHRESTIMER_H

#include <chrono>
#include <utility>
using namespace std::chrono;
template <class F, class ... Args>
auto HighResTimer(F f, Args&&... args) {
    auto pre = high_resolution_clock::now();
    auto res = f(std::forward<Args>(args)...);
    auto post = high_resolution_clock::now();
    return std::make_pair(res, post - pre);
}

double PrintMicroSecs( duration< double > timeSpan ) {
    return std::chrono::duration_cast<std::chrono::microseconds>( timeSpan ).count();
}

#endif //PROJECT_HIGHRESTIMER_H
