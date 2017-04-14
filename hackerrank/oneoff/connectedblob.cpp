//
// Created by Ranga on 3/2/17.
//

#include <iostream>
#include <array>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <tuple>
#include <set>
#include <map>
#include <stack>

template< unsigned N >
class Matrix {
public:
    Matrix( std::initializer_list< std::pair< unsigned, unsigned > > list ) : dimension( N ) {
        // Initialize matrix entries to false
        std::for_each( table.begin(), table.end(),
                       [] ( auto &row ) {
                           std::fill( row.begin(), row.end(), false );
                       }
        );
        // Set matrix values based on input values
        std::for_each( list.begin(), list.end(), [ this ] ( const auto &p ) {
            assert( p.first >= 0 && p.first < this->dimension && p.second >= 0 && p.second < this->dimension );
            this->table[ p.first ][ p.second ] = true;
        } );
    }

    Matrix( std::istream &in ) : dimension( N ) {
        unsigned i = 0;
        for( ; i < dimension; ++i ) {
            unsigned j = 0;
            for( ; j < dimension; ++j ) {
                bool value;
                in >> value;
                table[ i ][ j ] = value;
            }
            assert( j == dimension );
        }
        assert( i == dimension );
    }

    void EvaluateBlobSizeNaive( const std::pair< unsigned, unsigned > &start ) {
        ResetStats();
        blobDimensions.Set( start );

        std::map< std::pair< unsigned, unsigned >, bool > visited{ { start, true } };
        // Top
        RecursiveTraverse( visited, std::make_pair( start.first - 1, start.second ), blobDimensions );
        // Right
        RecursiveTraverse( visited, std::make_pair( start.first, start.second + 1 ), blobDimensions );
        // Bottom
        RecursiveTraverse( visited, std::make_pair( start.first + 1, start.second ), blobDimensions );
        // Left
        RecursiveTraverse( visited, std::make_pair( start.first, start.second - 1 ), blobDimensions );

        PrintStats();
    }

    void EvaluateBlobSizeOptimized( const std::pair< unsigned, unsigned > &start ) {
        ResetStats();
        OptimizedEvalImpl( start );
        PrintStats();
    }

    void EvaluateBlobSizeUnknownStartLocation() {
        ResetStats();
        auto startingNode = GetFirstSetLocation();
        OptimizedEvalImpl( startingNode );
        PrintStats();
    }

    friend std::ostream& operator << ( std::ostream &out, const Matrix &mat ) {
        std::for_each( mat.table.begin(), mat.table.end(),
                       [ &out ] ( auto &row ) {
                           std::copy( row.begin(), row.end(), std::ostream_iterator< bool >( out, " " ) );
                           out << std::endl;
                       }
        );
        return out;
    }

private:
    std::array< std::array< bool, N >, N > table;
    unsigned dimension;
    struct BlobDimensions {
        unsigned top, right, bottom, left;
        unsigned size;
        BlobDimensions() : top( 0 ), right( 0 ), bottom( 0 ), left( 0 ), size( 0 ) { }
        void Reset() {
            top = bottom = left = right = size = 0;
        }
        void Set( const std::pair< unsigned, unsigned > &c ) {
            top  = bottom = c.first;
            left = right  = c.second;
            size = 1;
        }
        void Ingest( const std::pair< unsigned, unsigned > &c ) {
            ++size;
            top     = std::min( top, c.first );
            right   = std::max( right, c.second );
            bottom  = std::max( bottom, c.first );
            left    = std::min( left, c.second );
        }
    };
    BlobDimensions blobDimensions;
    std::vector< std::pair< unsigned, unsigned > > accessRequests;

    void ResetStats() {
        blobDimensions.Reset();
        accessRequests.clear();
    }

    void PrintStats() {
        std::cout << "Cell Reads: " << accessRequests.size() << std::endl
                  << "Top: " << blobDimensions.top << std::endl
                  << "Left: " << blobDimensions.left << std::endl
                  << "Bottom: " << blobDimensions.bottom << std::endl
                  << "Right: " << blobDimensions.right << std::endl
                  << "Size: " << blobDimensions.size << std::endl;
    }

    bool Get( unsigned row, unsigned col ) {
        assert( row >= 0 && row < dimension && col >= 0 && col < dimension );
        accessRequests.push_back( std::make_pair( row, col ) );
        return table[ row ][ col ];
    }

    bool Get( std::pair< unsigned, unsigned > p ) {
        return Get( p.first, p.second );
    }

    bool IsValidLocation( unsigned row, unsigned col ) {
        return row >= 0 && row < dimension && col >= 0 && col < dimension;
    }

    bool IsValidLocation( std::pair<unsigned, unsigned> p ) {
        return IsValidLocation(p.first, p.second);
    }

    double GetDistanceFromCenter( const std::pair< unsigned, unsigned > &c ) {
        return sqrt( std::pow( dimension / 2 - c.first, 2 ) + std::pow( dimension / 2 - c.second, 2 ) );
    }

    std::pair< unsigned, unsigned > GetFirstSetLocation() {
        for( unsigned i = 0; i < dimension; ++i ) {
            for( unsigned j = 0; j < dimension; ++j ) {
                if( Get( i, j ) ) {
                    return std::make_pair( i, j );
                }
            }
        }
        return std::make_pair( 0, 0 );
    };

