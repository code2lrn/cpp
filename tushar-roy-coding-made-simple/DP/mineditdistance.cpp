//
// Created by Ranga on 2/20/17.
//

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

unsigned MinimumEditDistance(const std::string &s1, const std::string &s2 ) {
    const auto &str1( " " + s1 ), &str2( " " + s2 );
    std::vector< std::vector< unsigned > > table( str2.size(), std::vector< unsigned >( str1.size(), 0 ) );
    unsigned nullStr1Cost = 0;
    std::for_each( table.begin(), table.end(), [ &nullStr1Cost ] ( auto &row ) { row[ 0 ] = nullStr1Cost++; } );
    unsigned  nullStr2Cost = 0;
    std::for_each( table[ 0 ].begin(), table[ 0 ].end(), [ &nullStr2Cost ] ( auto &cost ) { cost = nullStr2Cost++; } );

    for( size_t i = 1; i <= s2.size(); ++i ) {
        for( size_t j = 1; j <= s1.size(); ++j ) {
            if( i == 0 ) {
                table[ i ][ j ] = ( j - ( str2[ i ] == str1[ j ] ? 0 : 1 ) );
            }
            else {
                table[ i ][ j ] = std::min( std::min( table[ i-1 ][ j-1 ], table[ i-1 ][ j ] ), table[ i ][ j-1 ] ) + ( str2[ i ] == str1[ j ] ? 0 : 1 );
            }
        }
    }

    return table[ s2.size() ][ s1.size() ];
}

int main(int argc, char *argv[] ) {

    std::string str1{ "abcdef" }, str2{ "azced" };
    std::cout << MinimumEditDistance( str1, str2 ) << std::endl;

    return 0;
}