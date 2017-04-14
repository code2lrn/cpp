//
// Created by Ranga on 3/11/17.
//

#include <cmath>
#include <iostream>

int main(int argc, char *argv[] ) {

    unsigned power = 16808;
    unsigned base = 2;
    while( base < power ) {
        double exponent = log10( power ) / log10( base );
        double integralPart;
        if( exponent > 0 && std::modf( exponent, &integralPart ) == 0.0 ) {
            std::cout << "Found " << base << " & " << exponent << std::endl;
            break;
        }
        ++base;
    }

    return 0;
}