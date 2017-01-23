//
// Created by Ranga on 1/11/17.
//

#include <iostream>
#include <cstring>
#include <cmath>
#include <iterator>
#include <algorithm>
#include <sstream>

int main(int argc, char *argv[] ) {

    unsigned strSize;
    std::cin >> strSize;
    char *str = new char[ strSize + 1 ];
    std::cin >> str;
    str[ strSize ] = 0;

    int pss = (int)pow( 2, strlen( str ) );
    char buf[ ( int )pow( 10, 5 ) ];
    unsigned numAnswersFound = 0;
    for( int i = pss -1; i > 0; --i ) {
        char *tmp = buf;
        bool firstMatch = true;
        bool foundNonDivisibleNumber = false;
        for( int j = strlen( str ) - 1; j >= 0; --j ) {
            if( i & ( 1 << j ) ) {
                char ch = str[ j ];
                if( firstMatch ) {
                    if( !( ch == '0' || ch == '2' || ch == '4' || ch == '6' || ch == '8' ) ) {
                        foundNonDivisibleNumber = true;
                        break;
                    }
                    firstMatch = false;
                }
               *tmp++ = str[ j ];
                if( tmp - buf == 3 ) {
                    break;
                }
            }
        }
        if( !foundNonDivisibleNumber ) {
            std::stringstream strOut;
            std::reverse_copy( buf, tmp, std::ostream_iterator< char >( strOut, "" ) );
            int i;
            strOut >> i;
            if( i % 8 == 0 ) {
                ++numAnswersFound;
            }
        }
    }
    std::cout << numAnswersFound << std::endl;

    delete [] str;
    return 0;
}
