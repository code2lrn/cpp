//
// Created by Ranga on 5/21/17.
//

#include <string>
#include <vector>

void InterleavedStrings( const std::string &x, int xi, const std::string &y, int yi, std::string &z, int zi, std::vector< std::string > &combos ) {
    if( xi >= x.size() && yi >= y.size() ) {
        combos.push_back( z );
        return;
    }

    if( xi < x.size() ) {
        z[ zi ] = x[ xi ];
        InterleavedStrings( x, xi + 1, y, yi, z, zi + 1, combos );
    }

    if( yi < y.size() ) {
        z[ zi ] = y[ yi ];
        InterleavedStrings( x, xi, y, yi + 1, z, zi + 1, combos );
    }
}

int main( int argc, char *argv[] ) {

    std::string x = "ab", y = "cd", z;
    z = x + y;
    std::vector< std::string > combos;
    InterleavedStrings( x, 0, y, 0, z, 0, combos );
    return 0;
}