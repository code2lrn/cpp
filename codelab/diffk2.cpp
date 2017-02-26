//
// Created by Ranga on 2/22/17.
//

#include <vector>
#include <algorithm>
#include <iostream>

int main(int argc, char *argv[] ) {

    std::vector< int > AA{ 59, 65, 70, 36, 47, 52, 1, 32, 65, 3, 20, 35, 32, 4, 52 };
    int B = 58;

    std::sort( AA.begin() , AA.end() );
    bool found = false;
    for( auto it = AA.begin(); it != AA.end(); ++it ) {
        auto reqd = B + *it;
        if( std::binary_search( it + 1, AA.end(), reqd ) ) {
            found = true;
            break;
        }
    }
    std::cout << std::boolalpha << found << std::endl;
    return 0;
}
