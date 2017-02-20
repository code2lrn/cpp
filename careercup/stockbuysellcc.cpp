//
// Created by Ranga on 2/14/17.
//

#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>

int main(int argc, char *argv[] ) {

    std::vector< unsigned > prices;
    unsigned price;
    while( std::cin >> price ) {
        prices.push_back( price );
    }

    std::pair< unsigned, unsigned > bestQuote = std::make_pair( prices[ prices.size() - 1 ], prices[ prices.size() - 1 ] );
    unsigned minPrice = std::numeric_limits< unsigned >::max(), maxPrice = std::numeric_limits< unsigned >::min();
    std::for_each( prices.rbegin(), prices.rend(),
                  [ &bestQuote, &minPrice, &maxPrice ] ( const auto &p ) {
                        if( p > maxPrice ) {
                            maxPrice = p;
                            minPrice = p;
                        }

                        minPrice = std::min( minPrice, p );

                        if( maxPrice - minPrice > bestQuote.second - bestQuote.first ) {
                            bestQuote.first = minPrice;
                            bestQuote.second = maxPrice;
                        }
                  } );

    std::cout << "Buy at: " << bestQuote.first << ". Sell at: " << bestQuote.second << std::endl;

    return 0;
}
