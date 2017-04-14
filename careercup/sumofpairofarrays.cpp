//
// Created by Ranga on 3/14/17.
//

#include <vector>
#include <algorithm>
#include <iostream>

template< typename T >
std::vector< std::pair< T, T > > GetPairsFromArrays( std::vector< T > A, std::vector< T > B, T sum ) {
    std::vector< std::pair< T, T > > output;
    std::sort( A.begin(), A.end() );
    std::sort( B.begin(), B.end() );
    std::for_each( A.begin(), A.end(), [ &B, sum, &output ] ( const T &i ) {
        T numToLookFor = sum - i;
        if( std::binary_search( B.begin(), B.end(), numToLookFor ) ) {
            output.push_back( std::make_pair( i, numToLookFor ) );
        }
    } );

    return output;
};

int main(int argc, char *argv[] ) {

    const std::vector< int > A{ 1,2,4,-6,5,7,9,0 };
    const std::vector< int > B{ 3,6,3,4,0 };
    auto pairs = GetPairsFromArrays< int >( A, B, 4 );
    std::for_each( pairs.begin(), pairs.end(), []( const auto it ){
        std::cout << it.first << ":" << it.second << std::endl;
    } );
    return 0;
}