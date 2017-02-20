//
// Created by Ranga on 2/19/17.
//

#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <cstring>

int main(int argc, char *argv[] ) {

    /*
    std::vector< int > A{ 1, 2, 2, 3, 1 };
    auto remNumber = A[ 0 ];
    std::for_each( A.begin() + 1, A.end(), [ &remNumber ] ( auto &i ) { remNumber ^= i; } );
    std::cout << remNumber << std::endl;
    //std::copy( A.begin(), A.end(), std::ostream_iterator< int >( std::cout, " " ) );
    */

    std::string A{ "aabcc" }, B{ "dbbca" }, C{ "aadbbcbcac" };

    auto a = A.begin(), b = B.begin(), c = C.begin();
    bool noGood = false;
    while( a != A.end() && b != B.end() && c != C.end() ) {
        if( *a == *c ) {
            ++a;
            ++c;
        }
        else if( *b == *c ) {
            ++b;
            ++c;
        }
        else {
            noGood = true;
            break;
        }
    }

    while( !noGood && a != A.end() && c != C.end() ) {
        if( *a == *c ) {
            ++a;
            ++c;
        }
        else {
            noGood = true;
            break;
        }
    }

    while( !noGood && b != B.end() && c != C.end() ) {
        if( *b == *c ) {
            ++b;
            ++c;
        }
        else {
            noGood = true;
            break;
        }
    }

    std::cout << std::boolalpha << ( !noGood && a == A.end() && b == B.end() && c == C.end() ) << std::endl;

    return 0;
}