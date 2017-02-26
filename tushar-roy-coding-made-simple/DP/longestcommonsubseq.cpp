//
// Created by Ranga on 2/20/17.
//

#include <vector>
#include <iostream>
#include <algorithm>

unsigned LongestCommonSubsequence( const std::string &str1, const std::string &str2 ) {

    const auto &s1( " " + str1 ), &s2( " " + str2 );
    std::vector< std::vector< unsigned > > table( s2.size(), std::vector< unsigned >( s1.size(), 0 ) );

    std::for_each( table.begin(), table.end(), []( auto &row ){ row[ 0 ] = 0;} );
    std::for_each( table[ 0 ].begin(), table[ 0 ].end(), []( auto &value ){ value = 0;} );

    for( size_t i = 1; i < s2.size(); ++i ) {
        for( size_t j = 1; j < s1.size(); ++j ) {
            table[ i ][ j ] = std::max( std::max( table[ i ][ j-1 ], table[ i-1 ][ j-1 ] ), table[ i-1 ][ j ] ) + ( s2[ i ] == s1[ j ] ? 1 : 0 );
        }
    }

    return table[ str2.size() ][ str1.size() ];
}

int main(int argc, char *argv[] ) {

    std::string str1{ "abcdaf" }, str2{ "acbcf" };
    std::cout << LongestCommonSubsequence( str1, str2 ) << std::endl;
    return 0;
}