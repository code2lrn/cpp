//
// Created by Ranga on 2/19/17.
//

#include <vector>
#include <cstddef>
#include <limits>
#include <iterator>
#include <iostream>

int main(int argc, char *argv[] ) {

    std::vector< unsigned > input{ 2, 3, 1, 1, 2, 4, 2, 0, 1, 1 };
    std::vector< unsigned > cost( input.size(), std::numeric_limits< unsigned  >::max() ), jump( input.size(), 0 );
    cost[ 0 ] = 0;

    for( size_t i = 1; i < input.size(); ++i ) {
        for( size_t j = 0; j < i; ++j ) {
            if( j + input[ j ] >= i ) {
                if( cost[ j ] + 1 < cost[ i ] ) {
                    cost[ i ] = cost[ j ] + 1;
                    jump[ i ] = j;
                }
            }
        }
    }

    std::copy( input.begin(), input.end(), std::ostream_iterator< unsigned >( std::cout, " ") ); std::cout << std::endl;
    std::copy( cost.begin(), cost.end(), std::ostream_iterator< unsigned >( std::cout, " ") ); std::cout << std::endl;
    std::copy( jump.begin(), jump.end(), std::ostream_iterator< unsigned >( std::cout, " ") ); std::cout << std::endl;

    return 0;
}