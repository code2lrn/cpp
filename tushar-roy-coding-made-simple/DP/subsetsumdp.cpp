//
// Created by Ranga on 2/20/17.
//

#include <vector>
#include <iostream>
#include <algorithm>

bool SubsetWithSumExists( const std::vector< int > &seq, int sum ) {

    std::vector< std::vector< bool > > table( seq.size(), std::vector< bool >( sum + 1, false ) );
    std::for_each( table.begin(), table.end(), []( auto &row ){ row[ 0 ] = true; } );

    for( int i = 0; i < seq.size(); ++i ) {
        for( int j = 1; j <= sum; ++j ) {
            if( i == 0 ) {
                table[ i ][ j ] = ( seq[ i ] == j );
            }
            else {
                if( table[ i-1 ][ j ] ) {
                    table[ i ][ j ] = true;
                }
                else if( seq[ i ] > j ) {
                    continue;
                }
                else {
                    table[ i ][ j ] = ( seq[ i ] == j ) || ( table[ i-1 ][ j - seq[ i ] ] );
                }
            }
        }
    }

    return table[ seq.size() - 1 ][ sum ];
}

int main(int argc, char *argv[] ) {

    std::vector< int > seq{ 2, 3, 7, 8, 10 };
    const int sum = 14;

    std::cout << std::boolalpha << SubsetWithSumExists( seq, sum ) << std::endl;

    return 0;
}