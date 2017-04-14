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
#include <unordered_map>
#include <limits>

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

    std::pair< int, std::vector< int > > DikjstraShortestPath( int from, int to ) {
        std::unordered_map< int, int > predecessor;
        std::unordered_map< int, int > distancebyVertex;
        auto maxVal = std::numeric_limits< int >::max();
        for( size_t i = 1; i <= vertices.size(); ++i ) {
            distancebyVertex.insert( std::make_pair( i, (unsigned)from == i ? 0 : maxVal ) );
        }
        predecessor.insert( std::make_pair( from, 0 ) );

        auto Comparator = []( const Edge &e1, const Edge &e2 ){ return e1.edgeValue > e2.edgeValue; };
        std::priority_queue< Edge, std::vector< Edge >, decltype( Comparator ) > heaptoGetMinValue( Comparator );
        heaptoGetMinValue.push( Edge( from, 0 ) );
        while( !heaptoGetMinValue.empty() ) {
            auto vertex = heaptoGetMinValue.top();
            heaptoGetMinValue.pop();
            for( auto adjacentVertex : vertices[ vertex.edgeTo ] ) {
                if( distancebyVertex[ adjacentVertex.edgeTo ] == maxVal
                    || distancebyVertex[ adjacentVertex.edgeTo ] > distancebyVertex[ vertex.edgeTo ] + adjacentVertex.edgeValue ) {
                    distancebyVertex[ adjacentVertex.edgeTo ] = distancebyVertex[ vertex.edgeTo ] + adjacentVertex.edgeValue;
                    heaptoGetMinValue.push( Edge( adjacentVertex.edgeTo, distancebyVertex[ adjacentVertex.edgeTo ] ) );
                    predecessor[ adjacentVertex.edgeTo ] = vertex.edgeTo;
                }
            }
        }
        std::vector< int > path;
        auto it = predecessor.find( to );
        while( it != predecessor.end() && it->second != 0 ) {
            path.push_back( it->second );
            it = predecessor.find( it->second );
        }
        return std::make_pair( distancebyVertex[ to ], path );
    }

    std::pair< int, std::vector< int > > BellmanFordShortestPath( int from, int to ) {
        std::unordered_map< int, std::pair< int, int > > distanceAndParentByDestn;
        auto intMax = std::numeric_limits< int >::max() - 1000000;
        for( size_t i = 1; i <= vertices.size(); ++i ) {
            distanceAndParentByDestn.insert( std::make_pair( i, std::make_pair( i == from ? 0 : intMax, -1 ) ) );
        }

        for( int i = 1; i < vertices.size(); ++i ) {
            for( int u = 1; u < vertices.size(); ++u ) {
                auto uCost = distanceAndParentByDestn.find( u )->second.first;
                for( auto edge : vertices[ u ] ) {
                    auto v = edge.edgeTo;
                    auto c = edge.edgeValue;
                    auto it = distanceAndParentByDestn.find( v );
                    if( it->second.first > uCost + c ) {
                        it->second.first  = uCost + c;
                        it->second.second = u;
                    }
                }
            }
        }
        std::vector< int > path;
        auto it = distanceAndParentByDestn.find( to );
        auto distance = it->second.first;
        while( it->second.second != -1 && it != distanceAndParentByDestn.end() ) {
            path.push_back( it->second.second );
            it = distanceAndParentByDestn.find( it->second.second );
        }
        return std::make_pair( distance, path );
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
