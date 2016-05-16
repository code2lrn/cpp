//
// Created by Ranga on 5/15/16.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

struct TeamPoints {
    std::string team;
    unsigned    points;
    TeamPoints( const std::string &t, const unsigned &p ) : team( t ), points( p ) { }
};
using Standings = std::vector< TeamPoints >;

Standings GetStandings( const std::string &teamNameFile ) {
    std::ifstream ifTeams{ teamNameFile, std::ifstream::in };
    std::string line;
    Standings standings;
    while( std::getline( ifTeams, line ) ) {
        std::string team;
        unsigned points;
        std::stringstream ss( line );
        std::getline( ss, team, '~' );
        ss >> points;
        standings.push_back( TeamPoints( team, points ) );
    }
    return standings;
}

struct Fixture {
    unsigned gameNumber;
    std::string team1;
    std::string team2;
    std::string winner;
    Fixture( const unsigned g, const std::string &t1, const std::string &t2 ) : gameNumber( g ), team1( t1 ), team2( t2 ) { }
};
using Fixtures = std::vector< Fixture >;

Fixtures GetFixtures( const std::string &fixturesFile ) {
    std::ifstream ifTeams{ fixturesFile, std::ifstream::in };
    std::string line;
    Fixtures fixtures;
    while( std::getline( ifTeams, line ) ) {
        std::string team1, team2, gameNumStr;
        std::stringstream ss( line );
        std::getline( ss, gameNumStr, '~' );
        std::getline( ss, team1, '~' );
        std::getline( ss, team2, '~' );
        fixtures.push_back( Fixture( atoi( gameNumStr.c_str() ), team1, team2 ) );
    }
    return fixtures;
}

int main( int argc, char *argv[] ) {
    std::string teamNameFile;
    std::cout << "File with team names? ";
    std::cin >> teamNameFile;
    Standings standings = GetStandings( teamNameFile );
    std::sort( standings.begin(), standings.end(), []( auto &x, auto &y ) { return x.points >= y.points; } );

    std::string fixturesFile;
    std::cout << "File with fixtures? ";
    std::cin >> fixturesFile;
    Fixtures fixtures = GetFixtures( fixturesFile );

    return 0;
}