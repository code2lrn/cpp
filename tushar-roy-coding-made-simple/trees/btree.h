//
// Created by Ranga on 2/18/17.
//

#ifndef PROJECT_BTREE_H
#define PROJECT_BTREE_H

#include <queue>
#include <stack>
#include <functional>

template< typename T >
class BTree {
public:
    BTree() : root( nullptr ) { }
    virtual ~BTree() { Destroy( &root ); }

    void LevelOrderTraverse( std::function< void( unsigned, const T& ) > cb ) {
        if( root == nullptr )
            return;

        std::queue< std::pair< Node*, unsigned > > nextItem;
        nextItem.push( std::make_pair( root, 1 ) );
        Node *curNode;
        unsigned curDepth;
        while( !nextItem.empty() ) {
            std::tie( curNode, curDepth ) = nextItem.front();
            nextItem.pop();
            if( curNode->left != nullptr )
                nextItem.push( std::make_pair( curNode->left, curDepth + 1 ) );
            if( curNode->right != nullptr )
                nextItem.push( std::make_pair( curNode->right, curDepth + 1 ) );
            cb( curDepth, curNode->value );
        }
    }

    void SpiralOrderTraverse( std::function< void( unsigned, const T& ) > cb ) {
        if( root == nullptr ) {
            return;
        }

        std::deque< std::pair< Node*, unsigned  > > nextItem;
        nextItem.push_back( std::make_pair( root, 1 ) );
        Node *curItem;
        unsigned priorDepth = 1, curDepth = 1;
        bool getFromFront = true;
        while( !nextItem.empty() ) {
            std::cout << std::endl << priorDepth << ":" << curDepth << std::endl;
            if( priorDepth != curDepth ) {
                getFromFront = !getFromFront;
                priorDepth = curDepth;
            }

            if( getFromFront ) {
                std::tie( curItem, curDepth ) = nextItem.front();
                nextItem.pop_front();
            }
            else {
                std::tie( curItem, curDepth ) = nextItem.back();
                nextItem.pop_back();
            }

            if( curItem->left != nullptr ) {
                nextItem.push_back( std::make_pair( curItem->left, curDepth + 1 ) );
            }
            if( curItem->right != nullptr ) {
                nextItem.push_back( std::make_pair( curItem->right, curDepth + 1 ) );
            }
            cb( curDepth, curItem->value );

        }
    }

    bool IsSameAs( const BTree &other ) {
        if( this == &other )
            return true;
        if( this == nullptr || other.root == nullptr )
            return false;

        return CompareNodeAndChildren( root, other.root );
    }

    bool PathToSum( std::function< void( const T& ) > cb, unsigned expectedSum ) {
        if( root == nullptr )
            return false;

        std::stack< T > pathToSum;
        if( !PathToSumImpl( pathToSum, expectedSum, root ) ) {
            return false;
        }

        while( pathToSum.size() > 0 ) {
            auto n = pathToSum.top();
            pathToSum.pop();
            cb( n );
        }
        return true;
    }

protected:
    struct Node {
        T    value;
        Node *left;
        Node *right;
    };

    Node *root;

    void Destroy( Node **n ) {
        if( *n == nullptr )
            return;
        Destroy( &( ( *n )->left ) );
        Destroy( &( ( *n )->right ) );
        delete *n;
        *n = nullptr;
    }

    Node* Create( const T &v ) {
        Node *n = new Node;
        n->value = v;
        n->left = n->right = nullptr;
        return n;
    }

    bool CompareNodeAndChildren( Node *n1, Node *n2 ) {
        if( n1 == nullptr && n2 == nullptr )
            return true;
        if( n1 == nullptr || n2 == nullptr )
            return false;
        if( n1->value != n2->value )
            return false;
        return CompareNodeAndChildren( n1->left, n2->left ) && CompareNodeAndChildren( n1->right, n2->right );
    }

    bool PathToSumImpl( std::stack< T > &path, unsigned remainingSum, Node *curNode ) {
        if( curNode == nullptr )
            return false;

        remainingSum = ( remainingSum - curNode->value );
        if( remainingSum == 0 && curNode->left == nullptr && curNode->right == nullptr ) {
            path.push( curNode->value );
            return true;
        }

        if( ( curNode->left != nullptr && PathToSumImpl( path, remainingSum, curNode->left ) )
         || ( curNode->right != nullptr && PathToSumImpl( path, remainingSum, curNode->right ) ) ) {

            path.push( curNode->value );
            return true;
        }

        return false;
    }
};


#endif //PROJECT_BTREE_H
