//
// Created by Ranga on 3/12/17.
//

#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <iterator>

std::vector< std::vector< int > > PartitionIntoParts( std::vector< int > A ) {
    auto fullAverage = std::accumulate( A.begin(), A.end(), 0 ) / A.size();
    std::sort( A.begin(), A.end() );

    return { {} };
}

int main(int argc, char *argv[] ) {

    const std::vector< int > A{ 1, 7, 15, 29, 11, 9 };
    auto parts = PartitionIntoParts( A );
    std::for_each( parts.begin(), parts.end(), [] ( const auto &part ) {
        std::copy( part.begin(), part.end(), std::ostream_iterator< int >( std::cout, " " ) );
        std::cout << std::endl;
    } );
    return 0;
}