//
// Created by shiva on 2/22/17.
//


#include <string>
#include <algorithm>
#include <iostream>

int main(int argc, char *argv[] ) {

    std::string A{ "A   " };
    int value = 0, index = 0;
    std::for_each( A.rbegin(), A.rend(), [ &value, &index ] ( const auto &ch ) {
        value += std::pow( 26, index ) * ( ch - 'A' + 1 );
        ++index;
    } );
    std::cout << value << std::endl;

    return 0;
}