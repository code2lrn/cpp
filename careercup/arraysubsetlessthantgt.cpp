//
// Created by Ranga on 3/14/17.
//

#include <vector>
#include <algorithm>
#include <iostream>

unsigned fact( unsigned  a ) {
    unsigned i = 1;
    if( a == 0 ) {
        return 0;
    }

    while( a > 0 ) {
        i *= a--;
    }
    return i;
}

int NumsubSetsLessThan( std::vector< int > A, int sum ) {
    std::sort( A.begin(), A.end() );
    auto it = A.begin();
    unsigned totalSubsets = 0;
    while( it != A.end() ) {
        if( *it * 2 > sum ) {
            break;
        }
        auto otherNum = sum - *it;
        if( std::binary_search( it + 1, A.end(), otherNum ) ) {
            auto ub = std::upper_bound( it + 1, A.end(), otherNum );
            auto minSet = 1 + std::distance( ub, A.end() ); // Initial Element + numbers larger than otherNum
            auto maxSet = A.size() - minSet; // elements not in minSet
            std::cout << "The pairs of numbers are: " << *it << " and " << otherNum << ". min/max set is " << minSet << "," << maxSet << ". Total combinations: " << fact( minSet ) * fact( maxSet ) << std::endl;
            totalSubsets += fact( minSet ) * fact( maxSet );
        }
        ++it;
    }

    return totalSubsets;
}

int main(int argc, char *argv[] ) {

    const std::vector< int > A{ 4,3,1,2,6,5,-5,7 };
    const int sum = 1;
    std::cout << "The total number of subsets are " << NumsubSetsLessThan( A, sum ) << std::endl;

    return 0;
}