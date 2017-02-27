//
// Created by Ranga on 2/26/17.
//

#ifndef PROJECT_GRAPH_H
#define PROJECT_GRAPH_H

#include <vector>
#include <list>
#include <iostream>
#include <set>
#include <queue>

class Graph {
public:
    Graph( int numVertices ) : vertices( numVertices + 1 ) { }
    Graph( int numVertices, const std::vector< std::pair< int, int > > &edges ) : vertices( numVertices + 1 ) {
        Insert( edges );
    }

    void Insert( const std::vector< std::pair< int, int > > &edges ) {
        for( auto p : edges ) {
            auto &vertexEdges = vertices[ p.first ];
            vertexEdges.push_back( Edge{ p.second, 1 } );
        }
    }

    void DFS() {
        std::set< int > visited;
        std::queue< int > verticesToVisit;
        for( int i = 1; i < vertices.size(); ++i ) {
            auto it = visited.find( i );
            if( it != visited.end() ) {
                continue;
            }
            visited.insert( it, i );
            DFSImpl( visited, i );
        }
    }

    void BFS() {
        std::set< int > visited;

        for( int i = 1; i < vertices.size(); ++i ) {
            auto it = visited.find( i );
            if( it != visited.end() ) {
                continue;
            }
            std::queue< int > verticesToVisit;
            verticesToVisit.push( i );
            while( verticesToVisit.size() ) {
                auto current = verticesToVisit.front();
                verticesToVisit.pop();
                auto it = visited.find( current );
                if( it != visited.end() ) {
                    continue;
                }
                visited.insert( it, current );
                std::cout << current << " ";
                for( auto edge : vertices[ current ] ) {
                    verticesToVisit.push( edge.edgeTo );
                }
            }
        }
    }

private:
    struct Edge {
        int edgeTo;
        int edgeValue;
        Edge( int to, int val ) : edgeTo( to ), edgeValue( val ) { }
    };
    std::vector< std::list< Edge > > vertices;

    void DFSImpl( std::set< int > &visited, int edgeFrom ) {
        std::cout << edgeFrom << " ";

        for( auto edge : vertices[ edgeFrom ] ) {
            auto it = visited.find( edge.edgeTo );
            if( it != visited.end() ) {
                continue;
            }
            visited.insert( it, edge.edgeTo );
            DFSImpl( visited, edge.edgeTo );
        }
    }
};

#endif //PROJECT_GRAPH_H
