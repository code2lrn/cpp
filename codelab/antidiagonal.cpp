//
// Created by Ranga on 3/11/17.
//

#include <vector>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <cassert>

std::vector< std::vector< int > > GetAntiDiagonal(const std::vector< std::vector< int > > &A ) {
    std::vector< std::vector< int > > output;

    size_t rowLimit = 0;
    for( size_t colLimit = 0; colLimit < A.size(); ++colLimit ) {
        auto x = rowLimit, y = colLimit;
        std::vector< int > row;
        while( x >= 0 && x < A.size() && y >= 0 && y < A.size() ) {
            row.push_back( A[ x ][ y ] );
            ++x;
            --y;
        }

        assert( row.size() > 0 );
        output.push_back( std::move( row ) );
    }

    size_t colLimit = A.size() - 1;
    for( size_t rowLimit = 1; rowLimit < A.size(); ++rowLimit ) {
        auto x = rowLimit, y = colLimit;
        std::vector< int > row;
        while( x >= 0 && x < A.size() && y >= 0 && y < A.size() ) {
            row.push_back( A[ x ][ y ] );
            ++x;
            --y;
        }

        assert( row.size() > 0 );
        output.push_back( std::move( row ) );
    }

    return std::move( output );
}

int main( int argc, char *argv[] ) {

    std::vector< std::vector< int > > A{ {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16} };
    auto antiDiagonal = GetAntiDiagonal( A );
    std::for_each( antiDiagonal.begin(), antiDiagonal.end(), []( const auto &row ){
        std::copy( row.begin(), row.end(), std::ostream_iterator< int >( std::cout, " " ) );
        std::cout << std::endl;
    } );

    return 0;
}