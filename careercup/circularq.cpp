//
// Created by Ranga on 5/30/16.
//

#include <array>
#include <vector>

template < typename T, unsigned S >
class CircularQueue {
public:
    CircularQueue() : backOfQueue( 0 ), frontOfQueue( -1 ), capacity( S ), numItems( 0 ) { }

    void ReplaceBackOfQueueOrPush(const T &data) {
        if( backOfQueue == frontOfQueue ) { // We are about to wrap around
            frontOfQueue = ( frontOfQueue + 1 ) % capacity;
        }
        queue[ backOfQueue ] = data;
        backOfQueue = ( backOfQueue + 1 ) % capacity;
        numItems = std::min( numItems + 1, capacity );
        if( frontOfQueue == -1 ) {
            ++frontOfQueue;
        }
    }

    unsigned NumItems() const {
        return numItems;
    }

    std::vector< T > PopNOrLess( const unsigned N ) {
        std::vector< T > items;
        unsigned itemsAvailable = std::min( N, NumItems() );
        unsigned i = 0;
        while( i++ < itemsAvailable ) {
            items.push_back( queue[ frontOfQueue ] );
            frontOfQueue = ( frontOfQueue + 1 ) % capacity;
            numItems = std::max( numItems - 1, static_cast< unsigned >( 0 ) );
        }
        return items;
    }

private:
    std::array< T, S > queue;
    int backOfQueue, frontOfQueue;
    const unsigned capacity;
    unsigned numItems;
};

int main( int argc, char *argv[] ) {
    CircularQueue< int, 4 > q;
    q.ReplaceBackOfQueueOrPush(1);
    q.ReplaceBackOfQueueOrPush(2);
    q.ReplaceBackOfQueueOrPush(3);
    q.ReplaceBackOfQueueOrPush(4);
    q.ReplaceBackOfQueueOrPush(5);
    std::vector< int > prior2 = q.PopNOrLess( 2 ); // 2, 3
    std::vector< int > last2 = q.PopNOrLess( 2 ); // 4, 5
    q.ReplaceBackOfQueueOrPush(6);
    q.ReplaceBackOfQueueOrPush(7);
    q.ReplaceBackOfQueueOrPush(8);
    q.ReplaceBackOfQueueOrPush(9);
    q.ReplaceBackOfQueueOrPush(10);
    q.ReplaceBackOfQueueOrPush(11);
    q.ReplaceBackOfQueueOrPush(12);
    std::vector< int > final6 = q.PopNOrLess( 6 ); // Will only get => 9, 10, 11, 12
    std::vector< int > none = q.PopNOrLess( 1 ); // There will be nothing in this
    return 0;
}