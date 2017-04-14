//
// Created by Ranga on 3/9/17.
//

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

using Matrix = std::vector< std::vector< int > >;

bool CanGoThere( const Matrix &m, unsigned r, unsigned c ) {
    if( r < 0 || r >= m.size() ) {
        return false;
    }

    if( c < 0 || c >= m[ 0 ].size() ) {
        return false;
    }

    return m[ r ][ c ] == 1;
}

int DFSTraverse( Matrix &m, unsigned i, unsigned j, unsigned rows, unsigned cols, int imageDepth ) {
    m[ i ][ j ] = imageDepth;

    // top
    if( CanGoThere( m, i - 1, j ) )
        imageDepth = std::max( imageDepth, DFSTraverse( m, i - 1, j, rows, cols, imageDepth + 1 ) );

    // bottom
    if( CanGoThere( m, i + 1, j ) )
        imageDepth = std::max( imageDepth, DFSTraverse( m, i + 1, j, rows, cols, imageDepth + 1 ) );

    // right
    if( CanGoThere( m, i, j + 1 ) )
        imageDepth = std::max( imageDepth, DFSTraverse( m, i, j + 1, rows, cols, imageDepth + 1 ) );

    // left
    if( CanGoThere( m, i, j - 1 ) )
        imageDepth = std::max( imageDepth, DFSTraverse( m, i, j - 1, rows, cols, imageDepth + 1 ) );

    return imageDepth;
}

void DFSMark( Matrix &m, unsigned i, unsigned j ) {
    m[ i ][ j ] = 0;
    // top
    if( CanGoThere( m, i - 1, j ) )
        DFSMark( m, i - 1, j );

    // bottom
    if( CanGoThere( m, i + 1, j ) )
        DFSMark( m, i + 1, j );

    // right
    if( CanGoThere( m, i, j + 1 ) )
        DFSMark( m, i, j + 1 );

    // left
    if( CanGoThere( m, i, j - 1 ) )
        DFSMark( m, i, j - 1 );
}

void DeleteLargestImage( Matrix &m ) {
    if( m.size() == 0 )
        return;

    Matrix output( m );
    auto rows = output.size(); // 3
    auto cols = output[ 0 ].size(); // 7
    int largestImageSize = 0, x, y;
    for( unsigned i = 0; i < rows; ++i ) {
        for( unsigned j = 0; j < cols; ++j ) {
            if( output[ i ][ j ] == 1 ) {
                auto l = DFSTraverse( output, i, j, rows, cols, 1 );
                if( l > largestImageSize ) {
                    x = i;
                    y = j;
                    largestImageSize = l;
                }
            }
        }
    }

    if( largestImageSize > 0 ) {
        DFSMark( m, x, y );
    }
}

int main( int argc, char *argv[] ) {

    std::cout << "Input" << std::endl;
    Matrix m1{ { 0, 0, 0, 0, 1, 1, 0 },
               { 0, 0, 0, 1, 0, 0, 0 },
               { 0, 0, 1, 1, 1, 0, 1 }, };

    std::for_each( m1.begin(), m1.end(), []( const auto &row ) {
        std::copy( row.begin(), row.end(), std::ostream_iterator< int >( std::cout, " " ) );
        std::cout << std::endl;
    } );

    std::cout << "Output" << std::endl;
    DeleteLargestImage( m1 );
    std::for_each( m1.begin(), m1.end(), []( const auto &row ) {
        std::copy( row.begin(), row.end(), std::ostream_iterator< int >( std::cout, " " ) );
        std::cout << std::endl;
    } );

    std::cout << "Input" << std::endl;
    Matrix m2{ { 0, 0, 1, 0, 1, 0, 0 },
               { 0, 0, 1, 1, 1, 0, 0 },
               { 0, 0, 1, 1, 1, 0, 1 }, };

    std::for_each( m2.begin(), m2.end(), []( const auto &row ) {
        std::copy( row.begin(), row.end(), std::ostream_iterator< int >( std::cout, " " ) );
        std::cout << std::endl;
    } );

    std::cout << "Output" << std::endl;
    DeleteLargestImage( m2 );
    std::for_each( m2.begin(), m2.end(), []( const auto &row ) {
        std::copy( row.begin(), row.end(), std::ostream_iterator< int >( std::cout, " " ) );
        std::cout << std::endl;
    } );

    return 0;
}