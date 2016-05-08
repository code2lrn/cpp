//
// Created by Ranga on 5/8/16.
//

#include <vector>
#include <iostream>

bool IsBotonic( const std::vector< int > &array ) {
    bool smaller_leading_num_seen = false;
    for( int i = 1; i < array.size(); ++i ) {
        bool smaller_than_previous = array[ i - 1 ] > array[ i ];
        switch( smaller_than_previous ) {
            case false:
                if( smaller_leading_num_seen )
                    return false;
                break;
            case true:
                if( !smaller_leading_num_seen ) {
                    smaller_leading_num_seen = true;
                    continue;
                }
                break;
        }
    }
    return true;
}

int main( int argc, char *argv[] ) {
    std::cout << "Enter number of elements: ";
    int num;
    std::cin >> num;
    std::cout << "Enter the elements: ";
    int val;
    std::vector< int > array;
    while( num-- && std::cin >> val ) {
        array.push_back( val );
    }

    std::cout << "Bitonic check returned: " << std::boolalpha << IsBotonic( array ) << std::endl;
    return 0;
}