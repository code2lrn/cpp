//
// Created by Ranga on 6/27/16.
//

#include <tuple>
#include <iostream>
#include <cmath>

std::tuple< bool, int, int > GetAsPairOfSquares( int n ) {
    auto num1 = 1;
    while( 2 * std::pow( num1, 2 ) < n ) {
        ++num1;
    }

    auto num2 = num1;
    while( num2 > 0 && std::pow( num1, 2 ) + std::pow( num2, 2 ) > n ) {
        --num2;
    }

    if( num2 > 0 && std::pow( num1, 2 ) + std::pow( num2, 2 ) == n ) {
        return std::make_tuple( true, num1, num2 );
    }

    return std::make_tuple( false, 0, 0 );
}

int main() {
    auto n = 0;
    bool foundPair;
    int num1, num2;
    while( std::cin >> n ) {
        std::tie( foundPair, num1, num2 ) = GetAsPairOfSquares( n );
        if( foundPair ) {
            std::cout << n << " can expresses as square of " << num1 << " & " << num2 << std::endl;
        }
        else {
            std::cout << n << " cannot be expressed as sum of 2 squares\n";
        }
    }

    return 0;
}