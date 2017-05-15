//
// Created by Ranga on 5/14/17.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

class Matrix {
public:
    Matrix( unsigned m ) : dim( m ), data( Matrix::Initialize( m ) ) {
        for( auto &row : data ) {
            std::copy( row.begin(), row.end(), std::ostream_iterator< unsigned >( std::cout, " " ) );
            std::cout << std::endl;
        }
    }

    void SpiralPrint() {
        SpiralPrint( 0, dim - 1 );
    }

private:
    using MatrixData = std::vector< std::vector< unsigned > >;
    MatrixData data;
    unsigned dim;

    static MatrixData Initialize( unsigned m ) {
        MatrixData d;
        for( unsigned i = 0; i < m; ++i ) {
            unsigned val = i * m;
            std::vector< unsigned > row;
            std::generate_n( std::back_inserter( row ), m, [ &val ] { return val++; } );
            d.push_back( row );
        }

        return d;
    }

    void SpiralPrint( int from, int to ) {
        if( from > to )
            return;

        if( from == to ) {
            std::cout << data[ from ][ to ] << std::endl;
            return;
        }

        for( int i = from; i <= to; ++i )
            std::cout << data[ from ][ i ] << " ";

        for( int i = from + 1; i <= to; ++i )
            std::cout << data[ i ][ to ] << " ";

        for( int i = to - 1; i >= from; --i )
            std::cout << data[ to ][ i ] << " ";

        for( int i = to - 1; i > from; --i )
            std::cout << data[ i ][ from ] << " ";

        SpiralPrint( from + 1, to - 1);
    }
};

int main( int argc, char *argv[] ) {

    Matrix m1( 5 );
    m1.SpiralPrint();
    return 0;
}