//
// Created by Ranga on 5/30/16.
//

#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <iterator>

using Matrix = std::vector< std::vector< unsigned > >;

void PrintSpiral( const Matrix &m, int from, int to ) {
    if( from > to ) {
        return;
    }

    for( auto j = from; j <= to; ++j ) { // Go right
        std::cout << m[ from ][ j ] << " " ;
    }

    for( auto i = from + 1; i <= to; ++i ) { // Go Down
        std::cout << m[ i ][ to ] << " ";
    }

    for( auto j = to - 1; j >= from; --j ){ // Go left
        std::cout << m[ to ][ j ] << " ";
    }

    for( auto i = to - 1; i > from; --i ) { // Go Up
        std::cout << m[ i ][ from ] << " ";
    }
    PrintSpiral( m, from + 1, to - 1 );
}

int main( int argc, char *argv[] ) {
    unsigned M;
    std::cout << "Enter matrix dimension: ";
    std::cin >> M;
    Matrix m;
    for( auto i = 0; i < M; ++i ) {
        std::vector< unsigned > row;
        unsigned j = ( i * M );
        std::generate_n( std::back_inserter( row ), M, [ &j ]() { return ++j; } );
        m.push_back( row );
    }

    std::cout << "The input matrix is:\n";
    for( const auto &row : m ) {
        std::copy( row.begin(), row.end(), std::ostream_iterator< unsigned >( std::cout, " " ) );
        std::cout << std::endl;
    }

    PrintSpiral( m, 0, M - 1 );
    return 0;
}