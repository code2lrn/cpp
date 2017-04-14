//
// Created by Ranga on 3/19/17.
//

#include <vector>
#include <iostream>

unsigned MoveNonZeroes( std::vector< int > &a ) {
    int i = 0, j = a.size() - 1;
    while( i < j ) {
        while( i < j && a[ i ] != 0 ) {
            ++i;
        }
        while( i < j && a[ j ] == 0 ) {
            --j;
        }
        if( i < j ) {
            std::swap( a[ i ], a[ j ] );
        }
    }

    return i;
}

int main(int argc, char *argv[] ) {

    std::vector< int > a{ 99,-2,1,0,2,0,0,3,4,0,0,1,0,0,0 };
    std::cout << MoveNonZeroes( a ) << std::endl;
    return 0;
}