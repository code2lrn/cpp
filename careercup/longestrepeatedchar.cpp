//
// Created by Ranga on 3/14/17.
//

#include <string>
#include <iostream>

int main( int argc, char *argv[] ) {

    const std::string str{ "abcaaba" };

    auto it = str.begin();
    auto longestCharSoFar = *it, priorChar = *it;
    unsigned longestCharRun = 1, currentCharRun = 1;
    while( ++it != str.end() ) {
        if( priorChar == *it ) {
            ++currentCharRun;
        }
        else {
            priorChar = *it;
            currentCharRun = 1;
        }

        if( currentCharRun > longestCharRun ) {
            if( priorChar != longestCharSoFar ) {
                longestCharSoFar = priorChar;
            }
            longestCharRun = currentCharRun;
        }
    }

    std::cout << "LongestRepeatedChar: " << longestCharSoFar << ", occurred " << longestCharRun << " times" << std::endl;

    return 0;
}