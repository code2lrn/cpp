//
// Created by Ranga on 2/24/17.
//

#include <vector>
#include <algorithm>
#include <iostream>

int main(int argc, char *argv[] ) {

//    std::vector< std::pair< int, int > > viewTimes{ { 4, 6 }, { 1, 2 } };
//    std::vector< std::pair< int, int > > viewTimes{ { 2, 5 }, { 1, 4 } };
    std::vector< std::pair< int, int > > viewTimes{ { 1, 4 }, { 6, 8 }, { 2, 4 }, { 7, 9 }, { 10, 15 } };

    std::sort( viewTimes.begin(), viewTimes.end(), []( const auto &a, const auto &b ) { return a.first < b.first || a.second < b.second; } );
    int useTime = 0, activeViewStartTime = std::numeric_limits< int >::min(), activeViewEndTime = std::numeric_limits< int >::min();
    std::for_each( viewTimes.begin(), viewTimes.end(),
                   [ &useTime, &activeViewStartTime, &activeViewEndTime ] ( const auto &times ) {
                        activeViewStartTime = std::max( times.first, activeViewEndTime );
                        if( times.second > activeViewEndTime ) {
                            useTime += times.second - activeViewStartTime;
                            activeViewEndTime = times.second;
                        }
                   } );

    std::cout << "The TV is used for " << useTime << " hours" << std::endl;
    return 0;
}