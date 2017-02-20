//
// Created by Ranga on 2/19/17.
//

#include <iostream>

int main(int argc, char *argv[] ) {

    unsigned num;
    while( std::cin >> num ) {
        auto numOnes = 0;
        while( num != 0 ) {
            num &= ( num - 1 );
            ++numOnes;
        }
        std::cout << "Num Ones: " << numOnes << std::endl;
    }
    return 0;
}