//
// Created by Ranga on 6/25/16.
//

#include <iostream>

class A {
public:
    int a;
    struct B {
        int m;
        int n;
    } b;
    int c;
};

int main() {
    A x{ 7, { 8, 9 }, 10 };

    std::cout << x.a << ", " << x.b.m << ", " << x.b.n << ", " << x.c << std::endl;
    return 0;
}