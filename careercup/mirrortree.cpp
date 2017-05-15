//
// Created by Ranga on 5/14/17.
//

#include <initializer_list>
#include <iostream>

class BTree {
public:
    BTree( const std::initializer_list< int > &values ) : root( nullptr ){
        for( auto val : values ) {
            IterativeInsert( val );
        }
    }

    void PrintInOrder() {
        PrintInOrder( this->root );
        std::cout << std::endl;
    }

    bool MakeMirrorTree() {
        if( !this->root || ( this->root->l && this->root->r ) || !( this->root->l || this->root->r ) )
            return false;

        if( this->root->l == nullptr )
            this->root->l = CreateMirror( this->root->r );
        else
            this->root->r = CreateMirror( this->root->l );
    }

    bool IsMirrorTree() {
        if( !this->root )
            return true;
        return IsMirrorTree( this->root->l, this->root->r );
    }

    void Push( int val ) {
        IterativeInsert( val );
    }

private:
    struct Node {
        int val;
        Node *l;
        Node *r;
        Node( int v ) : val( v ), l( nullptr ), r( nullptr ) { }
    };

    Node *root;
    void IterativeInsert( int val ) {
        if( root == nullptr ) {
            root = new Node{ val };
            return;
        }
        auto q = this->root;
        while( q ) {
            if( q->val > val ) {
                if( q->l == nullptr ) {
                    q->l = new Node{ val };
                    return;
                }
                else
                    q = q->l;
            }
            else {
                if( q->r == nullptr ) {
                    q->r = new Node{ val };
                    return;
                }
                else
                    q = q->r;
            }
        }
        std::cout << "Error adding " << val << std::endl;
    }
    void PrintInOrder( Node *n ) {
        if( !n )
            return;
        PrintInOrder( n->l );
        std::cout << n->val << " ";
        PrintInOrder( n->r );
    }
    Node* CreateMirror( Node *n ) {
        if( !n )
            return nullptr;
        Node *tmp = new Node{ n->val };
        tmp->l = CreateMirror( n->r );
        tmp->r = CreateMirror( n->l );
        return tmp;
    }

    bool IsMirrorTree( Node *p, Node *q ) {
        if( !p || !q )
            return !p && !q;

        return p->val == q->val && IsMirrorTree( p->l, q->r ) && IsMirrorTree( p->r, q->l );
    }
};

int main( int argc, char *argv[] ) {

    BTree b{ 10, 5, 3, 6, 7 };
    b.PrintInOrder();
    b.MakeMirrorTree();
    b.PrintInOrder();
    std::cout << "IsMirrorTree(): " << std::boolalpha << b.IsMirrorTree() << std::endl;
    b.Push( 8 );
    std::cout << "IsMirrorTree(): " << std::boolalpha << b.IsMirrorTree() << std::endl;
    return 0;
}