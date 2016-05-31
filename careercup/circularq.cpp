//
// Created by Ranga on 5/30/16.
//

#include <array>
#include <vector>

template < typename T, unsigned S >
class CircularQueue {
public:
    CircularQueue() : head( 0 ), tail( -1 ), capacity( S ), numItems( 0 ) { }

    void Push( const T& data ) {
        if( head == tail ) { // We are about to wrap around
            tail = ( tail + 1 ) % capacity;
        }
        queue[ head ] = data;
        head = ( head + 1 ) % capacity;
        numItems = std::min( numItems + 1, capacity );
        if( tail == -1 ) {
            ++tail;
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
            items.push_back( queue[ tail ] );
            tail = ( tail + 1 ) % capacity;
            numItems = std::max( numItems - 1, static_cast< unsigned >( 0 ) );
        }
        return items;
    }

private:
    std::array< T, S > queue;
    int head, tail;
    const unsigned capacity;
    unsigned numItems;
};

int main( int argc, char *argv[] ) {
    CircularQueue< int, 4 > q;
    q.Push( 1 );
    q.Push( 2 );
    q.Push( 3 );
    q.Push( 4 );
    q.Push( 5 );
    std::vector< int > prior2 = q.PopNOrLess( 2 ); // 2, 3
    std::vector< int > last2 = q.PopNOrLess( 2 ); // 4, 5
    q.Push( 6 );
    q.Push( 7 );
    q.Push( 8 );
    q.Push( 9 );
    q.Push( 10 );
    q.Push( 11 );
    q.Push( 12 );
    std::vector< int > final6 = q.PopNOrLess( 6 ); // Will only get => 9, 10, 11, 12
    std::vector< int > none = q.PopNOrLess( 1 ); // There will be nothing in this
    return 0;
}