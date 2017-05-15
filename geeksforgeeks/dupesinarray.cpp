//
// Created by Ranga on 5/15/17.
//

#include <vector>
#include <iostream>

void PrintDupes( std::vector< unsigned > &v ) {
    for( auto i = 0; i < v.size(); ++i ) {
        auto index = v[ i ] % v.size();
        v[ index ] += v.size();
    }

    for( auto i = 0; i < v.size(); ++i ) {
        if( v[ i ] / v.size() > 1 )
            std::cout << i << " ";
    }
}

int main(int argc, char *argv[] ) {

    std::vector< unsigned > v{ 3, 2, 6, 1, 3, 6, 2, 5 };
    PrintDupes( v );
    return 0;
}