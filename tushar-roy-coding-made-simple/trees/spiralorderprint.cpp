//
// Created by Ranga on 3/13/17.
//

#include <iostream>
#include "bstree.h"

int main( int argc, char *argv[] ) {

    BSTree< int > bst{ 4, 2, 1, 3, 6, 5, 7 };
    unsigned priorElementDepth = 0;
    std::function< void( unsigned, const unsigned& ) > printerWithDepth = [ &priorElementDepth ]( unsigned curDepth, unsigned value ) {
        if( curDepth > priorElementDepth )
            std::cout << std::endl;
        std::cout << value << " ";
        priorElementDepth = curDepth;
    };
    std::cout << std::endl << "LevelOrder: "; bst.LevelOrderTraverse( printerWithDepth );
    priorElementDepth = 0;
    std::cout << std::endl << "SpiralOrder: "; bst.SpiralOrderTraverse( printerWithDepth );

    return 0;
}