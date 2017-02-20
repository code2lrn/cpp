//
// Created by Ranga on 2/18/17.
//

#include <iostream>
#include <iterator>
#include "bstree.h"

int main( int argc, char *argv[] ) {

    std::vector< unsigned > values{ 10, 5, 8, 6, 9, 30, 25, 28, 60, 78 };

    BSTree< unsigned > bstree;
    bstree.Load( values, BSTTraverseStyle::PREORDER );
    std::cout << "Tree: ";
    std::function< void( const unsigned & ) > cb = []( const unsigned &v ){ std::cout << v << " "; };
    bstree.Traverse( cb, BSTTraverseStyle::INORDER );
    unsigned lowestCommonAncestor = 0;
    std::cout << "\nbstree.LowestCommonAncestor( ..., lowestCommonAncestor ) : " << std::boolalpha << bstree.LowestCommonAncestor( 7, 78, lowestCommonAncestor ) << std::endl;
    std::cout << "Lowest common ancestor is " << lowestCommonAncestor << std::endl;

    return 0;
}

