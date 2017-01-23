//
// Created by Ranga on 1/22/17.
//

#include <iostream>
#include <string>

unsigned AnagramEditdist( std::string &str, int i, int j ) {
    if( i >= j ) {
        return 0;
    }

    if( str[ i ] == str[ j ] ) {
        return( AnagramEditdist( str, i + 1, j - 1 ) );
    }
    else {
        return 1 + std::min( AnagramEditdist( str, i + 1, j ), AnagramEditdist( str, i, j - 1 ) );
    }
}

int main() {

    std::string input;
    while( std::cin >> input ) {
        std::cout << "The edit distance for " << input << " to an anagram is " << AnagramEditdist( input, 0, input.size() - 1) << std::endl;
    }

    return 0;
}