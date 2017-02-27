//
// Created by Ranga on 2/26/17.
//

#include <numeric>
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

int GetRank(const char *name ) {
    auto ptr = name;
    char values[ 26 ] = {0};
    while( ptr && *ptr != 0 ) {
        if( *ptr >= 'A' && *ptr <= 'Z' ) {
            values[ *ptr - 'A' ] = 1;
        }
        ++ptr;
    }

    return std::accumulate( values, values + 26, 0 );
}

int main( int argc, char *argv[] ) {

    unsigned numTestCases;
    std::cin >> numTestCases;
    while( numTestCases-- ) {
        auto bestRank = std::numeric_limits< int >::min();
        std::vector< std::string > topRankers;
        unsigned numContenders;
        std::cin >> numContenders;
        std::cin >> std::ws;
        std::string contender;
        while( numContenders-- ) {
            std::getline( std::cin, contender, '\n' );
            auto rank = GetRank( contender.c_str() );
            if( rank > bestRank ) {
                bestRank = rank;
                topRankers.clear();
                topRankers.push_back( contender );
            }
            if( rank == bestRank ) {
                topRankers.push_back( contender );
            }
        }
        std::sort( topRankers.begin(), topRankers.end() );
        std::cout << topRankers[ 0 ] << std::endl;
    }

    return 0;
}