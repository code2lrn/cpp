//
// Created by Ranga on 5/8/16.
//

#include <iostream>
#include <vector>
#include <unistd.h>
#include <stack>

struct Node {
    int value;
    Node *left;
    Node *right;
};

Node *GetNodeWithValue( int value ) {
    Node *n = new Node;
    n->value = value;
    n->left = n->right = nullptr;
    return n;
}

Node *CreateTreeFromInput( int &index, std::vector< int > &input ) {
    if( index >= input.size() || input[ index ] == -999 )
        return nullptr;
    Node *n = GetNodeWithValue( input[ index ] );
    n->left = CreateTreeFromInput( ++index, input );
    n->right = CreateTreeFromInput( ++index, input );
    return n;
}

void PreOrderTraversal( const Node *node ) {
    if( node == nullptr )
        return;
    std::cout << node->value << ", ";
    PreOrderTraversal( node->left );
    PreOrderTraversal( node->right );
}

void InOrderTraversal( const Node *node ) {
    if( node == nullptr )
        return;
    InOrderTraversal( node->left );
    std::cout << node->value << ", ";
    InOrderTraversal( node->right );
}

bool IsValidBinaryTree( const Node *node ) {
    if( node == nullptr )
        return true;
    if( node->left != nullptr && node->left->value > node->value )
        return false;
    if( node->right != nullptr && node->right->value < node->value )
        return false;
    return ( IsValidBinaryTree( node->left ) && IsValidBinaryTree( node->right ) );
}

int main( int argc, char *argv[] ) {
    std::cout << "Enter number of nodes: ";
    int num;
    std::cin >> num;
    std::cout << "Enter node values, -999 for null node, <enter> to stop:\n";
    std::vector< int > input;
    int val;
    while( num-- && std::cin >> val ) {
        input.push_back( val );
    }

    int index = 0;
    Node *root = CreateTreeFromInput( index, input );
    std::cout << "\nInorder Traversal: ";
    InOrderTraversal( root );
    std::cout << "\nPreorder Traversal: ";
    PreOrderTraversal( root );
    std::cout << "\nChecking if the tree was a valid binary tree: " << std::boolalpha << IsValidBinaryTree( root ) <<
    std::endl;
    sleep( 1 );
    return 0;
}