//
// Created by Ranga on 3/19/17.
//

#include <iostream>
#include "disjointset.h"

int main( int argc, char *argv[] ) {

    DisjointSet< int > ds( 5 );
    ds.MakeSet( 1 );
    ds.MakeSet( 2 );
    ds.MakeSet( 3 );
    ds.MakeSet( 4 );
    ds.MakeSet( 5 );
    std::cout << ds.FindUltimateParent( 1 ) << " " << ds.FindUltimateParent( 2 ) << std::endl;
    ds.Union( 1, 2 );
    std::cout << ds.FindUltimateParent( 1 ) << " " << ds.FindUltimateParent( 2 ) << std::endl;
    std::cout << ds.FindUltimateParent( 3 ) << " " << ds.FindUltimateParent( 4 ) << std::endl;
    ds.Union( 3, 4 );
    std::cout << ds.FindUltimateParent( 3 ) << " " << ds.FindUltimateParent( 4 ) << std::endl;
    ds.Union( 2, 4 );
    std::cout << ds.FindUltimateParent( 1 ) << " " << ds.FindUltimateParent( 2 ) << " " << ds.FindUltimateParent( 3 ) << " " << ds.FindUltimateParent( 4 ) << " " << ds.FindUltimateParent( 5 ) << std::endl;
    ds.Union( 5, 2 );
    std::cout << ds.FindUltimateParent( 1 ) << " " << ds.FindUltimateParent( 2 ) << " " << ds.FindUltimateParent( 3 ) << " " << ds.FindUltimateParent( 4 ) << " " << ds.FindUltimateParent( 5 ) << std::endl;
    return 0;
}