//
// Created by Ranga on 2/19/17.
//

#include <string>
#include <iostream>

bool IsInterleaved( const std::string &A, size_t i, size_t iEnd, const std::string &B, size_t j, size_t jEnd, const std::string &C, size_t k, size_t kEnd ) {
    if( i > iEnd & j > jEnd ) {
        return k > kEnd;
    }

    while( i <= iEnd && j <= jEnd && k <= kEnd ) {
        if( A[ i ] == C[ k ] && B[ j ] != C[ k ] ) {
            ++i;
            ++k;
        }
        else if( A[ i ] != C[ k ] && B[ j ] == C[ k ] ) {
            ++j;
            ++k;
        }
        else if( A[ i ] == C[ k ] && B[ j ] == C[ k ] ) {
            return IsInterleaved( A, i + 1, iEnd, B, j, jEnd, C, k + 1, kEnd ) || IsInterleaved( A, i, iEnd, B, j + 1, jEnd, C, k + 1, kEnd );
        }
        else {
            return false;
        }
    }

    while( i <= iEnd && k <= kEnd ) {
        if( A[ i ] == C[ k ] ) {
            ++i;
            ++k;
        }
        else {
            return false;
        }
    }

    while( j <= jEnd && k <= kEnd ) {
        if( B[ j ] == C[ k ] ) {
            ++j;
            ++k;
        }
        else {
            return false;
        }
    }

    return i > iEnd && j > jEnd && k > kEnd;
}

int main(int argc, char *argv[] ) {

    std::string A{ "B" }, B{ "e" }, C{ "Be" };
    std::cout << std::boolalpha << IsInterleaved( A, 0, A.size() - 1, B, 0, B.size() - 1, C, 0, C.size() - 1 ) << std::endl;
    return 0;
}

