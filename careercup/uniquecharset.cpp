//
// Created by Ranga on 3/13/17.
//

#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>

void Ingest( std::string str, std::unordered_map< std::string, std::vector< std::string > > &charsetWords ) {
    std::transform( str.begin(), str.end(), str.begin(), []( const char &c ){ return tolower( c ); } );
    auto sortedStr( str );
    std::sort( sortedStr.begin(), sortedStr.end() );
    auto newEnd = std::unique( sortedStr.begin(), sortedStr.end() );
    sortedStr.erase( newEnd, sortedStr.end() );
    auto it = charsetWords.find( sortedStr );
    if( it == charsetWords.end() ) {
        charsetWords.insert( it, std::make_pair( sortedStr, std::vector< std::string >{ str } ) );
    }
    else {
        it->second.push_back( str );
    }
}

int main( int argc, char *argv[] ) {
    std::stringstream ss{ "studentssess May student students dog god  Cat act tab bat flow wolf lambs  Amy Yam balms looped poodle john alice" };
    std::string word;
    std::unordered_map< std::string, std::vector< std::string > > charsetWords;
    while( ss >> word ){
        Ingest( word, charsetWords );
    }

    for( const auto &entry : charsetWords ) {
        for( const auto &str : entry.second ) {
            std::cout << " " << str;
        }
        std::cout << std::endl;
    }

    return 0;
}