    void RecursiveTraverse( std::map< std::pair< unsigned, unsigned >, bool > &visited, const std::pair< unsigned, unsigned > &c,
                            BlobDimensions &blobDimensionCumulative ) {
        if( !IsValidLocation(c) ) {
            return;
        }

        auto it = visited.find( c );
        if( it != visited.end() ) {
            return;
        }

        auto value = Get( c );
        it = visited.insert( it, std::make_pair( c, value ) );
        if( !value ) {
            return;
        }

        blobDimensionCumulative.Ingest( c );
        RecursiveTraverse( visited, std::make_pair( c.first - 1, c.second ), blobDimensionCumulative );
        RecursiveTraverse( visited, std::make_pair( c.first, c.second + 1 ), blobDimensionCumulative );
        RecursiveTraverse( visited, std::make_pair( c.first + 1, c.second ), blobDimensionCumulative );
        RecursiveTraverse( visited, std::make_pair( c.first, c.second - 1 ), blobDimensionCumulative );
    }

    std::pair< unsigned, unsigned > NextBestHop( const std::pair< unsigned, unsigned > &c, const std::set<std::pair< unsigned, unsigned>  > &visited ) {
        auto row = c.first, col = c.second;
        std::vector< std::pair<unsigned, unsigned > > possibleHops;
        // top?
        if(IsValidLocation(row - 1, col) ) {
            possibleHops.push_back(std::make_pair( row - 1, col ) );
        }

        // right?
        if(IsValidLocation(row, col + 1) ) {
            possibleHops.push_back(std::make_pair( row, col + 1 ) );
        }

        // bottom?
        if(IsValidLocation(row + 1, col) ) {
            possibleHops.push_back(std::make_pair( row + 1, col ) );
        }

        // left?
        if(IsValidLocation(row, col - 1) ) {
            possibleHops.push_back(std::make_pair( row, col - 1 ) );
        }

        std::pair< unsigned, unsigned > bestHop{ c };
        double farthestNodeDistance = std::numeric_limits< double >::min();
        for( auto hop : possibleHops ) {
            if( visited.find(hop) == visited.end() ) {
                if( farthestNodeDistance < GetDistanceFromCenter( hop ) ) {
                    farthestNodeDistance = GetDistanceFromCenter( hop );
                    bestHop = hop;
                }
            }
        }

        return bestHop;
    };

    void OptimizedEvalImpl( const std::pair< unsigned, unsigned > &start ) {
        blobDimensions.Set( start );

        std::set< std::pair< unsigned, unsigned > > visited{ start };
        std::stack< std::pair< unsigned , unsigned > > path;
        std::pair< unsigned, unsigned > currNode{ start }, nextHop;
        while( true ) {
            // Perform a spiral order traversal on the farthest node from the center that is available
            if( currNode.first == 4 && currNode.second == 4 ) {
                std::cout << "here!\n";
            }
            nextHop = NextBestHop( currNode, visited );
            if( nextHop == start ) {
                // We seem to have gone full circle
                break;
            }

            if( currNode == nextHop ) {
                // No visitable nodes
                if( path.size() > 0 ) {
                    currNode = path.top();
                    path.pop();
                    continue;
                }
                else {
                    // I dont know what this is... write a test, Shiva
                    break;
                }
            }

            visited.insert( nextHop );
            std::cout << "Hop " << nextHop.first << "," << nextHop.second << ": ";
            if( Get( nextHop ) ) {
                blobDimensions.Ingest( nextHop );
                path.push( currNode );
                currNode = nextHop;
                std::cout << " Accepted\n";
            }
            else
                std::cout << " (R)\n";
        }
    }
};

int main( int argc, char *argv[] ) {

/*
    Matrix< 5 > matrix{ {0,4}, {1,1}, {1,2}, {1,3}, {1,4}, {2,0}, {2,1}, {2,2}, {2,3}, {3,0}, {4,0}, {4,1} };
    std::cout << matrix;
    matrix.EvaluateBlobSizeNaive( { 0, 4 } );
    matrix.EvaluateBlobSizeOptimized( { 0, 4  } );
    matrix.EvaluateBlobSizeUnknownStartLocation();


    Matrix< 5 > matrix1{ std::cin };
    std::cout << matrix1;
    matrix1.EvaluateBlobSizeNaive( { 0, 4 } );
    matrix1.EvaluateBlobSizeOptimized( { 0, 4  } );
    matrix1.EvaluateBlobSizeUnknownStartLocation();
*/

/*
    Matrix< 10 > matrix{
                        {1,2}, {1,3}, {1,4},
                        {2,2}, {2,3}, {2,4}, {2,5}, {2,6},
                        {3,2}, {3,6},
                        {4,2}, {4,3}, {4,4}, {4,5}, {4,6},
                        {5,4}, {5,6},
                        {6,4}, {6,6},
                        {7,4}, {7,5}, {7,6}, };
    std::cout << matrix;
    matrix.EvaluateBlobSizeNaive( { 1, 2 } );
    matrix.EvaluateBlobSizeOptimized( { 1, 2 } );
    matrix.EvaluateBlobSizeUnknownStartLocation();
*/

    Matrix< 10 > matrix{ std::cin };
    std::cout << matrix;
    //matrix.EvaluateBlobSizeNaive( { 1, 2 } );
    //matrix.EvaluateBlobSizeOptimized( { 1, 2  } );
    matrix.EvaluateBlobSizeUnknownStartLocation();

    return 0;
}