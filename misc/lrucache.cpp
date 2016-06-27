//
// Created by Ranga on 6/7/16.
//

#include <ostream>
#include <iostream>

template< typename D >
struct LRUNode {
    D       data;
    LRUNode *left;
    LRUNode *right;

    ~LRUNode() {
        left = right = nullptr;
    }
};

template< typename V >
class LRUList {
public:
    LRUList() : head( nullptr ) {}

    LRUNode< V >* AddNode( const V& data ) {
        auto node = new LRUNode< V >;
        node->data = data;
        node->left = nullptr;
        node->right = head;
        if( head != nullptr ) {
            head->left = node;
        }
        head = node;
        return head;
    }

    bool RemoveNode( LRUNode< V > *node ) {
        if( node == nullptr ) {
            return false;
        }

        if( node == head ) {
            head = head->right;
            delete node;
            return true;
        }

        if( node->left != nullptr ) {
            auto lhs = node->left;
            auto rhs = node->right;
            if( rhs != nullptr ) {
                rhs->left = lhs;
            }
            lhs->right = node->right;
            delete node;
            return true;
        }
    }

    friend std::ostream& operator<< ( std::ostream& out, const LRUList< V >& list ) {
        auto node = list.head;
        while( node != nullptr ) {
            out << node->data << " <-> ";
            node = node->right;
        }
        return out;
    }

private:
    LRUNode< V > *head;
};

int main( int argc, char *argv[] ) {

    LRUList< int > list;
    auto node5 = list.AddNode( 10 );
    auto node4 = list.AddNode( 12 );
    auto node3 = list.AddNode( 13 );
    auto node2 = list.AddNode( 14 );
    auto node1 = list.AddNode( 9 );
    std::cout << "The list is:    " << list << std::endl;

    list.RemoveNode( node2 );
    std::cout << "The list now is " << list << std::endl;

    list.RemoveNode( node4 );
    std::cout << "The list now is " << list << std::endl;

    list.RemoveNode( node1 );
    std::cout << "The list now is " << list << std::endl;

    list.RemoveNode( node5 );
    std::cout << "The list now is " << list << std::endl;

    return 0;
}