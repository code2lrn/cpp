//
// Created by Ranga on 5/11/16.
//

#include <iostream>

unsigned Sum( unsigned x, unsigned y ) {
    while( y != 0 ) {
        int carry = x & y;
        x = x ^ y;
        y = carry << 1;
    }

    return x;
}

int main( int main, char *argv[] ) {
    unsigned x;
    std::cin >> x;
    std::cout << "Power of 2 check for " << x << " returned " << std::boolalpha << ( x && !( x & ( x - 1 ) ) ) << std::endl;

    unsigned y;
    std::cin >> y;
    std::cout << "Sum of " << x << " and " << y << " is " << Sum( x, y ) << std::endl;
    std::cout << "Dif of " << x << " and " << y << " is " << Sum( x, Sum( ~y, 1 ) ) << std::endl;
    return 0;
}