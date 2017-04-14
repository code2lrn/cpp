//
// Created by Ranga on 3/14/17.
//

#include "yag.h"

int main( int argc, char *argv[] ) {

    Graph g{ 4, { {1,2}, {2,3}, {3,4}, } };
    g.BFS();
    std::cout << std::boolalpha << g.IsBiPartite();
    return 0;
}