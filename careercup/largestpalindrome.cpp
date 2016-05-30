//
// Created by Ranga on 5/30/16.
//

#include <iostream>

bool IsPalindrome( const std::string &str, int l, int r ) {
    while( l < r && str[ l ] == str[ r ] ) {
        ++l;
        --r;
    }
    return l >= r;
}

std::string LargestPalindrome( const std::string &str, const int l, const int r ) {
    if( r - l >= 2 ) {
        if( IsPalindrome( str, l, r ) ) {
            return str.substr( l, r - l + 1 );
        }
        if( IsPalindrome( str, l + 1, r ) ) {
            return str.substr( l + 1, r - ( l + 1 ) + 1);
        }
        if( IsPalindrome( str, l, r - 1 ) ) {
            return str.substr( l, ( r - 1 ) - l + 1 );
        }
        auto s1 = LargestPalindrome( str, l + 1, r );
        auto s2 = LargestPalindrome( str, l, r - 1 );
        auto s3 = LargestPalindrome( str, l + 1, r - 1 );
        return s1.length() > s2.length() ? ( s1.length() > s3.length() ? s1 : s3 ) : s2;
    }

    if( r - l == 1 || r - l == 2 ) {
        if( str[ l ] == str[ r ] ) {
            return str;
        }
        else {
            return "";
        }
    }

    if( l == r ) {
        return str.substr( l, 1 );
    }
}

int main( int argc, char *argv[] ) {
    std::string str;
    while( std::cin >> str ) {
        std::cout << "The largest palindrome of " << str << " is " << LargestPalindrome( str, 0, str.length() - 1 ) << std::endl;
    }

    return 0;
}
