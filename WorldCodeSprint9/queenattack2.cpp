//
// Created by Ranga on 1/27/17.
//

#include <iostream>
#include <cmath>
#include <bitset>
#include <vector>
#include <map>
#include <set>

class GridImpl {
public:
    GridImpl( unsigned x, unsigned y ) : rows( x ), cols( y ) {
        data.reserve( rows + 1 );
        for( unsigned i = 0; i <= rows; ++i ) {
            data.push_back( std::bitset< 100000 >() );
        }
    }

    bool IsSet( unsigned x, unsigned y ) {
        return data[ x ][ y ];
    }

    void SetValue( unsigned x, unsigned y, bool value ) {
        data[ x ][ y ] = value;
    }

private:
    unsigned rows, cols;
    std::vector< std::bitset< 100000 > > data;
};

class GridImplMap {
public:
    GridImplMap( unsigned x, unsigned y ) : rows( x ), cols( y ) {
    }

    bool IsSet( unsigned x, unsigned y ) {
        return data.find( std::make_pair( x, y ) ) != data.end();
    }

    void SetValue( unsigned x, unsigned y, bool value ) {
        data.insert( std::make_pair( x, y ) );
    }

private:
    unsigned rows, cols;
    std::set< std::pair< unsigned, unsigned > > data;
};

class Grid {
public:
    Grid( unsigned g, unsigned o ) : gridSize( g ), numObstacles( o ), gridImpl( gridSize, gridSize ) { }

    void MarkValue( unsigned x, unsigned y, unsigned value ) {
        if( value == Grid::ObstacleVal ) {
            gridImpl.SetValue( x, y, true );
        }

        if( value == Grid::QueenVal ) {
            qX = x; qY = y;
        }
    }

    unsigned CalculateNumMoves() {
        unsigned numMoves = 0;

        // count left
        for( unsigned col = qY - 1; col > 0; --col ) {
            if( gridImpl.IsSet( qX, col ) )
                break;
            ++numMoves;
        }
        // count right
        for( unsigned col = qY + 1; col <= gridSize; ++col ) {
            if( gridImpl.IsSet( qX, col ) )
                break;
            ++numMoves;
        }
        // count up
        for( unsigned row = qX - 1; row > 0; --row ) {
            if( gridImpl.IsSet( row, qY ) )
                break;
            ++numMoves;
        }
        // count down
        for( unsigned row = qX + 1; row <= gridSize; ++row ) {
            if( gridImpl.IsSet( row, qY ) )
                break;
            ++numMoves;
        }
        // top-left
        for( unsigned row = qX - 1, col = qY - 1; row > 0 && col > 0; --row, --col ) {
            if( gridImpl.IsSet( row, col  ) )
                break;
            ++numMoves;
        }
        // top-right
        for( unsigned row = qX - 1, col = qY + 1; row > 0 && col <= gridSize; --row, ++col ) {
            if( gridImpl.IsSet( row, col ) )
                break;
            ++numMoves;
        }
        // bottom-right
        for( unsigned row = qX + 1, col = qY + 1; row <= gridSize && col <= gridSize; ++row, ++col ) {
            if( gridImpl.IsSet( row, col ) )
                break;
            ++numMoves;
        }
        // bottom-left
        for( unsigned row = qX + 1, col = qY - 1; row <= gridSize && col > 0; ++row, --col ) {
            if( gridImpl.IsSet( row, col ) )
                break;
            ++numMoves;
        }

        return numMoves;
    }

private:
    unsigned gridSize, numObstacles, qX, qY;
    GridImplMap gridImpl;

public:
    static const unsigned QueenVal = 2, ObstacleVal = 1;
};

int main(int argc, char* argv[] ) {

    unsigned gridSize, numObstacles, X, Y;
    std::cin >> gridSize >> numObstacles;
    Grid g( gridSize, numObstacles );
    std::cin >> X >> Y;
    g.MarkValue( X, Y, Grid::QueenVal );
    for( unsigned i =0; i < numObstacles; ++i ) {
        std::cin >> X >> Y;
        g.MarkValue( X, Y, Grid::ObstacleVal );
    }
    std::cout << g.CalculateNumMoves() << "\n";

    return 0;
}