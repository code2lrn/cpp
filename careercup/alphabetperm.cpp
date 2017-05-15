//
// Created by Ranga on 5/15/17.
//

#include <algorithm>
#include <bitset>
#include <iostream>

void PrintAlphabetPermutations( const std::string &str ) {
    unsigned numChars = std::count_if( str.begin(), str.end(), []( char ch ) { return isalpha( ch ); } );
    unsigned bits = 0;

    while( bits < std::pow( 2, numChars ) ) {
        auto s{ str };
        for( unsigned i = 0, j = 1; i < s.size(); ++i ) {
            if( isalpha( s[ i ] ) ) {
                s[ i ] = bits & j ? toupper( s[ i ] ) : s[ i ];
                j = j << 1;
            }
        }
        std::cout << bits << ": " << s << std::endl;
        ++bits;
    }
}

int main(int argc, char *argv[] ) {

    std::string str{ "ac|dw" };
    std::for_each( str.begin(), str.end(), []( char &ch ) { ch = (char)tolower( ch ); } );
    PrintAlphabetPermutations( str );
    return 0;
}