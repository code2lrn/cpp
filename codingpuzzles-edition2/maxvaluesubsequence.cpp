//
// Created by Ranga on 5/8/16.
//

#include <iostream>
#include <vector>
#include <limits>
#include <unistd.h>

using Sequence = std::vector< int >;

int SafeSum( int x, int y ) { // A quick hack to ensure the ints did not "wrap" around
    if( x < 0 && y < 0 && x + y > 0 )
        return std::numeric_limits<int>::min();
    if( x > 0 && y > 0 && x + y < 0 )
        return std::numeric_limits<int>::max();
    return( x + y );
}

int maxvalseq( const int l, const int r, const Sequence &seq ) {
    if( l > r )
        return std::numeric_limits< int >::min();
    if( l == r )
        return seq[ l ];

    int mid = ( l + r ) / 2;
    auto runningsum = std::numeric_limits< int >::min();
    auto maxsum = std::numeric_limits< int >::min();
    for( auto i = l; i < r; ++i ) {
        runningsum = std::max( seq[i], SafeSum( seq[i], runningsum ) );
        maxsum = std::max( maxsum, std::max( SafeSum( maxsum, seq[i] ), runningsum ) );
    }
    auto lmax = maxvalseq(l, mid, seq);
    auto rmax = maxvalseq(mid + 1, r, seq);

    return lmax > rmax ? std::max(maxsum, lmax) : std::max(maxsum, rmax);
}

int main( int argc, char *argv[] ) {
    std::cout << "Enter number of elements: ";
    int num;
    std::cin >> num;
    std::cout << "Enter the elements: ";
    int val;
    Sequence seq;
    while( num-- && std::cin >> val ) {
        seq.push_back( val );
    }

    std::cout << "The max value of a sub-sequence is " << maxvalseq( 0, seq.size(), seq ) << std::endl;

    sleep(1);
    return 0;
}

