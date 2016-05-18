//
// Created by Ranga on 5/18/16.
//

#include <string>
#include <iostream>
#include <sstream>
#include <iterator>

void BinaryAdd( std::string line ) {
    std::stringstream ss( line );
    std::string s1, s2;
    ss >> s1 >> s2;

    auto itr1 = s1.rbegin(), itr2 = s2.rbegin();
    std::stringstream result;
    unsigned carry = 0;
    while( itr1 != s1.rend() || itr2 != s2.rend() ) {
        unsigned digit1 = ( itr1 != s1.rend() ? *itr1 - '0' : 0 );
        unsigned digit2 = ( itr2 != s2.rend() ? *itr2 - '0' : 0 );
        unsigned sum    = ( carry + digit1 + digit2 );
        carry           = sum / 2;
        sum             = sum % 2;
        result << sum;
        if( itr1 != s1.rend() )
            ++itr1;
        if( itr2 != s2.rend() )
            ++itr2;
    }
    if( carry != 0 ) {
        result << carry;
    }

    std::string properResult, resultWithoutLeadingZeroes;
    result >> properResult;
    std::copy( properResult.rbegin(), properResult.rend(), std::back_inserter( resultWithoutLeadingZeroes ) );
    if( resultWithoutLeadingZeroes.find_first_of( '1' ) != std::string::npos ) {
        std::copy( resultWithoutLeadingZeroes.begin() + resultWithoutLeadingZeroes.find_first_of( '1' ),
                   resultWithoutLeadingZeroes.end(),
                   std::ostream_iterator< char >( std::cout, "" ) );
        std::cout << std::endl;
    }
    else
        std::cout << "0" << std::endl;
    return;
}

int main( int argc, char *argv[] ) {

    std::string line;
    while( std::getline( std::cin, line ) ) {
        BinaryAdd( line );
    }
    return 0;
}
