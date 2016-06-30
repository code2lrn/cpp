//
// Created by Ranga on 6/29/16.
//

#include "sortutils.h"

std::pair< bool, int > LowestCommonNumber( std::vector< int > &a1, std::vector< int > &a2 ) {
    size_t i = 0, j = 0, A = a1.size(), B = a2.size();
    while( i < A && j < B ) {
        if( a1[ i ] == a2[ j ]  ) {
            return std::make_pair( true, a1[ i ] );
        }
        else if( a1[ i ] < a2[ j ] ) {
            ++i;
        }
        else if( a1[ i ] > a2[ j ] ) {
            ++j;
        }
        else {
            ++i;
            ++j;
        }
    }


    return std::make_pair( false, 0 );
}

std::pair< bool, int > LowestCommonNumber( std::vector< std::vector< int > > &inputArrays ) {

    size_t smallestInputArraySize = std::numeric_limits< size_t >::max();
    std::for_each( inputArrays.begin(), inputArrays.end(),
                   [ &smallestInputArraySize ] ( auto &array ) { smallestInputArraySize = std::min( smallestInputArraySize, array.size() ); } );

    std::vector< int > arrayWatermark( inputArrays.size(), 0 );

    while( std::all_of( arrayWatermark.begin(), arrayWatermark.end(), [ smallestInputArraySize ] ( auto watermark ) { return watermark < smallestInputArraySize; } ) )  {
        std::vector< int > smallestValuesPerArray( inputArrays.size() );
        for( size_t i = 0; i < inputArrays.size(); ++i ) {
            smallestValuesPerArray[ i ] = inputArrays[ i ][ arrayWatermark[ i ] ];
        }
        auto maxValue = std::max_element( smallestValuesPerArray.begin(), smallestValuesPerArray.end() );
        if( std::all_of( smallestValuesPerArray.begin(), smallestValuesPerArray.end(),
                         [ maxValue ] ( auto &value ) { return value == *maxValue; } ) ) {
            return std::make_pair( true, *maxValue );
        }
        else {
            for( size_t i = 0; i < arrayWatermark.size(); ++i ) {
                if( smallestValuesPerArray[ i ] < *maxValue ) {
                    ++arrayWatermark[ i ];
                }
            }
        }
    }

    return std::make_pair( false, 0 );
};

int main( int argc, char *argv[] ) {

    std::vector< int > a1{ SortUtils::GetNSortedBoundedRandomInts( 1, 20, 10 ) };
    std::vector< int > a2{ SortUtils::GetNSortedBoundedRandomInts( 1, 20, 10 ) };

    std::copy( a1.begin(), a1.end(), std::ostream_iterator< int >( std::cout, ", " ) );
    std::cout << std::endl;
    std::copy( a2.begin(), a2.end(), std::ostream_iterator< int >( std::cout, ", " ) );
    std::cout << std::endl;

    auto result = LowestCommonNumber( a1, a2 );
    std::cout << "The lowest common number search returned " << std::boolalpha << result.first << ". The common number is " << result.second << std::endl;

    std::vector< std::vector< int > > inputArrays{ { SortUtils::GetNSortedBoundedRandomInts( 1, 20, 10 ) },
                                                   { SortUtils::GetNSortedBoundedRandomInts( 1, 20, 10 ) },
                                                   { SortUtils::GetNSortedBoundedRandomInts( 1, 20, 10 ) },
                                                   { SortUtils::GetNSortedBoundedRandomInts( 1, 20, 10 ) },
                                                   { SortUtils::GetNSortedBoundedRandomInts( 1, 20, 10 ) }, };
    std::for_each( inputArrays.begin(), inputArrays.end(),
                   []( auto array ) { std::copy( array.begin(), array.end(), std::ostream_iterator< int >( std::cout, ", " ) ); std::cout << std::endl; } );
    result = LowestCommonNumber( inputArrays );
    std::cout << "The lowest common number search returned " << std::boolalpha << result.first << ". The common number is " << result.second << std::endl;

    return 0;
}