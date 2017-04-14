//
// Created by Ranga on 2/28/17.
//

#include <utility>
#include <vector>
#include <tuple>
#include <cmath>
#include <iostream>
#include <iterator>

using Point = std::pair< int, int >;

void PrintSquares( std::vector< Point > &inputPoints ) {

    std::vector< std::vector< float > > distances{ inputPoints.size(), std::vector< float >( inputPoints.size(), 0 ) };
    for( int i = 0; i < inputPoints.size(); ++i ) {
        for( int j = i + 1; j < inputPoints.size(); ++j ) {
            int x1, x2, y1, y2;
            std::tie( x1, y1 ) = inputPoints[ i ];
            std::tie( x2, y2 ) = inputPoints[ j ];
            distances[ i ][ j ] = distances[ j ][ i ] = sqrt( std::pow( x2 - x1, 2 ) + std::pow( y2 - y1, 2) );
        }
    }
    for( auto row : distances ) {
        std::copy( row.begin(), row.end(), std::ostream_iterator< float >( std::cout, " " ) );
        std::cout << std::endl;
    }
}

int main( int argc, char *argv[] ) {

    std::vector< Point > inputPoints{ { 1, 3 }, { 1, 2 }, { 1, 1 }, { 2, 2 }, { 2, 1 }, { 3, 4 }, { 3, 3 }, { 3, 2 }, { 4, 4 }, { 4, 2 }, { 5, 4 }, { 5, 3 }, };
    // 2 Squares - { 1, 1 }, { 1, 1 }, { 2, 1 }, { 2, 1 } &  { 3, 3 }, { 4, 4 }, { 5, 3 }, { 4, 2 }
    PrintSquares( inputPoints );
    return 0;
}