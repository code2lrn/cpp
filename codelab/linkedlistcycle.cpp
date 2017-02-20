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

ListNode* CycleDetected( ListNode *head ) {
    auto t1 = head, t2 = head->next;
    while( t1 != t2 && t2 != NULL ) {
        t1 = t1->next;
        t2 = t2->next->next;
    }
    return t1 == t2 ? t1 : NULL;
}

ListNode* DetermineCycleStart( ListNode *head, ListNode *cycleDetectedAt ) {
    auto cycleStart = head;
    while( true ) {
        auto p = cycleDetectedAt;
        while( p->next != cycleDetectedAt && p->next != cycleStart )
            p = p->next;

        if( p->next == cycleStart )
            return p->next;

        cycleStart = cycleStart->next;
    }
    return NULL;
}

int main( int argc, char *argv[] ) {

    ListNode *head(NULL), *tail(NULL);
    int num = 0;
    while( std::cin >> num ) {
        if (head == NULL) {
            head = tail = new ListNode(num);
        } else {
            tail->next = new ListNode(num);
            tail = tail->next;
        }
    }

    auto p = head;
    auto nthNode = 43;
    while( --nthNode > 0 ) {
        p = p->next;
    }
    tail->next = p;

    auto A = head;

    auto t1 = A, t2 = A->next;
    while( t1 != t2 && t2 != NULL ) {
        t1 = t1->next;
        t2 = t2->next != NULL ? t2->next->next : NULL;
    }
    if( t1 != t2 ) {
        std::cout << "No cycle\n";
        return NULL;
    }

    auto cycleDetectedAt = t1;
    auto cycleStart = A;
    while( true ) {
        auto p = cycleDetectedAt;
        while( p != NULL && p->next != cycleDetectedAt && p->next != cycleStart )
            p = p->next;

        if( p->next == cycleStart ) {
            std::cout << p->next->val << std::endl;
            return 0;
        }

        cycleStart = cycleStart->next;
    }

    return 0;
}