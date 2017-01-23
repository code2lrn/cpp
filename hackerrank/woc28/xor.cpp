//
// Created by Ranga on 1/10/17.
//

#include <limits>
#include <iostream>
#include <bitset>

int main( int argc, char *argv[] ) {


    unsigned q;
    std::cin >> q;
    while( q-- ) {
        uint64_t x;
        std::cin >> x;

        uint64_t msbbit = ((uint64_t)1) << 63;
        while( msbbit && ( x & msbbit ) == 0 ) {
            msbbit = msbbit >> 1;
        }

        unsigned efficientAnswer = 0;
        while( msbbit ) {
            if( !( msbbit & x ) ) {
                efficientAnswer = efficientAnswer | msbbit;
            }
            msbbit >>= 1;
        }
        std::cout << efficientAnswer << std::endl;
    }

    return 0;
}
