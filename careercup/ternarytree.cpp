//
// Created by Ranga on 5/7/17.
//

#include <string>
#include <stack>
#include <iostream>
#include <sstream>

class TernaryTree {
public:
    TernaryTree( const std::string &expr ) {
        int curr = 0;
        head = ContructTreeRecursive( expr, curr );
        Print( head );
        std::cout << std::endl;
    }

    void Print( Node *n ) {
        if( n == nullptr ) {
            return;
        }

        std::cout << n->val;
        if( n->left ) {
            std::cout << " ? ( ";
            Print( n->left );
            std::cout << " )";
        }
        if( n->right ) {
            std::cout << " : ( ";
            Print( n->right );
            std::cout << " )";
        }
    }

    ~TernaryTree() {
        // destroy head;
    }

private:
    struct Node {
        char val;
        Node *left;
        Node *right;
        Node( char v ) : val( v ), left( nullptr ), right( nullptr ) { }
    };

    Node *head;

    Node* ContructTreeRecursive( const std::string &str, int &curr ) {
        if( curr >= str.size() ) {
            return nullptr;
        }

        auto ch = str[ curr ];
        if( ch == '?' || ch == ':' ) {
            return nullptr;
        }

        Node *n = new Node{ ch };
        if( curr + 4 < str.size() && str[ curr + 1 ] == '?' ) {
            curr += 2;
            n->left = ContructTreeRecursive( str, curr );
            if( curr + 2 < str.size() && str[ curr + 1 ] == ':' ) {
                curr += 2;
                n->right = ContructTreeRecursive( str, curr );
            }
        }

        return n;
    }
};

int main( int argc, char *argv[] ) {

    TernaryTree t1{ "a?b?c:d:x?y:z" }, t2{ "a?b:c" }, t3{ "a?b:c?d:e" }, t4{ "a?b?c:d:e" }, t5{ "a?c" }, t6{ "a?bc" }, t7{ "a" };
    return 0;
}