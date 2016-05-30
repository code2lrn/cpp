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

using Word = std::string;
using Words = std::vector< Word >;

template < typename T, int N >
class Matrix {
public:
    Words GetValidWords() {

    }

private:
    std::array< std::array< T, N >, N > elements;
};

struct TrieEntry {
    char currentChar;
    std::array< TrieEntry*, 26 > nextChar;
    Words words;
    TrieEntry() {
        nextChar.fill( nullptr );
    }
};

void AddToTrie( TrieEntry &t, const Word &word, const int index ) {
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

bool FindInTrie( const TrieEntry *trieHead, const Word &word ) {
    if( word.length() < 1 ) {
        return false;
    }

    return true;
}

int main( int argc, char *argv[] ) {
    //Matrix< int, 4 > m;
    TrieEntry trieHead = PopulateTrie( "/usr/share/dict/words" );

    return 0;
}

