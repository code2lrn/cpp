//
// Created by Ranga on 2/19/17.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

int main(int argc, char *argv[] ) {

    std::vector< int > A{ 0, 1, 0, 1 };
    auto numflips = 0, nextSwitchState = 0;
    for( size_t i = 0; i < A.size(); ++i ) {
        if( A[ i ] == nextSwitchState ) {
            //std::for_each( A.begin() + i + 1, A.end(), []( auto &b ) { b = b == 0? 1 : 0; } );
            nextSwitchState = nextSwitchState == 0 ? 1 : 0;
            ++numflips;
        }
    }
    std::cout << numflips << std::endl;
    return 0;
}