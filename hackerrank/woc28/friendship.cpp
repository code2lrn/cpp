//
// Created by Ranga on 1/15/17.
//

#include <iostream>
#include <algorithm>
#include <set>

int main(int argc, char *argv[] ) {

    unsigned numQueries;
    std::cin >> numQueries;
    while( numQueries-- ) {
        unsigned numStudents, numFriendships, total = 0;
        std::vector< std::set< unsigned > > relationships;
        std::cin >> numStudents >> numFriendships;
        while( numFriendships-- ) {
            unsigned a, b;
            std::cin >> a >> b;
            auto aFriends = std::find_if( relationships.begin(), relationships.end(), [ a ]( auto &s ) { return s.find( a ) != s.end(); } );
            auto bFriends = std::find_if( relationships.begin(), relationships.end(), [ b ]( auto &s ) { return s.find( b ) != s.end(); } );
            if( aFriends == relationships.end() && bFriends == relationships.end() ) {
                relationships.push_back( std::set< unsigned >( { a, b } ) );
                //std::cout << "Neither existed; added\n";
            }
            else if( aFriends != relationships.end() && bFriends == relationships.end() ) {
                (*aFriends).insert( b );
                //std::cout << "A existed; added B\n";
            }
            else if( aFriends == relationships.end() && bFriends != relationships.end() ) {
                (*bFriends).insert( a );
                //std::cout << "B existed; added A\n";
            }
            else if( aFriends == bFriends ) {
                //std::cout << "Both existed; nothing to add\n";
            }
            else if( aFriends != bFriends ) {
                //std::cout << "Unhandled scenario\n";
                if( (*aFriends).size() > (*bFriends).size() ) {
                    (*aFriends).insert( (*bFriends).begin(), (*bFriends).end() );
                    relationships.erase( bFriends );
                }
                else {
                    (*bFriends).insert( (*aFriends).begin(), (*aFriends).end() );
                    relationships.erase( aFriends );
                }
                //abort();
            }
            int value = 0;
            std::for_each( relationships.begin(), relationships.end(), [ &value ]( auto &s ) { value += ( s.size() * ( s.size() - 1 ) ); } );
            //std::cout << "Value at this stage is " << value << std::endl;
            total += value;
        }
        //std::cout << "Total for this query is " << total << std::endl;
        std::cout << total << std::endl;
    }
    return 0;
}