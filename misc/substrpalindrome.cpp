//
// Created by Ranga on 7/10/16.
//

#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>

bool IsPalindrome( const std::string &str ) {
    if( str.length() < 2 ) {
        return true;
    }
    int i = 0, j = str.size() - 1;
    while( i < j ) {
        if( str[ i ] != str[ j ] ) {
            return false;
        }
        ++i;
        --j;
    }
    return true;
}

std::set< std::string > GenerateSubstringsKludgy( std::string str ) {
    std::set< std::string > output;
    for( auto itr1 = str.begin(); itr1 != str.end(); ++itr1 ) {
        std::string subStr;
        for( auto itr2 = itr1; itr2 != str.end(); ++itr2 ) {
            subStr += *itr2;
            if( IsPalindrome( subStr ) ) {
                output.insert( subStr );
            }
        }
    }

    return output;
}

int palindrome( std::string str ) {
    auto powerSet = GenerateSubstringsKludgy( str );
    return powerSet.size();
}

int main( int argc, char *argv[] ) {

    std::string input;
    std::cin >> input;
    std::cout << palindrome( input ) << std::endl;
    return 0;
}