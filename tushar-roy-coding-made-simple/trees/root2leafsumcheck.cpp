//
// Created by Ranga on 2/18/17.
//

#include <iostream>
#include <iterator>
#include "bstree.h"

int main( int argc, char *argv[] ) {

    std::vector< unsigned > values{ 10, 7, 6, 9, 20, 15, 21 };

    BSTree< unsigned > btree;
    btree.Load( values, BSTTraverseStyle::PREORDER );

    std::vector< unsigned > pathToSum;
    std::function< void( const unsigned & ) > cbPath = [ &pathToSum ]( const unsigned &v ){ pathToSum.push_back( v ); };
    unsigned expectedSum = 26;
    std::cout << "btree.PathToSum( cbPath ): " << std::boolalpha << btree.PathToSum( cbPath, expectedSum ) << std::endl;
    std::copy( pathToSum.begin(), pathToSum.end(), std::ostream_iterator< unsigned >( std::cout, " " ) );
    return 0;
}

