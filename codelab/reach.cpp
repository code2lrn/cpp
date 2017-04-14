//
// Created by Ranga on 3/11/17.
//

#include <vector>
#include <cstddef>
#include <cstdlib>
#include <limits>
#include <array>
#include <cmath>
#include <iostream>

using Point = std::pair< int, int >;

double Distance( const Point &a, const Point &b ) {
    return sqrt( std::pow( a.first - b.first, 2 ) + std::pow( a.second - b.second, 2 ) );
}

Point GetClosestLocation( const Point &origin, const Point &destn ) {

    Point closestLocation( origin );
    auto minDist = std::numeric_limits< double >::max();
    std::array< int, 3 > increments{ -1, 0, 1 };
    for( int i = 0; i < increments.size(); ++i ) {
        for( int j = 0; j < increments.size(); ++j ) {
            if( i == 0 && j == 0 ) {
                continue;
            }
            Point p = std::make_pair( origin.first + increments[ i ], origin.second + increments[ j ] );
            auto dist = Distance( p, destn );
            if( dist < minDist ) {
                minDist = dist;
                closestLocation = p;
            }
        }
    }

    return closestLocation;
}

unsigned GetStepsToLocation( const Point &origin, const Point &destn ) {
    unsigned x = abs( origin.first - destn.first ), y = abs( origin.second - destn.second );
    return std::max( x, y );
}

unsigned CalculateSteps( const std::vector< int > &x, const std::vector< int > &y ) {
    if( x.size() == 0 || x.size() != y.size() ) {
        return 0;
    }

    Point lastLocation = std::make_pair( x[ 0 ], y[ 0 ] );
    unsigned steps = 0;
    for( size_t i = 1; i < x.size(); ++i ) {
        Point nextLocation = std::make_pair( x[ i ], y[ i ] );
        steps += GetStepsToLocation( lastLocation, nextLocation );
        lastLocation = nextLocation;
    }

    return steps;
}

int main(int argc, char *argv[] ) {

    std::vector< int > X{ 2, -7, -13 };
    std::vector< int > Y{ 2, 1, -5 };
    auto numSteps = CalculateSteps( X, Y );
    std::cout << numSteps << std::endl;

    return 0;
}