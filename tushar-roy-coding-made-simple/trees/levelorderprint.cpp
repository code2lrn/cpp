//
// Created by Ranga on 2/17/17.
//

#include <iostream>
#include <functional>
#include <vector>
#include "bstree.h"

int main( int argc, char *argv[] ) {

    BSTree< unsigned > b;

    unsigned numElements;
    std::cin >> numElements;
    unsigned num;
    while( numElements-- ) {
        std::cin >> num;
        b.Insert( num );
    }

    std::function< void( const unsigned & ) > printer = []( const unsigned &v ){ std::cout << v << " "; };
    std::cout << std::endl << "Preorder:  "; b.Traverse( printer, BSTTraverseStyle::PREORDER );
    std::cout << std::endl << "Inorder:   "; b.Traverse( printer, BSTTraverseStyle::INORDER );
    std::cout << std::endl << "Postorder: "; b.Traverse( printer, BSTTraverseStyle::POSTORDER );

    unsigned priorElementDepth = 0;
    std::function< void( unsigned, const unsigned& ) > printerWithDepth = [ &priorElementDepth ]( unsigned curDepth, unsigned value ) {
        if( curDepth > priorElementDepth )
            std::cout << std::endl;
        std::cout << value << " ";
        priorElementDepth = curDepth;
    };
    std::cout << std::endl << "LevelOrder: "; b.LevelOrderTraverse( printerWithDepth );

    return 0;
}
