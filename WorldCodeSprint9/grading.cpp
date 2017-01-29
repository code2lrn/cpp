//
// Created by Ranga on 1/27/17.
//

#include <iostream>
#include <cmath>

int main( int argc, char *argv[] ) {

    unsigned numGrades;
    std::cin >> numGrades;
    while( numGrades-- > 0 ) {
        unsigned grade;
        std::cin >> grade;
        if( grade < 38 ) {
            std::cout << grade << "\n";
            continue;
        }

        unsigned factor = floor( grade / 5 );
        if( ( factor + 1 ) * 5 - grade < 3 ) {
            std::cout << ( factor + 1 ) * 5 << "\n";
        }
        else {
            std::cout << grade << "\n";
        }
    }

    return 0;
}
