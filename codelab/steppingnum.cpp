//
// Created by Ranga on 3/12/17.
//

#include <sstream>
#include <iostream>

bool IsSteppingNum( int x ) {

    int prev = x % 10;
    x /= 10;
    bool isSteppingNum = true;
    while( x > 0 ) {
        auto next = x % 10;
        if( abs( prev - next ) != 1 ) {
            isSteppingNum = false;
            break;
        }
        prev = next;
        x = x / 10;
    }

    return isSteppingNum;
}

int main( int argc, char *argv[] ) {

    const int A = 0, B = 20;
    unsigned numSteppingNum = 0;
    for( auto i = A; i <= B; ++i ) {
        if( IsSteppingNum( i ) ) {
            std::cout << i << std::endl;
            //++numSteppingNum;
        }
    }
    return 0;
}