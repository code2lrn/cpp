//
// Created by Ranga on 1/9/17.
//

#include <iostream>

int main(int argc, char *argv[] ) {

    unsigned numTrips, boatCapacity, numBoats, numPassengers;
    std::cin >> numTrips >> boatCapacity >> numBoats;
    bool tripPossible = true;
    while( numTrips-- && std::cin >> numPassengers ) {
        if( numPassengers > boatCapacity * numBoats ) {
            tripPossible = false;
            break;
        }
    }

    std::cout << ( tripPossible ? "Yes" : "No" ) << std::endl;

    return 0;
}

