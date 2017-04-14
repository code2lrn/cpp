//
// Created by Ranga on 3/19/17.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

bool FactorSumPossible( const std::vector< unsigned > &a, const unsigned tgt ) {
    using Entry = std::pair< bool, unsigned >;
    std::vector< std::vector< Entry > > table( 1 + a.size(), std::vector< Entry >( tgt + 1 ) );

    for( size_t i = 1; i <= a.size(); ++i ) {
        for( size_t j = 1; j <= tgt; ++j ) {
            if( table[ i - 1 ][ j ].first == true ) {
                table[ i ][ j ].first = true;
            }
            else {
                auto curNum = a[ i - 1 ];
                for( size_t k = 1; k <= j / curNum; ++k ) {
                    auto remainder = j - ( k * curNum );
                    if( remainder == 0 || table[ i - 1 ][ remainder ].first == true ) {
                        table[ i ][ j ] = std::make_pair( true, k );
                    }
                }
            }
        }
    }
    std::for_each( table.begin() + 1, table.end(), []( const auto &row ){
        std::for_each( row.begin() + 1, row.end(), []( const auto &p ) {
            std::cout << "(" << p.first << "," << p.second << "), ";
        } );
        std::cout << std::endl;
    } );
    return table[ a.size() ][ tgt ].first == true;
}

int main(int argc, char *argv[] ) {
    const std::vector< unsigned > a{ 6, 9, 20 };
    const unsigned target = 23  ;
    std::cout << std::boolalpha << FactorSumPossible( a, target ) << std::endl;
    return 0;
}