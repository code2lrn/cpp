//
// Created by Ranga on 2/26/17.
//

#include <string>
#include <vector>
#include <iostream>

bool WildCardMatch( std::string str, std::string pattern ) {
    str = " " + str;
    pattern = " " + pattern;
    std::vector< std::vector< bool > > matrix( str.size(), std::vector< bool >( pattern.size(), false ) );
    matrix[ 0 ][ 0 ] = true; // Zero length Pattern and zero length string;

    for( unsigned i = 1; i < str.size(); ++i ) {
        for(unsigned j = 1; j < pattern.size(); ++j ) {
            if( pattern[ j ] == '?' ) {
                matrix[ i ][ j ] = matrix[ i - 1 ][ j - 1 ];
            }
            else if( pattern[ j ] == '*' ) {
                matrix[ i ][ j ] = matrix[ i - 1 ][ j ] || matrix[ i ][ j - 1 ];
            }
            else if( str[ i ] == pattern[ j ] ) {
                matrix[ i ][ j ] = matrix[ i - 1 ][ j - 1 ];
            }
            else {
                matrix[ i ][ j ] = false;
            }
        }
    }

    return matrix[ str.size() - 1 ][ pattern.size() - 1 ];
}

int main( int argc, char *argv[] ) {

    std::string str{ "abxcsdsdsa" }, pattern{ "a*b?c*a" };
    std::cout << "WildCardMatch( " << "\"" << str << "\", \"" << pattern << "\"): " << std::boolalpha << WildCardMatch( str, pattern ) << std::endl;

    return 0;
}