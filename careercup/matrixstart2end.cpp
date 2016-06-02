//
// Created by Ranga on 6/1/16.
//

#include <iterator>
#include <iostream>
#include <algorithm>

using Matrix = std::vector< std::vector< unsigned > >;
using Coordinate = std::pair< unsigned, unsigned >;

struct MatrixHelper {
    MatrixHelper( unsigned x, unsigned y ) : M( x ), N( y ) { }
    bool IsValidCoordinate( const Coordinate &c ) const { return c.first < M && c.second < N; }

    unsigned M, N;
};

void TraverseAndMarkNode( Matrix &m, const MatrixHelper &mh, const Coordinate &start, const Coordinate &destination ) {
    if( start == destination ) {
        if( m[ destination.first ][ destination.second ] > 0 ) {
            ++m[ destination.first ][ destination.second ];
        }
        return;
    }

    auto right = std::make_pair( start.first, start.second + 1 );
    if( mh.IsValidCoordinate( right ) && m[ right.first ][ right.second ] > 0 ) {
        TraverseAndMarkNode( m, mh, right, destination );
    }
    auto down  = std::make_pair( start.first + 1, start.second );
    if( mh.IsValidCoordinate( down ) && m[ down.first ][ down.second ] > 0 ) {
        TraverseAndMarkNode( m, mh, down, destination );
    }
    auto bRight= std::make_pair( start.first + 1, start.second + 1 );
    if( mh.IsValidCoordinate( bRight ) && m[ bRight.first ][ bRight.second ] > 0 ) {
        TraverseAndMarkNode( m, mh, bRight, destination );
    }
}

int main( int argc, char *argv[] ) {
    unsigned M, N;
    std::cout << "Enter matrix(M,N) dimension: ";
    std::cin >> M >> N;
    Matrix m;
    for( auto i = 0; i < M; ++i ) {
        std::vector< unsigned > row;
        unsigned j = 0, num = 0;
        while( j++ < N && std::cin >> num ) {
            row.push_back( num );
        }
        m.push_back( row );
    }

    MatrixHelper mh{ M, N };
    TraverseAndMarkNode( m, mh, std::make_pair( 0, 0 ), std::make_pair( M - 1, N - 1) );
    std::cout << "The number of paths to the bottom right is: " << ( m[ M - 1 ][ N - 1 ] > 0 ? m[ M - 1 ][ N - 1 ] - 1 : 0 ) << std::endl;
    return 0;
}