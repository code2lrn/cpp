//
// Created by Ranga on 6/5/16.
//

#include <iostream>
#include <vector>
#include <sstream>

void AlmostSorted( std::vector< int >& array ) {
    const int numElements = array.size();
    int i = 0;
    while( i + 1 < numElements && array[ i ] <= array[ i + 1 ] ) {
        ++i;
    }

    int j = std::max( 1, numElements - 1 );
    while( i < j && array[ j - 1 ] <= array[ j ] ) {
        j--;
    }

    std::swap( array[ i ], array[ j ] );
    int originalI = i, originalJ = j;
    while( i < j && array[ i ] <= array[ j ] ) {
        i++;
        j--;
    }

    std::string result{ "no" };
    if( i >= j ) {
        std::stringstream tmp;
        tmp << "swap " << originalI << " " << originalJ;
        result = tmp.str();
    }
    else {
        i = originalI;
        j = originalJ;
        while( i < j && array[ i ] >= array[ j ] ) {
            i++;
            j--;
        }
        if( i >= j ) {
            std::stringstream tmp;
            tmp << "reverse " << originalI << " " << originalJ;
            result = tmp.str();
        }
    }

    std::cout << "The points of replacement are " << i << " and " << j << ". Result is " << result << std::endl;
}

int main(int argc, char *argv[] ) {
    int numElements, element;
    std::vector< int > array;
    std::cin >> numElements;
    int i = 0;
    while( i++ < numElements && std::cin >> element ) {
        array.push_back( element );
    }

    AlmostSorted( array );
    return 0;
}