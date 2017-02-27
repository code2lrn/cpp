//
// Created by Ranga on 2/26/17.
//

#include <string>
#include <vector>
#include <iterator>
#include <iostream>

std::vector<int> GenerateSuffixArray( const std::string &str ) {
    std::vector<int> suffixLength( str.size(), 0 );
    auto j = 0, i = 1;
    while( i < suffixLength.size() ) {
        if( str[ i ] != str[ j ] ) {
            while( j != 0 && str[ i ] != str[ j ] ) {
                j = suffixLength[ j - 1 ];
            }
            suffixLength[ i ] = ( str[ i ] == str[ j ] ) ? j + 1 : suffixLength[ j ];
            ++i;
        }
        else if( str[ i ] == str[ j ] ) {
            suffixLength[ i ] = j + 1;
            ++j;
            ++i;
        }
    }
    return std::move( suffixLength );
}

int main( int argc, char *argv[] ) {

    //std::string str{ "acacabacacabacacac" };
    std::string str{ "abcaby" };
    auto suffixLength( GenerateSuffixArray( str ) );
    std::copy( suffixLength.begin(), suffixLength.end(), std::ostream_iterator< int >( std::cout, " " ) );
    return 0;
}