//
// Created by Ranga on 2/20/17.
//

#include <map>
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

unsigned MinimumChangeFor( unsigned total, const std::vector< unsigned > &denominations ) {
    std::vector< std::vector< unsigned > > table( denominations.size(), std::vector< unsigned >( total + 1 ) );
    std::for_each( table.begin(), table.end(), [] ( auto &row ){ row[ 0 ] = 0; } );
    std::iota( table[ 0 ].begin(), table[ 0 ].end(), 0 ); // Assuming that 1 is always present & at the start to dispense change

    for( size_t i = 1; i < denominations.size(); ++i ) {
        for( size_t j = 1; j <= total; ++j ) {
            auto denomination = denominations[ i ];
            if( denomination > j ) {
                table[ i ][ j ] = table[ i - 1 ][ j ];
            }
            else {
                table[ i ][ j ] = std::min( table[ i - 1 ][ j ], table[ i ][ j - denomination ] + 1 );
            }
        }
    }

    return table[ denominations.size() - 1 ][ total ];
}

int main(int argc, char *argv[] ) {

    unsigned total = 14;
    std::vector< unsigned > denominations{ 1, 2, 3 };

    std::cout << MinimumChangeFor( total, denominations ) << std::endl;

    return 0;
}
