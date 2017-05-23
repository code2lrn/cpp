//
// Created by Ranga on 5/21/17.
//

#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <array>

bool IsValidTriplet( const std::string &triplet ) {
    return triplet.size() > 0 && triplet.size() < 4 && std::stoul( triplet ) <= 255;
}

void GenIPAddr( const std::string &str, int si, std::vector< std::string > &triplets, int tripletsFound ) {
    if( tripletsFound == 4 ) {
        std::copy( triplets.begin(), triplets.end(), std::ostream_iterator< std::string >( std::cout, "." ) );
        std::cout << std::endl;
        return;
    }

    for( auto i = 1; i <= 3; ++i ) {
        if( si + i > str.size() ) {
            return;
        }

        std::string triplet = str.substr( si, i );
        if( !IsValidTriplet( triplet ) ) {
            continue;
        }
        triplets[ tripletsFound ] = triplet;
        GenIPAddr( str, si + i, triplets, tripletsFound + 1 );
    }
}

int main( int argc, char *argv[] ) {

    std::string str{ "123456789" };
    std::vector< std::string > triplets( 4, "" );
    GenIPAddr( str, 0, triplets, 0 );
    return 0;
}