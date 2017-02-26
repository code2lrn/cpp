//
// Created by Ranga on 2/20/17.
//

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

class StringPerm{
public:
    static void Permutate( const std::string &str ) {
        std::string permutation(str);

        // O(n*n!) space & time
/*
        char used[ 26 ]= {0};
        PermImplNaive( permutation, used, 0 );
*/

        // Iterative Impl
        PermImplIterative( permutation );
    }

private:

    static void PermImplNaive( std::string &permutation, char used[], size_t index ) {
        if( index == permutation.size() ) {
            std::cout << permutation << std::endl;
            return;
        }

        for( size_t i = index; i < permutation.size(); ++i ) {
            if( used[ permutation[ i ] - 'a' ] )
                continue;
            used[ permutation[ i ] - 'a' ] = 1;
            std::swap( permutation[ index ], permutation[ i ] );
            PermImplNaive( permutation, used, index + 1 );
            std::swap( permutation[ index ], permutation[ i ] );
            used[ permutation[ i ] - 'a' ] = 0;
        }
    }

    static void PermImplIterative( std::string &permutation ) {
        std::sort( permutation.begin(), permutation.end() );

        while( true ) {

            static unsigned numPermutation;
            std::cout << ++numPermutation << ". " << permutation << std::endl;
            // Rightmost char lesser than any char to the right
            int i;
            for( i = permutation.size() - 2; i >= 0; --i ) {
                if( permutation[ i ] < permutation[ i + 1 ] ) {
                    break;
                }
            }
            if( i < 0 ) {
                break;
            }
            // Find smallest char bigger than permutation[ i ]
            unsigned leastBiggerIndex = i + 1;
            for( unsigned  j = i + 2; j < permutation.size(); ++j ) {
                if( permutation[ i ] < permutation[ j ] && permutation[ j ] < permutation[ leastBiggerIndex ] ) {
                    leastBiggerIndex = j;
                }
            }
            std::swap( permutation[ i ], permutation[ leastBiggerIndex ] );
            std::sort( permutation.begin() + i + 1, permutation.end() );
       }
    }
};

int main(int argc, char *argv[] ) {
    std::string str{ "aba" };
    StringPerm::Permutate( str );
    return 0;
}