//
// Created by Ranga on 7/4/16.
//

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>

void UpsertToSortedSequence( std::vector< unsigned > &elements, const unsigned value ) {
    auto position = std::lower_bound( elements.begin(), elements.end(), value );
    if( position == elements.end() ) {
        elements.push_back( value );
    }
    else {
        *position = value;
    }
}

int main( int argc, char *argv[] ) {

    size_t numElements;
    std::cin >> numElements;
    size_t i = 0;
    std::vector< unsigned > elements;
    elements.reserve( numElements );
    while( i++ < numElements ) {
        unsigned element;
        std::cin >> element;
        elements.push_back( element );
    }

    std::vector< unsigned > lis;
    std::for_each( elements.begin(), elements.end(), [&lis] ( auto u ) { UpsertToSortedSequence( lis, u ); } );
    std::cout << lis.size() << std::endl;

    return 0;
}