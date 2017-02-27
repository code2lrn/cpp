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

    std::string haystack{ "abxabcabcxaby" }, needle{ "abcaby" };
    auto suffixLength( GenerateSuffixArray( needle ) );
    std::cout << "Suffix array is: ";
    std::copy( suffixLength.begin(), suffixLength.end(), std::ostream_iterator< int >( std::cout, " " ) );
    std::cout << std::endl;

    auto i = 0, j = 0;
    bool found = false;
    while( i < haystack.size() && j < needle.size() ) {
        while( haystack[ i ] == needle[ j ] ) {
            ++i;
            ++j;
            if( j == needle.size() ) {
                found = true;
            }
        }

        if( found ){
            break;
        }

        j = suffixLength[j - 1];
        while( i < haystack.size() && haystack[i] != needle[j] ) {
            ++i;
        }
    }

    if( found ) {
        std::cout << needle << " was found in " << haystack << std::endl;
    }

    return 0;
}