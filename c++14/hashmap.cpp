//
// Created by Ranga on 6/5/16.
//

#include <functional>
#include <iostream>
#include <unordered_map>
#include <algorithm>

struct MyHash {
    size_t operator()( const std::string& str ) const {
        std::string s;
        std::transform( str.begin(), str.end(), std::back_inserter( s ), []( auto& ch ) { return std::tolower( ch ); } );
        auto hashVal = hasher( s );
        return hashVal;
    }
    std::hash< std::string > hasher;
};

int main( int argc, char *argv[] ) {

    std::unordered_map< std::string, std::string, MyHash > primeMinisters;
    primeMinisters.insert( std::make_pair( "Narendra", "Modi" ) );
    primeMinisters.insert( std::make_pair( "narendra", "Modi" ) );
    primeMinisters.insert( std::make_pair( "narendra", "Singh" ) );
    return 0;
}