//
// Created by Ranga on 2/14/17.
//

#include <cstdint>
#include <array>
#include <vector>
#include <iostream>
#include <iterator>

std::array< uint64_t, 100000 + 1 > lowerBound;
std::array< uint64_t, 100000 + 1 > upperBound;

void Solve( unsigned left, unsigned right, uint64_t numComparisions, unsigned &nextNum, std::vector< unsigned > &array ) {
    unsigned n = right - left;
    if( n == 0 )
        return;
    if( n == 1 ) {
        array[ left ] = nextNum++;
        return;
    }

    numComparisions -= n - 1;
    for( unsigned i = 0; i < n; ++i ) {
        if( lowerBound[ i ] + lowerBound[ n - i - 1 ] <= numComparisions ) {
            uint64_t remainingComparisions = std::min( upperBound[ i ], numComparisions - lowerBound[ n - i - 1 ] );
            Solve( left + 1, left + 1 + i, remainingComparisions, nextNum, array );
            array[ left ] = nextNum++;
            Solve( left + 1 + i, right, numComparisions - remainingComparisions, nextNum, array );
            return;
        }
    }
}

int main( int argc, char *argv[] ) {

    for( int i = 2; i <= 100000; ++i ) {
        lowerBound[ i ] = ( i - 1 ) + lowerBound[ ( i - 1 ) / 2 ] + lowerBound[ i / 2 ];
        upperBound[ i ] = ( i - 1 ) + upperBound[ i - 1 ];
    }

    unsigned numQueries;
    std::cin >> numQueries;
    while( numQueries-- ) {
        unsigned arraySize;
        uint64_t numComparions;
        std::cin >> arraySize >> numComparions;
        std::vector< unsigned > array( arraySize );
        if( numComparions < lowerBound[ arraySize ] || numComparions > upperBound[ arraySize ] )
            std::cout << "-1\n";
        else {
            unsigned nextNum = 1;
            Solve( 0, arraySize, numComparions, nextNum, array );
            std::copy( array.begin(), array.end(), std::ostream_iterator< unsigned >( std::cout, " " ) );
            std::cout << std::endl;
        }
    }

    return 0;
}