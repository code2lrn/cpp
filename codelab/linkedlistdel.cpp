//
// Created by Ranga on 2/19/17.
//

#include <cstddef>
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode( int x ) : val( x ), next( NULL ){ }
};

int main( int argc, char *argv[] ) {

    ListNode *head( NULL ), *tail( NULL );
    /*
    for( auto i = 1; i <= 10; ++i ) {
        for( auto j = 1; j <= 50; ++j ) {
            if( head == NULL ) {
                head = tail = new ListNode( i );
            }
            else {
                tail->next = new ListNode( i );
                tail = tail->next;
            }
        }
    }
    */
    int num;
    while( std::cin >> num ) {
        if( head == NULL ) {
            head = tail = new ListNode( num );
        }
        else {
            tail->next = new ListNode( num );
            tail = tail->next;
        }
    }

    std::cout << "List Before\n";
    for( auto p = head; p != NULL; p = p->next ) {
        std::cout << p->val << " ";
    }
    std::cout << std::endl;

    auto A = head;
    while( A->next != NULL ) {
        if( A->val == A->next->val ) {
            auto tmp = A->next;
            A->next = A->next->next;
            delete tmp;
        }
        else {
            A = A->next;
        }
    }

    std::cout << "List After\n";
    for( auto p = head; p != NULL; p = p->next ) {
        std::cout << p->val << " ";
    }
    std::cout << std::endl;

    return 0;
}