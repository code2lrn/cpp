//
// Created by Ranga on 7/10/16.
//

#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>

std::string compress( std::string input ) {
    if( input.length() < 2 ) {
        return input;
    }

    auto prevChar = input[ 0 ];
    auto charFrequency = 1;
    std::stringstream ss;
    std::for_each( input.begin() + 1, input.end(), [ &prevChar, &charFrequency, &ss ] ( const auto ch ) {
        if( ch == prevChar ) {
            ++charFrequency;
        }
        else {
            ss << prevChar;
            if( charFrequency > 1 ) {
                ss << charFrequency;
            }
            prevChar = ch;
            charFrequency = 1;
        }
    } );

    ss << prevChar;
    if( charFrequency > 1 ) {
        ss << charFrequency;
    }

    return( ss.str() );
}

int main( int argc, char *argv[] ) {

    std::string input;
    while( std::cin >> input ) {
        std::cout << compress( input ) << std::endl;
    }
    return 0;
}