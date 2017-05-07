//
// Created by Ranga on 4/14/17.
//

#include <vector>
#include <iostream>

std::string Sortable( std::vector< int > v ) {

    auto Swappable = []( int x, int y ){ return abs( x - y ) == 1; };
    auto sortable = true;
    for( size_t i = 0, j = 1; j < v.size(); ++i, ++j ) {
        if( v[ i ] > v[ j ] ) {
            if( Swappable( v[ i ], v[ j ] ) ) {
                std::swap( v[ i ], v[ j ] );
            }
            else {
                sortable = false;
                break;
            }
        }
    }

    return sortable ? "Yes" : "No";
}

int main( int argc, char *argv[] ) {

    int queries;
    std::cin >> queries;
    while( queries-- ) {
        int num;
        std::cin >> num;
        std::vector< int > v;
        v.reserve( num );
        while( num-- ) {
            int n;
            std::cin >> n;
            v.push_back( n );
        }
        std::cout << Sortable( v ) << std::endl;
    }

    return 0;
}