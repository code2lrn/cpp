//
// Created by Ranga on 6/26/16.
//

#ifndef PROJECT_SORTUTILS_H
#define PROJECT_SORTUTILS_H

#include <cstddef>
#include <iostream>
#include <iterator>
#include <limits>
#include <random>
#include <functional>
#include <algorithm>

namespace SortUtils {

std::vector< int > GetNBoundedRandomInts( const int &minValue, const int &maxValue, const size_t &numValues ) {
    std::vector< int > randomItems;
    if( minValue > maxValue ) {
        return randomItems;
    }

    std::random_device rd;
    std::mt19937 engine{ rd() };
    std::uniform_int_distribution<> dist{ minValue, maxValue };

    randomItems.resize( numValues );
    std::generate( randomItems.begin(), randomItems.end(), std::bind( dist, std::ref( engine ) ) );

    return std::move( randomItems );
}

std::vector< int > GetNSortedBoundedRandomInts( const int &minValue, const int &maxValue, const size_t &numValues ) {
    auto randomItems = GetNBoundedRandomInts( minValue, maxValue, numValues );
    std::sort( randomItems.begin(), randomItems.end() );
    return randomItems;
}

int QSortPartition( const int left, const int right, std::vector< int > &items ) {
    int pivot = ( left + right ) / 2; // This need not be the return value
    auto l = left, r = right - 1;
    auto pivotElement = items[ pivot ]; // Elements to the left of this function's return value will be less than this amount
    std::swap( items[ pivot ], items[ right ] ); // Squirrel this number away at the end so we can look the remaining numbers
    while( l < r ) {
        while( l < r && items[ l ] < pivotElement )
            ++l;

        while( r > l && items[ r ] > pivotElement )
            r--;

        if( l < r )
            std::swap( items[ l ], items[ r ] );
    }

    std::swap( items[ l ], items[ right ] ); // Put the Pivot element where it belongs
    return l; // l will not always be Pivot.
}

int KthMinQSort( std::vector< int > &items, const int k ) {
    auto left = 0, right = (int)items.size() - 1, adjustedK = k - 1;
    while( true ) {
        auto partition = QSortPartition( left, right, items );
        if( partition == adjustedK ) {
            return items[ partition ];
        }
        else if( partition < adjustedK ) {
            left = partition;
        }
        else {
            right = partition;
        }
    }
}

int KthMinSelectionSort( std::vector< int > &items, const int k ) {
    auto pos = -1;
    while( ++pos <= k ) {
        auto smallest = std::min_element( items.begin() + pos, items.end() );
        std::swap( items[ pos ], *smallest );
    }
    return( items[ k ] );
}

};

#endif //PROJECT_SORTUTILS_H
