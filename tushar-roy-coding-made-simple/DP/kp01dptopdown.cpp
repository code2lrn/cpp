//
// Created by Ranga on 2/12/17.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include <map>

class Knapsack01DPTopdown {
public:
    Knapsack01DPTopdown( const unsigned mw, const std::vector< unsigned > &w, const std::vector< unsigned > &v ) : maxw( mw ), weights( w ), values( v ) {
    }

    unsigned GetBestValue() {
        if( maxw == 0 || weights.size() == 0 || weights.size() != values.size() )
            return 0;

        ValueByRemainingWeightAndItemCount remembered;
        return GetValueRecursive( maxw, 0, weights.size(), remembered );
    }

private:
    unsigned maxw;
    std::vector< unsigned > weights, values;

    using ValueByRemainingWeightAndItemCount = std::map< std::pair< unsigned, unsigned >, unsigned >;

    unsigned GetValueRecursive( unsigned weightRemaining, unsigned currItem, unsigned totalItems, ValueByRemainingWeightAndItemCount &remembered ) {
        if( weightRemaining <= 0 || currItem >= totalItems )
            return 0;

        std::pair< unsigned, unsigned  > remWeightAndItems = std::make_pair( weightRemaining, totalItems - currItem -1 );
        auto hit = remembered.find( remWeightAndItems );
        if( hit != remembered.end() )
            return hit->second;

        unsigned bestValue;
        if( weightRemaining < weights[ currItem ] )
            bestValue = GetValueRecursive( weightRemaining, currItem + 1, totalItems, remembered );
        else
            bestValue = std::max( values[ currItem ] + GetValueRecursive( weightRemaining - weights[ currItem ], currItem + 1, totalItems, remembered ),
                                  GetValueRecursive( weightRemaining, currItem + 1, totalItems, remembered ) );

        remembered.insert( std::make_pair( remWeightAndItems, bestValue ) );
        return bestValue;
    }
};

int main(int argc, char *argv[] ) {

    unsigned maxw, num, w, v;
    std::cin >> maxw >> num;
    std::vector< unsigned > weights( num ), values( num );
    while( num-- ) {
        std::cin >> w >> v;
        weights.push_back( w );
        values.push_back( v );
    }

    Knapsack01DPTopdown kp( maxw, weights, values );
    std::cout << "The best value to select is " << kp.GetBestValue() << "\n";
    return 0;
}
