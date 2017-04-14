//
// Created by Ranga on 3/19/17.
//

#ifndef PROJECT_DISJOINTSET_H
#define PROJECT_DISJOINTSET_H

#include <unordered_map>

template< typename T >
class DisjointSet {
public:
    DisjointSet( unsigned n ) { entries.reserve( n ); }
    DisjointSet( const DisjointSet &d  ) = delete;
    DisjointSet& operator=( const DisjointSet &d ) = delete;

    void MakeSet( const T a ) {
        entries.insert( std::make_pair( a, std::make_pair( 1, a ) ) );
    }

    const T Union( const T a, const T b ) {
        auto parentA = Find( a );
        auto parentB = Find( b );
        if( parentA == parentB ) {
            return parentA.second;
        }

        if( parentA.first < parentB.first ) {
            entries[ a ].second = entries[ parentA.second ].second = parentB.second;
            return parentB.second;
        }
        else if( parentA.first > parentB.first ) {
            entries[ b ].second = entries[ parentB.second ].second = parentA.second;
        }
        else {
            entries[ b ].second = entries[ parentB.second ].second = parentA.second;
            ++( entries[ a ].first );
        }
        return parentA.second;
    }

    const T FindUltimateParent( const T a ) {
        return Find( a ).second;
    }

private:
    std::unordered_map< T, std::pair< int, T > > entries;

    std::pair< int, const T > Find( const T a ) {
        auto it = entries.find( a );
        if( it->first == ( it->second ).second ) {
            return it->second;
        }
        ( it->second ).second = Find( ( it->second ).second ).second;
        return ( it->second );
    }
};

#endif //PROJECT_DISJOINTSET_H
