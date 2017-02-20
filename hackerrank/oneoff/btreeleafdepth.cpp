//
// Created by Shiva on 2/12/17.
//

#include <iostream>
#include <sstream>
#include <map>
#include <limits>
#include <algorithm>

struct Status {
    unsigned depth;
    bool     hasChild;
    Status( unsigned d, bool c ) : depth( d ), hasChild( c ) { }
};

int main(int argc, char *argv[] ) {

    std::string inputLine;
    unsigned currentChildDepth = 1;
    std::map< std::string, Status > allChildren;
    while( std::cin >> inputLine ) {
        std::stringstream ss( inputLine );
        std::string parent, leftChild, rightChild;
        std::getline( ss, parent, ',' );
        std::getline( ss, leftChild, ',' );
        std::getline( ss, rightChild, ',' );

        if( allChildren.size() == 0 ) {
            Status s{ 0, leftChild.size() > 0 || rightChild.size() > 0 };
            allChildren.insert( std::make_pair( parent, s ) );
        }
        else {
            auto found = allChildren.find( parent );
            if( found != allChildren.end() ) {
                found->second.hasChild = true;
            }
        }

        // Add
        Status childStatus{ currentChildDepth, false };
        if( leftChild.size() > 0 )
            allChildren.insert( std::make_pair( leftChild, childStatus ) );
        if( rightChild.size() > 0 )
            allChildren.insert( std::make_pair( rightChild, childStatus ) );

        ++currentChildDepth;
    }

    std::string shallowestLeafNode;
    unsigned shallowestLeafNodeDepth = std::numeric_limits< unsigned >::max();
    for( auto it = allChildren.begin(); it != allChildren.end(); ++it ) {
        if (it->second.hasChild == false && it->second.depth < shallowestLeafNodeDepth) {
            shallowestLeafNodeDepth = it->second.depth;
            shallowestLeafNode = it->first;
        }
    }

    if( shallowestLeafNode.size() > 0 )
        std::cout << shallowestLeafNodeDepth << std::endl;
    std::cout.flush();

    return 0;
}
