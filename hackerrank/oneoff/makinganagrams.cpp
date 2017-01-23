//
// Created by Ranga on 1/22/17.
//

#include <algorithm>
#include <iostream>
#include <string>

int main() {

    std::string str1, str2;
    std::cin >> str1 >> str2;
    const unsigned S1 = str1.size(), S2 = str2.size();
    std::sort( str1.begin(), str1.end() );
    std::sort( str2.begin(), str2.end() );
    unsigned i = 0, j = 0;
    unsigned numDeletions = 0;
    while( i < S1 && j < S2 ) {
        if( str1[ i ] != str2[ j ] ) {
            str1[ i ] < str2[ j ] ? ++i : ++j;
            ++numDeletions;
        }
        else {
            ++i; ++j;
        }
    }
    numDeletions += ( S1 - i ) + ( S2 - j );
    //std::cout << "Num deletions for " << str1 << " and " << str2 << " is " << numDeletions << std::endl;
    std::cout << numDeletions << std::endl;
    return 0;
}