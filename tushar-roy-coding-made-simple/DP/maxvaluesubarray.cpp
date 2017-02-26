//
// Created by Ranga on 2/20/17.
//

#include <iostream>
#include <vector>
#include <algorithm>

int MaximumValueOfSubArray( const std::vector< int > &seq ) {
    std::vector< int > costEndingAtNum( seq.size() );
    for( unsigned i = 0; i < seq.size(); ++i ) {
        if( i == 0 ) {
            costEndingAtNum[ i ] = seq[ i ];
        }
        else {
            costEndingAtNum[ i ] = std::max( costEndingAtNum[ i-1 ] + seq[ i ], seq[ i ] );
        }
    }

    auto maxElement = std::max_element( costEndingAtNum.begin(), costEndingAtNum.end() );
    return *maxElement;
}

int main(int argc, char *argv[] ) {

    //std::vector< int > seq{ 3, 4, -1, 0, 6, 2, 3 };
    std::vector< int > seq{ 3, 4, -8, 0, 6, 2, -1 };
    std::cout << MaximumValueOfSubArray( seq ) << std::endl;
    return 0;
}
