//
// Created by Ranga on 6/23/16.
//

#include <iostream>
#include <vector>
#include <algorithm>

int main( int argc, char *argv[] ) {
    unsigned numWords;
    std::cin >> numWords;
    std::string word;
    std::vector< std::string > words;
    words.reserve( numWords );
    while( numWords-- && std::cin >> word ) {
        words.push_back( word );
    }

    size_t shortestWordLength = std::numeric_limits< unsigned >::max();
    std::for_each( words.begin(), words.end(), [&shortestWordLength] ( auto &str ) { shortestWordLength = std::min( shortestWordLength, str.length() ); } );
    std::cout << "The shortest word is " << shortestWordLength << std::endl;

    size_t longestPrefix;
    for( longestPrefix = 0; longestPrefix< shortestWordLength; ++longestPrefix ) {
        auto ch = words[ 0 ][ longestPrefix ];
        auto allCharsSame = true;
        std::for_each( words.begin() + 1, words.end(), [&] ( auto &str ) { allCharsSame = ( ch == str[ longestPrefix ] ); } );
        if( !allCharsSame ) {
            break;
        }
    }

    std::cout << "The longest prefix length is " << longestPrefix << std::endl;
    return 0;
}