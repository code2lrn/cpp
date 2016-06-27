//
// Created by Ranga on 6/7/16.
//

#include <iostream>

template < int N >
constexpr int factorial() {
    return N * factorial< N - 1 >();
}

template <>
constexpr int factorial<0>() {
    return 1;
}

int main( int argc, char *argv[] ) {
    std::cout << "Factorial 5 is " << factorial< 5 >() << std::endl;
    return 0;
}
