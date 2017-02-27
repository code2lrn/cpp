//
// Created by Ranga on 2/26/17.
//

#include "graph.h"

int main( int argc, char *argv[] ) {

//    Graph g{ 4, { { 1, 2 }, { 1, 3 }, { 2, 4 }, { 3, 4 } } };
    Graph g{ 6, { { 1, 2 }, { 1, 3 }, { 2, 4 }, { 3, 4 }, { 2, 5 }, { 5, 6 } } };
    g.DFS();
    std::cout << std::endl;
    g.BFS();
    return 0;
}