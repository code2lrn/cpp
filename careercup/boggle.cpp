//
// Created by Ranga on 5/29/16.
//

#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>
#include <set>
#include <iterator>
#include <chrono>

using Word = std::string;
using Words = std::vector< Word >;
using Matrix = std::vector< std::vector< char > >;
using Path = std::set< std::pair< int, int > >;
using Coordinate = std::pair< int, int >;
using Coordinates = std::vector< Coordinate >;

struct TrieEntry {
    std::array< TrieEntry*, 26 > nextChar;
    Words words;
    TrieEntry() {
        nextChar.fill( nullptr );
    }
};

void AddToTrie( TrieEntry &t, const Word &word, const unsigned index ) {
    if( index > word.length() ) {
        return;
    }

    if( index == word.length() ) {
        t.words.push_back( word );
    }
    else {
        auto nextChar = std::tolower( word[ index ] );
        if( t.nextChar[ nextChar - 'a' ] == nullptr ) {
            t.nextChar[ nextChar - 'a' ] = new TrieEntry;
        }
        AddToTrie( *( t.nextChar[ nextChar - 'a' ] ), word, index + 1 );
    }
}

TrieEntry PopulateTrie( const std::string dictionaryFileName ) {
    TrieEntry trieHead;
    std::ifstream fileDictionary( dictionaryFileName );
    while( fileDictionary.is_open() && !fileDictionary.eof() ) {
        Word word;
        std::getline( fileDictionary, word, '\n' );
        if( std::any_of( word.begin(), word.end(), []( const auto ch ){ return( tolower( ch ) < 'a' || tolower( ch ) > 'z' ); } ) ) {
            continue;
        }
        AddToTrie( trieHead, word, 0 );
    }
    fileDictionary.close();
    return trieHead;
}

/*
    std::cout << "Finding Abe in Trie: " << std::boolalpha << FindInTrie( &trieHead, "Abe" ) << std::endl;
    std::cout << "Finding RangaReddy in Trie: " << std::boolalpha << FindInTrie( &trieHead, "RangaReddy" ) << std::endl;
    std::cout << "Finding Rangoon in Trie: " << std::boolalpha << FindInTrie( &trieHead, "Rangoon" ) << std::endl;
    std::cout << "Finding Rankin in Trie: " << std::boolalpha << FindInTrie( &trieHead, "Rankin" ) << std::endl;
    std::cout << "Finding Rankine in Trie: " << std::boolalpha << FindInTrie( &trieHead, "Rankine" ) << std::endl;
    std::cout << "Finding Rankined in Trie: " << std::boolalpha << FindInTrie( &trieHead, "Rankined" ) << std::endl;
*/

bool FindInTrie( const TrieEntry *trieHead, const Word &word ) {
    if( word.length() < 1 ) {
        return false;
    }

    unsigned i = 0;
    auto *trieEntry = trieHead;
    while( i < word.length() && trieEntry->nextChar[ tolower( word[ i ] ) - 'a' ] != nullptr ) {
        trieEntry = trieEntry->nextChar[ tolower( word[ i ] ) - 'a' ];
        ++i;
    }

    return i == word.length() && trieEntry != nullptr && trieEntry->words.size() > 0;
}

class MatrixPositions {
public:
    MatrixPositions( const unsigned size ) : size( size ) { }

    Coordinates GetAdjacentPositions( const int i, const int j ) const {
        Coordinates coordinates;
        if( i - 1 > -1 ) { // Above
            if( j - 1 > -1 ) { // Left
                coordinates.push_back( std::make_pair( i - 1, j - 1 ) );
            }
            coordinates.push_back( std::make_pair( i - 1, j ) );
            if( j + 1 < size ) { // Right
                coordinates.push_back( std::make_pair( i - 1, j + 1 ) );
            }
        }

        if( j - 1 > -1 ) { // To the left
            coordinates.push_back( std::make_pair( i, j - 1 ) );
        }

        if( j + 1 < size ) { // To the Right
            coordinates.push_back( std::make_pair( i, j + 1 ) );
        }

        if( i + 1 < size ) { // Below
            if( j - 1 > -1 ) { // Left
                coordinates.push_back( std::make_pair( i + 1, j - 1 ) );
            }
            coordinates.push_back( std::make_pair( i + 1, j ) );
            if( j + 1 < size ) { // Right
                coordinates.push_back( std::make_pair( i + 1, j + 1 ) );
            }
        }

        return coordinates;
    }

    Coordinates GetAdjacentPositions( const Coordinate &coordinate ) const {
        return GetAdjacentPositions( coordinate.first, coordinate.second );
    }
private:
    const int size;
};

void RecursiveMatchUsingTrie( const TrieEntry *trieEntry, const Matrix &matrix, const MatrixPositions &matrixPositions, const Coordinate &coordinate, Path &path, Words &words ) {
    auto ch = matrix[ coordinate.first ][ coordinate.second ];
    if( trieEntry->nextChar[ tolower( ch ) - 'a' ] == nullptr ) {
        return;
    }

    trieEntry = trieEntry->nextChar[ tolower( ch ) - 'a' ];
    path.insert( coordinate );
    Coordinates adjacentCoordinates{ matrixPositions.GetAdjacentPositions( coordinate ) };
    auto wordsBeforeIteration = words.size();
    for( const auto &c : adjacentCoordinates ) {
        auto alreadyInPath = path.find( c );
        if( alreadyInPath != path.end() ) {
            continue;
        }
        RecursiveMatchUsingTrie( trieEntry, matrix, matrixPositions, c, path, words );
    }
    path.erase( coordinate );
    if( trieEntry->words.size() && wordsBeforeIteration == words.size() ) {
        std::copy( trieEntry->words.begin(), trieEntry->words.end(), std::back_inserter( words ) );
    }
}


int main( int argc, char *argv[] ) {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    TrieEntry trieHead = PopulateTrie( "/usr/share/dict/words" );

    std::chrono::steady_clock::time_point load = std::chrono::steady_clock::now();

    Matrix matrix{{ { 'a', 'b', 'c', 'd' },
                    { 'e', 'k', 'l', 'a' },
                    { 'c', 'a', 'm', 'n' },
                    { 'd', 'i', 'n', 'g' } }};

    int N = matrix.size();
    const MatrixPositions matrixPositions{ static_cast<unsigned>( N ) };
    for( auto i = 0; i < N; ++i ) {
        for( auto j = 0; j < N; ++j ) {
            Path path;
            Words words;
            RecursiveMatchUsingTrie( &trieHead, matrix, matrixPositions, std::make_pair( i, j ), path, words );
            if( words.size() == 0 ) {
                continue;
            }
            else {
                std::copy( words.begin(), words.end(), std::ostream_iterator< Word >( std::cout, "\n" ) );
            }
        }
    }

    std::chrono::steady_clock::time_point evaluated = std::chrono::steady_clock::now();

    std::cout << "Creating Trie from dictionary took " << std::chrono::duration_cast<std::chrono::microseconds>( load - start ).count() << " ms.\n";
    std::cout << "Determining posible words took " << std::chrono::duration_cast<std::chrono::microseconds>( evaluated - load ).count() << " ms.\n";

    return 0;
}