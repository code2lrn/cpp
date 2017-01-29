//
// Created by Ranga on 1/27/17.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iterator>

class AdjacencyList {
public:
    AdjacencyList( unsigned n ) : numElements( n ) {
        elements.reserve( numElements + 1 );
        for( unsigned i = 0; i <= numElements; ++i ) {
            elements.push_back( std::set< unsigned >() );
        }
    }

    void AddEdge( unsigned x, unsigned y ) {
        ( elements[ x ] ).insert( y );
        ( elements[ y ] ).insert( x );
    }

    unsigned CalculateNumWaysToDivideKingdom() {
        ChoicesMade choicesMade( numElements + 1, Choice::None );
        unsigned answer = 0, startingNode = 1;
        AssignCityAndValidate( choicesMade, answer, startingNode );
        return answer;
    }

private:
    unsigned numElements;
    std::vector< std::set< unsigned > > elements;
    enum Choice { None, A, B };
    using ChoicesMade = std::vector< Choice >;


    void AssignCityAndValidate( ChoicesMade &choicesMade, unsigned &answer, unsigned node ) {
        choicesMade[ node ] = Choice::A;
        if( ValidChoiceForNodeAndNeighbours( choicesMade, node ) ) {
            if( node < numElements )
                AssignCityAndValidate( choicesMade, answer, node + 1 );
            else {
                ++answer;
            }
        }
        choicesMade[ node ] = Choice::B;
        if( ValidChoiceForNodeAndNeighbours( choicesMade, node ) ) {
            if( node < numElements )
                AssignCityAndValidate( choicesMade, answer, node + 1 );
            else {
                ++answer;
            }
        }
        choicesMade[ node ] = Choice::None;
    }

    bool ValidChoiceForNodeAndNeighbours( ChoicesMade &choicesMade, unsigned currNode ) {
        if( !ValidChoice( choicesMade, currNode ) )
            return false;
        const auto &adjacentNodes = elements[ currNode ];
        return std::count_if( adjacentNodes.begin(), adjacentNodes.end(), [ &choicesMade, this ]( const auto &n ){ return ( choicesMade[ n ] == Choice::None || this->ValidChoice( choicesMade, n ) ); } ) == adjacentNodes.size();
    }

    bool ValidChoice( ChoicesMade &choicesMade, unsigned currNode ) {
        const auto &adjacentNodes = elements[ currNode ];
        return std::find_if( adjacentNodes.begin(), adjacentNodes.end(), [ currNode, &choicesMade ]( const auto &n ){ return choicesMade[ n ] == choicesMade[ currNode ] || choicesMade[ n ] == Choice::None; } ) != adjacentNodes.end();
    }
};

int main( int argc, char *argv[] ) {

    unsigned numCities;
    std::cin >> numCities;
    AdjacencyList kingdomAndRoads( numCities );
    for( unsigned i = 1; i < numCities; ++i ) {
        unsigned routeFrom, routeTo;
        std::cin >> routeFrom >> routeTo;
        kingdomAndRoads.AddEdge( routeFrom, routeTo );
    }

    std::cout << kingdomAndRoads.CalculateNumWaysToDivideKingdom() << "\n";

    return 0;
}
