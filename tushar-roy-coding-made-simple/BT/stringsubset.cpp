//
// Created by Ranga on 2/22/17.
//

#include <string>
#include <bitset>
#include <stack>
#include <iostream>
#include <sstream>
#include <cmath>

void IncrementByOne( std::bitset< 64 > &charToBeSet ) {
    if( charToBeSet[ 0 ] == 0 ) {
        charToBeSet.set( 0 );
        return;
    }

    charToBeSet.set( 0, 0 );
    for( int i = 1; i < charToBeSet.size(); ++i ) {
        if( charToBeSet[ i ] == 0 ) {
            charToBeSet.set( i );
            return;
        }
        else {
            charToBeSet.set( i, 0 );
        }
    }
}

int main( int argc, char *argv[] ) {

    std::string str{ "abcdefg" };

    std::bitset< 64 > charToBeSet( 0 );
    unsigned maxValue = std::pow( 2, str.size() );
    while( !charToBeSet.all() && charToBeSet.to_ulong() <= maxValue ) {
        std::stringstream ss;
        for( int i = 0; i < str.size(); ++i ) {
            if( charToBeSet[ i ] ) {
                ss << str[ i ];
            }
        }

        std::cout << ss.str() << std::endl;

        IncrementByOne( charToBeSet );
    }

    return 0;
}
