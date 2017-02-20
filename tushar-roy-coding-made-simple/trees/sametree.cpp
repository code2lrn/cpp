//
// Created by Ranga on 2/18/17.
//

#include <iostream>
#include "bstree.h"

int main( int argc, char *argv[] ) {

    std::vector< unsigned > values1{ 10, 7, 6, 9, 20, 15, 21 };
    std::vector< unsigned > values2{ 10, 7, 6, 9, 20, 15, 21 };

    BSTree< unsigned > b1, b2;
    b1.Load( values1, BSTTraverseStyle::PREORDER );
    b2.Load( values2, BSTTraverseStyle::PREORDER );

    std::cout << "b1.IsSameAs( b2 ) " << std::boolalpha << b1.IsSameAs( b2 ) << std::endl;

    return 0;
}
