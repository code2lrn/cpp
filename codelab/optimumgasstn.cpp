//
// Created by Ranga on 2/26/17.
//

#include <vector>
#include <iostream>

int main(int argc, char *argv[] ) {

    std::vector< int > gas{ 1, 2, 3, 4, 5, 6, 7 };
    std::vector< int > cost{ 2, 3, 2, 4, 7, 6, 3 };
    std::vector< int > possibleStartingStations;
    for( int i = 0; i < gas.size(); ++ i ) {
        if( gas[ i ] >= cost[ i ] ) {
            possibleStartingStations.push_back( i );
        }
    }

    int bestStartingStation = -1;
    for( auto startingStn : possibleStartingStations ) {
        auto gasRemaining = gas[ startingStn ] - cost[ startingStn ];
        auto nextStn = ( startingStn + 1 ) % gas.size();
        for( ; nextStn != startingStn; nextStn = ( nextStn + 1 ) % gas.size() ) {
            gasRemaining += gas[ nextStn ];
            if( gasRemaining >= cost[ nextStn ] ) {
                gasRemaining -= cost[ nextStn ];
            }
            else {
                break;
            }
        }
        if( nextStn == startingStn ) {
            bestStartingStation = startingStn;
            break;
        }
    }

    std::cout << bestStartingStation << std::endl;

    return 0;
}