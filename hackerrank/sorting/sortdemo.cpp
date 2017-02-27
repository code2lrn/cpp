//
// Created by Ranga on 2/26/17.
//

#include <cassert>
#include "sortutils.h"

int QsortPartition( std::vector< int > &array, int left, int right ) {
    auto mid = ( left + right ) / 2;
    auto pivotElement = array[ mid ];
    auto l = left + 1, r = right;
    std::swap( array[ mid ], array[ left ] );
    while( l <= r ) {
        while( array[ r ] > pivotElement )
            --r;
        while( l <= r && array[ l ] <= pivotElement )
            ++l;
        if( l <= r ) {
            std::swap( array[ l ], array[ r ] );
            ++l;
            --r;
        }
    }
    std::swap( array[ left ], array[ r ] );
    return r;
}

void Qsort( std::vector< int > &array, int l, int r ) {
    if( l >= r ) {
        return;
    }
    auto partition = QsortPartition( array, l, r );
    Qsort( array, l, partition - 1 );
    Qsort( array, partition + 1, r );
}

class Heap {
public:
    Heap( const std::vector< int > &a ) : maxHeapSize ( a.size() ), numElements( 0 ) {
        array.reserve( a.size() );
        for( auto num : a ) {
            Insert( num );
        }
    }

    bool HasElements() const {
        return numElements > 0;
    }

    int GetMinValue() {
        assert( HasElements() );
        auto minValue = array[ 1 ];
        array[ 1 ] = array[ numElements ];
        --numElements;
        MaxValueBubbleDown( 1 );
        return minValue;
    }

private:
    unsigned long maxHeapSize, numElements;
    std::vector< int > array;

    void Insert( const int num ) {
        assert( numElements < maxHeapSize );
        array[ ++numElements ] = num;
        MinValueBubbleUp( numElements );
    }

    void MinValueBubbleUp( int elementAt ) {
        auto parent = Parent( elementAt );
        if( parent == 0 ) {
            return;
        }

        if( array[ parent ] > array[ elementAt ] ) {
            std::swap( array[ parent ], array[ elementAt ] );
            MinValueBubbleUp( parent );
        }
    }

    void MaxValueBubbleDown( int elementAt ) {

        auto youngestChild = YoungestChild( elementAt );
        auto childIndexWithLowerValue = elementAt;
        for( auto i = 0; i <= 1; ++i ) {
            if( youngestChild + i <= numElements && array[ youngestChild + i ] < array[ childIndexWithLowerValue ] ) {
                childIndexWithLowerValue = youngestChild + i;
            }
        }
        if( childIndexWithLowerValue != elementAt ) {
            std::swap( array[ elementAt ], array[ childIndexWithLowerValue ] );
            MaxValueBubbleDown( childIndexWithLowerValue );
        }
    }

    int Parent( int elementAt ) {
        return floor( elementAt / 2 );
    }

    int YoungestChild( int elementAt ) {
        return elementAt * 2;
    }
};

int main( int argc, char *argv[] ) {

    std::vector< int > master( SortUtils::GetNBoundedRandomInts( -1000, 1000, 50 ) );
    std::copy( master.begin(), master.end(), std::ostream_iterator< int >( std::cout, " " ) );
    std::cout << std::endl;

    std::vector< int > array1( master );
    Qsort( array1, 0, array1.size() - 1 );
    std::copy( array1.begin(), array1.end(), std::ostream_iterator< int >( std::cout, " " ) );
    std::cout << std::endl;

    std::vector< int > array2( master );
    Heap heap{ array2 };
    while( heap.HasElements() ) {
        std::cout << heap.GetMinValue() << " ";
    }
    std::cout << std::endl;
    return 0;
}