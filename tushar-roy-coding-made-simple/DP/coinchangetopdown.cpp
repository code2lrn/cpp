//
// Created by Ranga on 2/19/17.
//

#include <map>
#include <iostream>
#include <vector>
#include <limits>

unsigned MinimumChangeFor( unsigned total, const std::vector< unsigned > &denominations, std::map< unsigned, unsigned > &minChangeByTotal ) {
    if( total == 0 ) {
        return 0;
    }

    auto found = minChangeByTotal.find( total );
    if( found != minChangeByTotal.end() ) {
        return found->second;
    }

    unsigned minChange = std::numeric_limits< unsigned >::max();
    for( size_t i = 0; i < denominations.size(); ++i ) {
        if( denominations[ i ] > total )
            continue;

        minChange = std::min( minChange, MinimumChangeFor( total - denominations[ i ], denominations, minChangeByTotal ) );
    }

    if( minChange != std::numeric_limits< unsigned >::max() )
        minChange = minChange + 1;

    minChangeByTotal[ total ] = minChange;
    return minChange;
}

int main(int argc, char *argv[] ) {

    unsigned total = 14;
    std::vector< unsigned > denominations{ 1, 2, 3 };
    std::map< unsigned, unsigned > minChangeByTotal;

    std::cout << MinimumChangeFor( total, denominations, minChangeByTotal ) << std::endl;

    return 0;
}
