//
// Created by Ranga on 4/14/17.
//

#include <string>
#include <iostream>
#include <limits>

unsigned TurnsForGame( std::string str ) {

    unsigned turns = 0;
    const std::string pat1{ "000" }, pat2{ "010" };
    const std::string::size_type NOT_FOUND = std::numeric_limits< std::string::size_type >::max();
    while( true ) {
        std::string::size_type pos = str.find( pat1 );
        if( pos == NOT_FOUND ) {
            pos = str.find( pat2 );
            if( pos == NOT_FOUND ) {
                break;
            }
        }

        str.replace( str.begin() + pos, str.begin() + pos + 3, "00" );
        ++turns;
    }

    return turns;
}

unsigned TurnsForGameOptimized( const std::string &str ) {

    unsigned turns = 0;
    auto strSize = str.size();
    auto s = str.c_str();
    int x = 0;
    for( std::string::size_type i = 1; i < strSize - 1; ) {
        int y = i + 1;
        if( s[ x ] == 0 && s[ x ] == s[ y ] ) {
            ++turns;
            ++i;
        }
        else if( s[ x ] == '1' ) {
            while( s[ i ] != '0' && i < strSize - 1 ) {
                ++i;
            }
            x = i - 1;
        }
    }
    return turns;
}

int main( int argc, char *argv[] ) {

/*
    int queries;
    std::cin >> queries;
    while( queries-- ) {
        int num;
        std::cin >> num;
        std::string str;
        str.reserve( num );
        while( num-- ) {
            char ch;
            std::cin >> ch;
            str += ch;
        }
        //std::cout << ( TurnsForGame( str ) % 2 == 1 ? "Alice" : "Bob" ) << std::endl;
        std::cout << ( TurnsForGameOptimized( str ) % 2 == 1 ? "Alice" : "Bob" ) << std::endl;
    }
*/

    std::cout << ( TurnsForGameOptimized( "000000" ) % 2 == 1 ? "Alice" : "Bob" ) << std::endl;

    return 0;
}