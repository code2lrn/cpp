//
// Created by Ranga on 5/21/17.
//

#include <iostream>

void GenerateBitonicPattern(int n ) {
    if( n < 0 || n % 2 == 0 ) {
        return;
    }

    int patStart = n/2, patEnd = n/2, halfwayMark = n/2;
    for( int i = 0; i < n; ++i ) {
        for( int j = 0; j < n; ++j ) {
            if( j >= patStart && j <= patEnd )
                std::cout << 'X';
            else
                std::cout << '-';
        }
        std::cout << std::endl;
        if( i < halfwayMark ) {
            --patStart; ++patEnd;
        }
        else {
            ++patStart; --patEnd;
        }
    }
}

int main( int argc, char *argv[] ) {

    GenerateBitonicPattern( 11 );
    return 0;
}