//
// Created by Ranga on 1/16/17.
//

#include <iostream>
#include <algorithm>
#include <set>
#include <cstring>

class Graph {
public:
    Graph( unsigned v ) : numVertices( v ) {
        edges = new unsigned*[ numVertices + 1 ];
        for( unsigned i = 0; i <= numVertices; ++i ) {
            edges[ i ] = new unsigned[ numVertices + 1 ];
            memset( edges[i], 0, numVertices + 1 );
        }
    }

    ~Graph() {
        for( unsigned i = 0; i <= numVertices; ++i ) {
            delete [] edges[ i ];
        }
        delete [] edges;
    }

    void AddEdge( unsigned u, unsigned v ) {
        edges[ u ][ v ] = edges[ v ][ u ] = 1;
    }

    void PrintConnectedComponents() {
        std::vector< bool > visited( numVertices, false );

        for( unsigned u = 1; u <= numVertices; ++u ) {
            if( !visited[ u ] ) {
                DFSTraverse( u, visited );
                std::cout << "\n";
            }
        }
    }

    friend std::ostream& operator <<( std::ostream &out, const Graph &g );

private:
    unsigned numVertices;
    unsigned **edges;

    void DFSTraverse( unsigned u, std::vector< bool > &visited ) {
        visited[ u ] = true;
        std::cout << u << " ";
        for( unsigned v = 1; v <= numVertices; ++v ) {
            if( edges[ u ][ v ] && !visited[ v ] ) {
                DFSTraverse( v, visited );
            }
        }
    }
};

std::ostream& operator <<( std::ostream &out, const Graph &g ) {
    for(unsigned i = 1; i <= g.numVertices; ++i ) {
        for( unsigned j = 1; j <= g.numVertices; ++j ) {
            out << g.edges[ i ][ j ] << " ";
        }
        out << "\n";
    }
    return out;
}

int main(int argc, char *argv[] ) {

    unsigned numQueries;
    std::cin >> numQueries;
    while( numQueries-- ) {
        unsigned numStudents, numFriendships, total = 0;
        std::cin >> numStudents >> numFriendships;
        Graph g{ numStudents };
        while( numFriendships-- ) {
            unsigned u, v;
            std::cin >> u >> v;
            g.AddEdge( u, v );
        }
        std::cout << g << "Connected Components:\n";
        g.PrintConnectedComponents();
    }
    return 0;
}