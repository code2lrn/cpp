//
// Created by Ranga on 2/20/17.
//

#include <vector>
#include <iostream>
#include <algorithm>

bool RecursiveSumCheck( const std::vector< int > &seq, size_t curIndex, std::vector< bool > &selected, int sum ) {

    if( curIndex < seq.size() ) {
        // without selecting cur
        auto withoutCur = RecursiveSumCheck( seq, curIndex + 1, selected, sum );
        selected[ curIndex ] = true;
        auto withCur    = RecursiveSumCheck( seq, curIndex + 1, selected, sum );
        selected[ curIndex ] = false;
        return withoutCur || withCur;
    }
    else {
        auto pathSum = 0;
        for( size_t i = 0; i < selected.size(); ++i ) {
            pathSum += ( selected[ i ] ? seq[ i ] : 0 );
        }
        return pathSum == sum;
    }
}

bool SubsetWithSumExists( const std::vector< int > &seq, int sum ) {

    std::vector< bool > selected( seq.size(), false );
    return RecursiveSumCheck( seq, 0, selected, sum );
}

int main(int argc, char *argv[] ) {

    std::vector< int > seq{ 2, 3, 7, 8, 10 };
    const int sum = 11;

    std::cout << std::boolalpha << SubsetWithSumExists( seq, sum ) << std::endl;

    return 0;
}