//
// Created by Ranga on 1/27/17.
//

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

inline unsigned CharWeight(char x) { return x - 'a' + 1; }

int main(int argc, char *argv[] ) {

    std::string str;
    std::cin >> str;
    std::vector< unsigned > weights;
    for( size_t i = 0; i < str.size(); ) {
        auto seqWeight = CharWeight(str[i]);
        weights.push_back( seqWeight );
        auto j = i + 1;
        for( ;j < str.size() && str[ i ] == str[ j ]; ++j ) {
            seqWeight += CharWeight(str[i]);
            weights.push_back( seqWeight );
        }
        i = j;
    }
    //std::copy( weights.begin(), weights.end(), std::ostream_iterator< unsigned >( std::cout, "\n" ) );
    std::sort( weights.begin(), weights.end() );

    unsigned numQueries;
    std::cin >> numQueries;
    while( numQueries-- ) {
        unsigned weight;
        std::cin >> weight;
        if( std::binary_search( weights.begin(), weights.end(), weight ) ) {
            std::cout << "Yes\n";
        }
        else {
            std::cout << "No\n";
        }
    }

    return 0;
}