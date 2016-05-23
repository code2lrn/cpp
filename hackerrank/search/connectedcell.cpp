//
// Created by Ranga on 5/22/16.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <limits>

using MatrixData = std::vector< std::vector< int > >;

class Matrix {
public:
    Matrix( MatrixData &&data ) {
        rows = static_cast< int >( data.size() );
        cols = static_cast< int >( data.size() ? data[0].size() : 0 );
        this->data = data;
    }

    int& operator()( int row, int col ) {
        return data[ row ][ col ];
    }

    int operator()( int row, int col ) const {
        return data[ row ][ col ];
    }

    bool alreadyTraversed( int i, int j ) {
        return data[ i ][ j ] == -1;
    }

    bool isValidPosition( int i, int j ) {
        return 0 <= i && i < Rows() && 0 <= j && j < Cols();
    }

    const int Rows() { return rows; }
    const int Cols() { return cols; }

private:
    MatrixData data;
    int rows, cols;
};

void RecursiveMarkAndTraverse( Matrix &m, const int i, const int j, int &sum ) {
    if( m( i, j ) != 1 ) {
        return;
    }

    sum++;
    m( i, j ) = -1;
    if( m.isValidPosition( i, j - 1 ) )
        RecursiveMarkAndTraverse( m, i, j - 1, sum  ); // Left
    if( m.isValidPosition( i, j + 1 ) )
        RecursiveMarkAndTraverse( m, i, j + 1, sum  ); // Right
    if( m.isValidPosition( i - 1 , j ) )
        RecursiveMarkAndTraverse( m, i - 1, j, sum  ); // Top
    if( m.isValidPosition( i + 1, j ) )
        RecursiveMarkAndTraverse( m, i + 1, j, sum  ); // Bottom
    if( m.isValidPosition( i - 1 , j - 1 ) )
        RecursiveMarkAndTraverse( m, i - 1, j - 1, sum  ); // Top-Left
    if( m.isValidPosition( i + 1, j - 1 ) )
        RecursiveMarkAndTraverse( m, i + 1, j - 1, sum  ); // Bottom-Left
    if( m.isValidPosition( i - 1 , j + 1 ) )
        RecursiveMarkAndTraverse( m, i - 1, j + 1, sum  ); // Top-Right
    if( m.isValidPosition( i + 1, j + 1 ) )
        RecursiveMarkAndTraverse( m, i + 1, j + 1, sum  ); // Bottom-Right
}

int CalculateConnectedCells( Matrix &matrix ) {
    int maxConnectedCells = 0;
    for( auto i = 0; i < matrix.Rows(); ++i ) {
        for( auto j = 0; j < matrix.Cols(); ++j ) {
            if( matrix.alreadyTraversed( i, j ) || matrix( i, j ) == 0 )
                continue;
            int iterationSum = 0;
            RecursiveMarkAndTraverse( matrix, i, j, iterationSum );
            maxConnectedCells = std::max( maxConnectedCells, iterationSum );
        }
    }
    return maxConnectedCells;
}

int main( int argc, char *argv[] ) {
    int rows, cols;
    std::cin >> rows;
    std::cin >> cols;
    std::string line;
    auto i = rows;
    MatrixData data;
    std::cin.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
    while( i-- && std::getline( std::cin, line ) ) {
        std::stringstream ss( line );
        unsigned num;
        std::vector< int > row;
        auto j = cols;
        while( j-- && ss >> num ) {
            row.push_back( num );
        }
        data.push_back( row );
    }

    Matrix matrix( std::move( data ) );
    std::cout << CalculateConnectedCells( matrix ) << std::endl;

    return 0;
}

