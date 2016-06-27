//
// Created by Ranga on 6/23/16.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <bitset>

int main( int argc, char *argv[] ) {
    size_t numberOfElements;
    std::cin >> numberOfElements;
    if( numberOfElements < 1 ) {
        return 1;
    }

    unsigned num;
    std::vector< unsigned > numbers;
    while( numberOfElements-- && std::cin >> num ) {
        numbers.push_back( num );
    }

    std::for_each( numbers.begin(), numbers.end(), [] ( auto num ) { std::cout << std::bitset< 32 >( num ) << std::endl; } );

    unsigned singleNumber = numbers[ 0 ];
    std::for_each( numbers.begin() + 1, numbers.end(), [ &singleNumber ] ( auto num ) { singleNumber ^= num; std::cout << "Result: " << std::bitset< 32 >( singleNumber ) << std::endl; } );
    std::cout << "The number occuring only once is " << singleNumber << std::endl;
    return 0;
}
