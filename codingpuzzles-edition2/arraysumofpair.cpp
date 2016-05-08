//
// Created by Ranga on 5/8/16.
//

#include <iostream>
#include <vector>
#include <unistd.h>

using Pairs = std::vector< std::pair< int, int > >;

void GetCombinationsForSum( const std::vector< int > array, Pairs &pairs, const int sum ) {
    for( auto i = 0; i < array.size() - 1; ++i ) {
        for( auto j = i + 1; j < array.size(); ++j ) {
            if( array[ i ] + array[ j ] == sum ) {
                pairs.push_back( std::make_pair( array[ i ], array[ j ] ) );
            }
        }
    }
}

int main( int argc, char *argv[] ) {
    std::cout << "Enter number of elements: ";
    int num;
    std::cin >> num;
    std::cout << "Enter the elements: ";
    int val;
    std::vector< int > array;
    while( num-- && std::cin >> val ) {
        array.push_back( val );
    }
    int sum;
    std::cout << "Enter the sum: ";
    std::cin >> sum;

    Pairs pairs;
    GetCombinationsForSum( array, pairs, sum );
    std::cout << "The pairs adding up to " << sum << " are:\n";
    for( auto p : pairs ) {
        std::cout << p.first << " - " << p.second << std::endl;
    }

    sleep(1);
    return 0;
}