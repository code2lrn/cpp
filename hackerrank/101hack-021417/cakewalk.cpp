//
// Created by Ranga on 2/14/17.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main(int argc, char *argv[] ) {

    unsigned numCupCakes, calorie;
    std::cin >> numCupCakes;
    std::vector< unsigned > calories;
    while( numCupCakes-- ) {
        std::cin >> calorie;
        calories.push_back( calorie );
    }

    std::sort( calories.begin(), calories.end(), []( auto &a, auto &b ){ return a >= b; } );
    int64_t totalCalories = 0;
    unsigned numCakesPicked = 0;
    std::for_each( calories.begin(), calories.end(),
                   [ &totalCalories, &numCakesPicked ] ( auto &calorieValue ) {
                       totalCalories += calorieValue * std::pow( 2, numCakesPicked++ );
                   } );

    std::cout << totalCalories << std::endl;
    //std::copy( calories.begin(), calories.end(), std::ostream_iterator< unsigned >( std::cout, " " ) );

    return 0;
}
