//
// Created by shiva on 2/22/17.
//


#include <string>
#include <algorithm>
#include <iostream>

int main(int argc, char *argv[] ) {

    int A = 25;
    std::vector< std::vector< int > > tri;

    tri.push_back( std::vector< int >{ 1 } );
    if( A > 1 ) {
        int *prev = new int[ A ];
        int *curr = new int[ A ];
        *prev = *curr = 1;
        for( int row = 2; row <= A; ++row ) {
            int i;
            for( i = 1; i < row - 1; ++i ) {
                curr[ i ] = prev[ i ] + prev[ i - 1 ];
            }
            curr[ i ] = 1;
            std::vector< int > v;
            for( int j = 0; j <= i; ++j )
                v.push_back( curr[ j ] );
            tri.push_back( std::move( v ) );
            int *t = prev;
            prev = curr;
            curr = t;
        }
        delete [] prev;
        delete [] curr;
    }


    return 0;
}