//
// Created by Ranga on 5/15/16.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>

struct TeamPoints {
    std::string team;
    unsigned    points;
    TeamPoints( const std::string &t, const unsigned &p ) : team( t ), points( p ) { }
    friend std::ostream& operator <<( std::ostream &out, const TeamPoints &t );
};
using Standings = std::vector< TeamPoints >;

std::ostream& operator <<( std::ostream &out, const TeamPoints &t ) {
    out << t.team << "~" << t.points;
    return out;
}

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
    friend std::ostream& operator <<( std::ostream &out, const Fixture &f );
};
using Fixtures = std::vector< Fixture >;

std::ostream& operator <<( std::ostream &out, const Fixture &f ) {
    out << "Game " << f.gameNumber << "~" << f.team1 << "~" << f.team2 << "~" << f.winner;
    return out;
}

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

using Outcome = std::map< std::string, unsigned >;
using PossibleOutcomes = std::vector< std::pair< Outcome, Fixtures > >;

void InitializeOutcome( const Standings &standings, Outcome &outcome ) {
    for( const auto &standing : standings ) {
        outcome.insert( std::make_pair( standing.team, standing.points ) );
    }
}

void DetermineOutcomes( const unsigned gameNumber, const Standings &currentStandings, Fixtures &fixtures, Outcome &outcome, PossibleOutcomes &possibleOutcomes ) {
    if( gameNumber == fixtures.size() ) {
        possibleOutcomes.push_back( std::make_pair( outcome, fixtures ) );
        return;
    }

    if( gameNumber == 0 ) {
        outcome.clear();
        InitializeOutcome( currentStandings, outcome );
    }

    std::string team1 = fixtures[ gameNumber ].team1;
    outcome[ team1 ] += 2;
    fixtures[ gameNumber ].winner = team1;
    DetermineOutcomes( gameNumber + 1, currentStandings, fixtures, outcome, possibleOutcomes );
    outcome[ team1 ] -= 2;

    std::string team2 = fixtures[ gameNumber ].team2;
    outcome[ team2 ] += 2;
    fixtures[ gameNumber ].winner = team2;
    DetermineOutcomes( gameNumber + 1, currentStandings, fixtures, outcome, possibleOutcomes );
    outcome[ team2 ] -= 2;
}

void PrintProspectsForTeam( const PossibleOutcomes &possibleOutcomes, const std::string &yourTeam, std::string outputFileName ) {
    std::ofstream outFile( outputFileName );

    for( const auto &outcome : possibleOutcomes ) {
        const auto teamPoints = outcome.first.find( yourTeam );
        if( teamPoints->second < 16 ) {
            continue;
        }
        Standings finalStandings;
        for( const auto &result : outcome.first ) {
            finalStandings.push_back( TeamPoints( result.first, result.second ) );
        }
        std::sort( finalStandings.begin(), finalStandings.end(), []( auto &x, auto &y ) { return x.points >= y.points; } );
        outFile << "If this happens:\n";
        std::copy( outcome.second.begin(), outcome.second.end(), std::ostream_iterator< Fixture >( outFile, "\n" ) );
        outFile << "Then, this will happen:\n";
        std::copy( finalStandings.begin(), finalStandings.end(), std::ostream_iterator< TeamPoints >( outFile, "\n" ) );
    }

}

int main( int argc, char *argv[] ) {
    std::string teamNameFile;
    std::cout << "File with team names? "; //iplteams.txt
    std::cin >> teamNameFile;
    Standings standings = GetStandings( teamNameFile );
    std::sort( standings.begin(), standings.end(), []( auto &x, auto &y ) { return x.points >= y.points; } );

    std::string fixturesFile;
    std::cout << "File with fixtures? "; //iplremaining.txt
    std::cin >> fixturesFile;
    Fixtures fixtures = GetFixtures( fixturesFile );

    PossibleOutcomes possibleOutcomes;
    Outcome outcome;
    DetermineOutcomes( 0, standings, fixtures, outcome, possibleOutcomes );

    std::string yourTeam = "Royal Challengers Bangalore";
    std::string outputFileName;
    std::cout << "Enter output file name: "; // iplpredictions.txt
    std::cin >> outputFileName;
    PrintProspectsForTeam( possibleOutcomes, yourTeam, outputFileName );

    return 0;
}