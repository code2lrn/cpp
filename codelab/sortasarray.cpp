//
// Created by Ranga on 2/19/17.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

int main(int argc, char *argv[] ) {

    std::vector< int > a;
    int n;
    while( std::cin >> n ) {
        a.push_back( n );
    }

    std::sort( a.begin(), a.end() );
    std::copy( a.begin(), a.end(), std::ostream_iterator< int >( std::cout, " " ) );
    std::cout << std::endl;
    for( auto i = 0; i < a.size() - 1; i += 2 ) {
        std::swap( a[ i ], a[ i + 1 ] );
    }
    std::copy( a.begin(), a.end(), std::ostream_iterator< int >( std::cout, " " ) );

    return 0;
}