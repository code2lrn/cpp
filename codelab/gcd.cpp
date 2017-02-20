//
// Created by Ranga on 2/19/17.
//

#include <iostream>

int main(int argc, char *argv[] ) {

    unsigned a = 48, b = 18;
    while( b != 0 ) {
        auto t = a % b;
        a = b;
        b = t;
    }

    std::cout << a << std::endl;

    return 0;
}