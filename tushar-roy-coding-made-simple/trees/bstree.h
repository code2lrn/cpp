//
// Created by Ranga on 2/17/17.
//

#ifndef PROJECT_BSTREE_H
#define PROJECT_BSTREE_H

#include "btree.h"
#include <stack>
#include <algorithm>

enum BSTTraverseStyle{ PREORDER, INORDER, POSTORDER };

template< typename T >
class BSTree : public BTree< T > {
public:
    BSTree() { }
    virtual ~BSTree() { }

    void Insert( const T &value ) {
        Node *n = BTree< T >::Create( value );
        IterativeInsert( n );
    }

    void Traverse( std::function< void( const T& ) > cb ) {
        RecursiveTraverse( cb, this->root, BSTTraverseStyle::PREORDER );
    }

    void Traverse( std::function< void( const T& ) > cb, BSTTraverseStyle t ) {
        RecursiveTraverse( cb, this->root, t );
    }

    void Load( const std::vector< T > &values, BSTTraverseStyle t ) {
        if( t == BSTTraverseStyle::PREORDER )
            LoadFromPreOrder( values );
        else if( t == BSTTraverseStyle::POSTORDER )
            LoadFromPostOrder( values );
    }

    bool LowestCommonAncestor( T v1, T v2, T &ancestor ) {
        if( v1 > v2 ) {
            std::swap( v1, v2 );
        }

        return LowestCommonAncestorImpl( this->root, v1, v2, ancestor );
    }

private:
    using typename BTree< T >::Node;

    void IterativeInsert( Node *n ) {
        if( this->root == nullptr ) {
            this->root = n;
            return;
        }

        Node *current = this->root;
        while( ( current->value >= n->value && current->left != nullptr )
               || ( current->value < n->value && current->right != nullptr ) )
        {
            current = ( current->value >= n->value ) ? current->left : current->right;
        }

        if( current->value >= n->value )
            current->left = n;
        if( current->value < n->value )
            current->right = n;
    }

    void RecursiveTraverse( std::function< void( const T& ) > cb, Node *n, BSTTraverseStyle t ) {
        if( n == nullptr )
            return;

        switch( t ) {
            case BSTTraverseStyle::PREORDER :
                cb( n->value );
                RecursiveTraverse( cb, n->left, t );
                RecursiveTraverse( cb, n->right, t );
                break;
            case BSTTraverseStyle::INORDER :
                RecursiveTraverse( cb, n->left, t );
                cb( n->value );
                RecursiveTraverse( cb, n->right, t );
                break;
            case BSTTraverseStyle::POSTORDER :
                RecursiveTraverse( cb, n->left, t );
                RecursiveTraverse( cb, n->right, t );
                cb( n->value );
                break;
        }
    }

    void LoadFromPreOrder( const std::vector< T > &values ) {
        if( this->root != nullptr ) {
            BTree< T >::Destroy( &( this->root ) );
        }

        if( values.size() == 0 ) {
            return;
        }

        this->root = BTree< T >::Create( values[ 0 ] );
        std::stack< Node* > priorNodes;
        priorNodes.push( this->root );
        std::for_each( values.begin() + 1, values.end(), [ &priorNodes, this ]( const T &v ) {
            auto curNode = BTree< T >::Create( v );
            auto priorNode = priorNodes.top();
            if( curNode->value <= priorNode->value ) {
                priorNode->left = curNode;
                priorNodes.push( curNode );
            }
            else if( curNode->value > priorNode->value ) {
                priorNodes.pop();
                if( priorNodes.size() > 0 ) {
                    auto priorNodeParent = priorNodes.top();
                    while( curNode->value > priorNodeParent->value ) {
                        priorNode = priorNodeParent;
                        priorNodes.pop();
                        if( priorNodes.size() == 0 )
                            break;
                        priorNodeParent = priorNodes.top();
                    }
                }
                priorNode->right = curNode;
                priorNodes.push( curNode );
            }
        } );
    }

    void LoadFromPostOrder( const std::vector< T > &values ) {
        if( this->root != nullptr ) {
            BTree< T >::Destroy( &( this->root ) );
        }

        if( values.size() == 0 ) {
            return;
        }

        this->root = BTree< T >::Create( values[ values.size() - 1 ] );
        std::stack< Node* > priorNodes;
        priorNodes.push( this->root );
        std::for_each( values.rbegin() + 1, values.rend(), [ &priorNodes, this ]( const T &v ) {
            auto curNode = BTree< T >::Create( v );
            auto priorNode = priorNodes.top();
            if( curNode->value > priorNode->value ) {
                priorNode->right = curNode;
                priorNodes.push( curNode );
            }
            else if( curNode->value <= priorNode->value ) {
                priorNodes.pop();
                if( priorNodes.size() > 0 ) {
                    auto priorNodeParent = priorNodes.top();
                    while( curNode->value <= priorNodeParent->value ) {
                        priorNode = priorNodeParent;
                        priorNodes.pop();
                        if( priorNodes.size() == 0 )
                            break;
                        priorNodeParent = priorNodes.top();
                    }
                }
                priorNode->left = curNode;
                priorNodes.push( curNode );
            }
        } );
    }

    bool LowestCommonAncestorImpl( Node *n, const T &v1, const T &v2, T &ancestor ) {
        if( n == nullptr )
            return false;

        if( v1 < n->value && v2 < n->value )
            return LowestCommonAncestorImpl( n->left, v1, v2, ancestor );
        if( v1 > n->value && v2 > n->value )
            return LowestCommonAncestorImpl( n->right, v1, v2, ancestor );

        if( NodeExists( n, v1 ) && NodeExists( n, v2 ) ) {
            ancestor = n->value;
            return true;
        }

        return false;
    }

    bool NodeExists( Node *n, const T &value ) {
        if( n == nullptr )
            return false;

        return ( n->value == value ) ? true : ( n->value > value ? NodeExists( n->left, value ) : NodeExists( n->right, value ) );
    }
};

#endif //PROJECT_BTREE_H
