//
// Created by Ranga on 3/12/17.
//

#include <vector>
#include <iostream>

int GetMaxValueDP( const std::vector< int > &coins, std::vector< std::vector< std::vector< int > > > &table, unsigned playerNum, int start, int end ) {
    if( start > end ) {
        return 0;
    }

    if( table[ playerNum ][ start ][ end ] != -1 ) {
        return table[ playerNum ][ start ][ end ];
    }

    if( playerNum == 0 ) {
        auto valueWhenLeftChosen  = coins[ start ] + GetMaxValueDP( coins, table, 1, start + 1, end );
        auto valueWhenRightChosen = coins[ end ] + GetMaxValueDP( coins, table, 1, start, end - 1 );
        return table[ playerNum ][ start ][ end ] = std::max( valueWhenLeftChosen, valueWhenRightChosen );
    }
    else {
        auto valueWhenLeftChosen  = GetMaxValueDP( coins, table, 0, start + 1, end );
        auto valueWhenRightChosen = GetMaxValueDP( coins, table, 0, start, end - 1 );
        return table[ playerNum ][ start ][ end ] = std::min( valueWhenLeftChosen, valueWhenRightChosen );
    }
}

int GetMaxValue( const std::vector< int > &coins ) {

    size_t i = 0, j = coins.size() - 1;
    int playerValue[2] = {0,0}, turn = 0;
    while( i < j ) {
        if( coins[ i ] > coins[ j ] ) {
            playerValue[ turn ] += coins[ i ];
            ++i;
        }
        else if( coins[ i ] < coins[ j ] ) {
            playerValue[ turn ] += coins[ j ];
            --j;
        }
        else {
            if( j - i >= 2 ) {
                auto curValue = coins[ i ], nextLeft = coins[ i + 1 ], nextRight = coins[ j - 1 ];
                if( curValue > nextLeft && curValue > nextRight ) {
                    if( nextLeft >= nextRight ) {
                        playerValue[ turn ] += coins[ i ];
                        ++i;
                    }
                    else {
                        playerValue[ turn ] += coins[ j ];
                        --j;
                    }
                }
                else if( curValue < nextLeft && curValue < nextRight ) {
                    if( nextLeft >= nextRight ) {
                        playerValue[ turn ] += coins[ j ];
                        --j;
                    }
                    else {
                        playerValue[ turn ] += coins[ i ];
                        ++i;
                    }
                }
                else if( nextLeft >= nextRight ) {
                    playerValue[ turn ] += coins[ j ];
                    --j;
                }
                else {
                    playerValue[ turn ] += coins[ i ];
                    ++i;
                }

            }
            else {
                playerValue[ turn ] = coins[ i ];
                ++i;
            }
        }
        turn = turn ? 0 : 1;
    }
    return playerValue[ 0 ];
}

int main( int argc, char *argv[] ) {

    const std::vector< int > &A{ 1, 100, 500, 10 };
    std::vector< std::vector< std::vector< int > > > table( 2, std::vector< std::vector< int > >( A.size(), std::vector< int >( A.size(), -1 ) ) );
    std::cout << GetMaxValue( A ) << std::endl << GetMaxValueDP( A, table, 0, 0, A.size() - 1 ) << std::endl;
    return 0;
}