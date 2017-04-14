//
// Created by Ranga on 3/6/17.
//


#include <array>
#include <vector>
#include <iostream>

struct Tick{
    Tick() : current_time( 0 ), value( 0 ) {}
    Tick( time_t t ) : current_time( t ), value( 0 ) {}
    Tick( time_t t, double v ) : current_time( t ), value( v ) {}
    bool operator == ( const Tick &t2 ) const {  return this->current_time == t2.current_time; }
    bool operator < ( const Tick &t2 ) const { return this->current_time < t2.current_time; }
    friend std::ostream& operator << ( std::ostream &out, const Tick &t ) { out << t.current_time << ":" << t.value << std::endl; return out; }

    time_t current_time;
    double value;
};

template < typename T, unsigned S >
class CircularQueue {
public:
    CircularQueue() : backOfQueue( 0 ), frontOfQueue( -1 ), lastItemIndex( 0 ), capacity( S ), numItems( 0 ) { }

    void ReplaceBackOfQueueOrPush(const T &data) {
        if( NumItems() > 0 && queue[ lastItemIndex ] == data ) {
            queue[ lastItemIndex ] = data;
            return;
        }

        if( backOfQueue == frontOfQueue ) { // We are about to wrap around
            frontOfQueue = ( frontOfQueue + 1 ) % capacity;
        }
        queue[ backOfQueue ] = data;
        lastItemIndex = backOfQueue;
        backOfQueue = ( backOfQueue + 1 ) % capacity;
        numItems = std::min( numItems + 1, capacity );
        if( frontOfQueue == -1 ) {
            ++frontOfQueue;
        }
    }

    T PeekFront() const {
        return NumItems() ? queue[ frontOfQueue ] : T();
    }

    unsigned NumItems() const {
        return numItems;
    }

    T Search( const T &data ) {
        if( frontOfQueue > 0 ) { // 2 binary search by range
            auto it1 = std::lower_bound( queue.begin() + frontOfQueue, queue.end(), data );
            if( it1 == queue.end() || !( *it1 == data ) ) {
                auto it2 = std::lower_bound( queue.begin(), queue.begin() + lastItemIndex, data );
                return ( it2 == queue.end() || !( *it2 == data ) ) ? Tick( 0 ) : *it2;
            }
            else {
                return *it1;
            }
        }
        else { // 1 binary search
            auto it = std::lower_bound( queue.begin(), queue.begin() + NumItems(), data );
            return ( it == queue.end() || !( *it == data ) ) ? Tick( 0 ) : *it;
        }
    }

private:
    std::array< T, S > queue;
    int backOfQueue, frontOfQueue, lastItemIndex;
    const unsigned capacity;
    unsigned numItems;
};

class TimeSeries {
public:
    TimeSeries(size_t window) {}
    void AddValue(time_t current_time, double value) {
        static time_t lastTimeAdded = 0;
        if( lastTimeAdded == current_time ) {
            return;
        }

        circularQueue.ReplaceBackOfQueueOrPush( Tick( current_time, value ) );
    }

    double GetValue(time_t desired_time) {
        Tick lowestTick = circularQueue.PeekFront();
        if( lowestTick.current_time > desired_time ) {
            return 0;
        }

        Tick tickFound = circularQueue.Search( Tick( desired_time ) );
        while( tickFound.current_time != desired_time && desired_time >= lowestTick.current_time ) {
            --desired_time;
            tickFound = circularQueue.Search( Tick( desired_time ) );
        }

        return desired_time >= lowestTick.current_time ? tickFound.value : 0;
    }

private:
    CircularQueue< Tick, 5000 > circularQueue;
};

int main( int argc, char *argv[] ) {

    CircularQueue< Tick, 7 > circularQueue;
    circularQueue.ReplaceBackOfQueueOrPush(Tick(1, 1.1));
    circularQueue.ReplaceBackOfQueueOrPush(Tick(2, 2.1));
    circularQueue.ReplaceBackOfQueueOrPush(Tick(3, 3.1));
    circularQueue.ReplaceBackOfQueueOrPush(Tick(4, 4.1));
    circularQueue.ReplaceBackOfQueueOrPush(Tick(5, 5.1));
    circularQueue.ReplaceBackOfQueueOrPush(Tick(6, 6.1));
    circularQueue.ReplaceBackOfQueueOrPush(Tick(7, 7.1));
    circularQueue.ReplaceBackOfQueueOrPush(Tick(8, 8.1));
    circularQueue.ReplaceBackOfQueueOrPush(Tick(8, 8.2));
    circularQueue.ReplaceBackOfQueueOrPush(Tick(10, 10.1));

    std::cout << circularQueue.Search( Tick( 7 ) );
    std::cout << circularQueue.Search( Tick( 9 ) );
    std::cout << circularQueue.Search( Tick( 1 ) );
    std::cout << circularQueue.Search( Tick( 6 ) );
    //circularQueue.NumItems();
    return 0;
}