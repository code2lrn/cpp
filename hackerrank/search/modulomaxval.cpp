//
// Created by Ranga on 5/22/16.
//

#include <algorithm>
#include <iostream>

using ULL = unsigned long long;
using MyArray = std::vector< ULL >;

ULL BoundedSum( ULL x, ULL y ) {
    if( x < 0 && y < 0 && x + y > 0) {
        return std::numeric_limits< ULL >::min();
    }
    if( x > 0 && y > 0 && ( x + y < 0 || x + y < x || x + y < y ) ) {
        std::__throw_out_of_range( "Number exceeded ULL limit" );
        return std::numeric_limits< ULL >::max();
    }
    return x + y;
}

int ModuloMax( const int moduloNum, int x, int y ) {
    auto a = x % moduloNum;
    auto b = y % moduloNum;
    return a > b ? x : y;
}

int ModuloMaxSubArray( const MyArray &array, const int moduloNum, const int left, const int right ) {
    if( left > right ) {
        return std::numeric_limits< int >::min();
    }

    if( left == right ) {
        return ModuloMax( moduloNum, array[ left ], 0 );
    }

    auto mid = ( left + right ) / 2;
    auto runningSum = 0;
    auto maxSumSoFar = 0;
    for( auto i = left; i < right; ++i ) {
        runningSum  = ModuloMax( moduloNum, BoundedSum( runningSum, array[ i ] ), array[ i ] );
        maxSumSoFar = ModuloMax( moduloNum, maxSumSoFar, runningSum );
    }

    auto leftSum = ModuloMaxSubArray( array, moduloNum, left, mid );
    auto rightSum = ModuloMaxSubArray( array, moduloNum, mid + 1, right );
    return leftSum < maxSumSoFar ? ModuloMax( moduloNum, maxSumSoFar, rightSum ) : ModuloMax( moduloNum, leftSum, rightSum );
}

int main( int argc, char *argv[] ) {
    int numTests;
    std::cin >> numTests;
    while( numTests-- ) {
        int arraySize, moduloNum;
        std::cin >> arraySize >> moduloNum;
        auto i = arraySize;
        ULL value;
        MyArray input;
        while( i-- && std::cin >> value ) {
            input.push_back( value );
        }

        std::cout << ModuloMaxSubArray( input, moduloNum, 0, input.size() ) << std::endl;
    }

    return 0;
}