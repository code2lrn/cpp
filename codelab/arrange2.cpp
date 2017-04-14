//
// Created by Ranga on 3/11/17.
//

#include <string>
#include <iostream>
#include <vector>
#include <tuple>

std::vector< std::string > GetAllSubstr( const std::string horses, const int stables, const unsigned maxHorsesPerStable, const unsigned curHorse, const unsigned curStable ) {


    for( size_t i = curHorse; i < horses.size() && i - curHorse < maxHorsesPerStable; ++i ) {
        std::cout << i << " ";
        auto foo = horses.substr( curHorse, horses.size() - 1 - i );
        std::cout << foo << std::endl;
    }
}

int main( int argc, char *argv[] ) {

    std::string horses{ "WWWB" };
    int stables = 2;
    auto maxHorsesPerStable = horses.size() - stables + 1;

    //std::cout << horses << ": " << stables << ", " << maxSubStrLen << std::endl;
    GetAllSubstr( horses, stables, maxHorsesPerStable, 0, 0 );

    return 0;
}