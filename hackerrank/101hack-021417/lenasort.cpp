//
// Created by Ranga on 2/14/17.
//

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using SortIndices = std::vector< std::pair< unsigned, unsigned > >;

void DetermineSortIndices( unsigned arrayStart, unsigned arrayEnd, uint64_t &numComparisions, SortIndices &sortIndices ) {
    if( arrayStart >= arrayEnd || numComparisions <= 0 )
        return;

    numComparisions -= arrayEnd - arrayStart;
    sortIndices.push_back( std::make_pair( arrayStart, arrayEnd ) );
    unsigned mid = ( arrayStart + arrayEnd ) / 2;
    if( numComparisions > 0 );
        DetermineSortIndices( arrayStart, mid, numComparisions, sortIndices );
    if( numComparisions > 0 )
        DetermineSortIndices( mid + 1, arrayEnd, numComparisions, sortIndices );
}

int main(int argc, char *argv[] ) {

    unsigned numQueries;
    std::cin >> numQueries;
    while( numQueries-- ) {
        unsigned arraySize;
        uint64_t numComparions;
        std::cin >> arraySize >> numComparions;

        std::vector< unsigned > array( arraySize );
        unsigned value = 0;
        std::generate( array.begin(), array.end(), [ &value ](){ return ++value; } );

        SortIndices sortIndices;

        DetermineSortIndices( 0, arraySize - 1, numComparions, sortIndices );

        //std::cout << "State of array:\n";
        //std::copy( array.begin(), array.end(), std::ostream_iterator< unsigned >( std::cout, " " ) );
        //std::cout << std::endl;
        if( numComparions == 0 ) {
            std::for_each( sortIndices.begin(), sortIndices.end(),
                           [ &array ] ( auto &p ) {
                               //std::cout << "for (" << p.first << ", " << p.second << ")\n";
                               std::swap( array[ p.first ], array[ p.first + 1 ] );
                               //std::copy( array.begin(), array.end(), std::ostream_iterator< unsigned >( std::cout, " " ) );
                               //std::cout << std::endl;
                           } );

            std::copy( array.begin(), array.end(), std::ostream_iterator< unsigned >( std::cout, " " ) );
            std::cout << std::endl;
        }
        else {
            std::cout << "-1\n";
        }
    }

    return 0;
}