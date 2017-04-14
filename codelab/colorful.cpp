//
// Created by Ranga on 3/12/17.
//

#include <sstream>
#include <iostream>
#include <unordered_set>

bool IsColorful( const int A ) {
    std::stringstream ss;
    ss << A;
    auto str = ss.str();
    std::unordered_set< int > knownProducts;
    for( size_t i = 0; i < str.size(); ++i ) {
        auto product = 1;
        for( size_t j = i; j < str.size(); ++j ) {
            product *= str[ j ] - '0';
            auto result = knownProducts.insert( product );
            if( result.second == false ) {
                return false;
            }
        }
    }

    return true;
}

int main( int argc, char *argv[] ) {

    const int A = 1;
    std::cout << std::boolalpha << IsColorful( A ) << std::endl;
    return 0;
}