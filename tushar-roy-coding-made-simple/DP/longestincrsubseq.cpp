//
// Created by Ranga on 2/20/17.
//

#include <vector>
#include <iostream>
#include <algorithm>

unsigned LongestIncreasingSubsequence( const std::vector< int > seq ) {

    std::vector< int > seqCount( seq.size(), 1 );
    for( size_t j = 1; j < seq.size(); ++j ) {
        for( size_t i = 0; i < j; ++i ) {
            if( seq[ i ] < seq[ j ] ) {
                seqCount[ j ] = std::max( 1 + seqCount[ i ], seqCount[ j ] );
            }
        }
    }

    auto maxElement = std::max_element( seqCount.begin(), seqCount.end() );
    return maxElement != seqCount.end() ? *maxElement : 1;
}

int main(int argc, char *argv[] ) {

    std::vector< int > seq{ 2, 5, 1, 8, 3 }; //{ 3, 4, -1, 0, 6, 2, 3 };

    std::cout << LongestIncreasingSubsequence( seq ) << std::endl;

    return 0;
}