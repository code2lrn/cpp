//
// Created by Ranga on 9/17/16.
//

#include <memory>
#include <iostream>
#include "highrestimer.h"

struct Impl {
    pthread_mutex_t my_mutex;
};
class Mutex {
    struct Impl;
    std::unique_ptr<Impl> p;
public:
    Mutex();
    Mutex(Mutex&&);
    Mutex& operator=(Mutex&&);
    void lock() const;
    void unlock() const;
    ~Mutex();
};

int DoSomething( int i ) {
    for( int j = 0; j < i; ++j ) {
        std::cout << "Iteration " << i << std::endl;
    }
    return 0;
}

int main() {
    auto stat = HighResTimer( DoSomething, 100 );
    std::cout << "Time taken is " << std::chrono::duration_cast<std::chrono::microseconds>( stat.second ).count() << std::endl;
    return 0;
}