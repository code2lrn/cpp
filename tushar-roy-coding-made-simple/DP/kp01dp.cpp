//
// Created by Ranga on 2/12/17.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>

class Knapsack01DP {
public:
    Knapsack01DP( const unsigned mw, const std::vector< unsigned > &w, const std::vector< unsigned > &v ) : maxw( mw ), weights( w ), values( v ) {
    }

    unsigned GetBestValue() {
        if( maxw == 0 || weights.size() == 0 || weights.size() != values.size() )
            return 0;

        std::vector< std::vector< unsigned > > results( weights.size() + 1 );
        for( size_t i = 0; i < weights.size() + 1; ++i ) {
            results[ i ] = std::vector< unsigned >( maxw + 1 );
            results[ i ][ 0 ] = 0; // Cant pick anything if max weight allowed is 0
            if( i == 0 ) {
                std::fill( results[ 0 ].begin(), results[ 0 ].end(), 0 );
            }
        }

        for( size_t i = 1; i <= weights.size(); ++i ) {
            auto curItemWeight = weights[ i ];
            auto curItemValue  = values[ i ];
            for( size_t j = 1; j <= maxw; ++j ) {
                if( curItemWeight > j ) {
                    // inherit prior value
                    results[ i ][ j ] = results[ i - 1 ][ j ];
                }
                else {
                    // decide best value
                    results[ i ][ j ] = std::max( curItemValue + results[ i - 1 ][ j - curItemWeight ], results[ i - 1 ][ j ] );
                }
            }
        }
        return results[ weights.size() ][ maxw ];
    }

private:
    unsigned maxw;
    std::vector< unsigned > weights, values;
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

    Knapsack01DP kp( maxw, weights, values );
    std::cout << "The best value to select is " << kp.GetBestValue() << "\n";
    return 0;
}
