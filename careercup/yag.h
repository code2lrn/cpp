//
// Created by Ranga on 3/14/17.
//

#ifndef YAG_H
#define YAG_H

#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <queue>

class Graph {
public:
    Graph( unsigned n, const std::initializer_list< std::pair< unsigned, unsigned > > &edges ) : numVertices( n ), vertices( n + 1 ) {
        std::for_each( edges.begin(), edges.end(), [ this ]( const auto &edge ){ this->AddEdge( edge.first, edge.second, 1 ); } );
        for( unsigned i = 1; i <= numVertices; ++i ) {
            std::cout << i << "=>";
            if( !( vertices[ i ].empty() ) ) {
                std::for_each( vertices[ i ].begin(), vertices[ i ].end(), [ &i ]( const Edge &edge ) {
                    std::cout << edge.edgeTo << ",";
                } );
            }
            std::cout << std::endl;
        }
    }

/*
    Graph( unsigned n, const std::initializer_list< std::tuple< unsigned, unsigned, int > > &edges ) : numVertices( n ), vertices( n + 1 ) {
        std::for_each( edges.begin(), edges.end(), [ this ]( const auto &edge ){ this->AddEdge( std::get<0>( edge ), std::get<1>( edge ), std::get<2>( edge ) ); } );
    }
*/

    void DFS() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    void BFS() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;

        std::unordered_set< unsigned > visited;
        for( unsigned i = 1; i <= numVertices; ++i ) {
            if( visited.find( i ) != visited.end() ) {
                continue;
            }

            std::queue< unsigned > verticesToVisit;
            verticesToVisit.push( i );
            while( !verticesToVisit.empty() ) {
                auto currentVertex = verticesToVisit.front();
                verticesToVisit.pop();
                auto found = visited.find( currentVertex );
                if( found != visited.end() ) {
                    continue;
                }
                visited.insert( found, currentVertex );

                std::cout << "Visited " << currentVertex << std::endl;
                for( auto adjacentVertex : vertices[ currentVertex ] ) {
                    verticesToVisit.push( adjacentVertex.edgeTo );
                }
            }
        }
    }

    bool IsBiPartite() {
        enum ColorState { Uncolored, Color_1, Color_2 };
        std::vector< ColorState > vertexColor( numVertices, ColorState::Uncolored );
        auto OtherColor = [] ( const ColorState cs ) {
            switch (cs) {
                case ColorState::Color_1:
                    return ColorState::Color_2;
                case ColorState::Color_2:
                    return ColorState::Color_1;
                default:
                    return ColorState::Uncolored;
            }
        };
        for( unsigned i = 1; i <= numVertices; ++i ) {
            if( vertexColor[ i ] == Uncolored ) {
                vertexColor[i] = ColorState::Color_1;
            }
            for (auto adjacentVertex : vertices[i]) {
                if( vertexColor[ adjacentVertex.edgeTo ] == ColorState::Uncolored ) {
                    vertexColor[ adjacentVertex.edgeTo ] = OtherColor( vertexColor[i] );
                }

                if ( vertexColor[ adjacentVertex.edgeTo ] != OtherColor( vertexColor[i] ) ) {
                    return false;
                }
            }
        }

        return true;
    }

private:
    struct Edge {
        unsigned edgeTo;
        int      edgeValue;
        Edge( unsigned to, int value ) : edgeTo( to ), edgeValue( value ) {}
        friend bool operator ==( const Edge &e1, const Edge &e2 ) { return e1.edgeTo == e2.edgeTo; }
    };

    const unsigned numVertices;
    std::vector< std::list< Edge > > vertices;

    void AddEdge( unsigned from, unsigned to, int value ) {
        auto &list = vertices[ from ];
        Edge edge{ to, value };
        auto tail = std::find( list.begin(), list.end(), edge );
        if( tail == list.end() ) {
            list.insert( tail, edge );
        }
        else {
            *tail = edge;
        }
    }
};

#endif //PROJECT_YAG_H
