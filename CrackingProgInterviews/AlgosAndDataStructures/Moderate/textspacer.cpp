//
// Created by Ranga on 2/25/17.
//

#include <array>
#include <bits/unique_ptr.h>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <set>

class Trie {
public:
    Trie( const std::vector< std::string > &words ) {
        std::for_each( words.begin(), words.end(), [ this ]( const auto &word ) { this->IngestWord( word ); } );
    }

    bool Exists( const std::string &str ) const {
        TrieEntry *entry = nullptr;
        auto it = str.begin();
        if( trieEntries[ *it - 'a' ] ) {
            entry = trieEntries[ *it - 'a' ].get();
        }
        else {
            return false;
        }

        for( it = it + 1; it != str.end(); ++it ) {
            if( !( entry->Exists( *it ) ) ) {
                return false;
            }
            entry = entry->Get( *it );
        }

        return entry != nullptr && entry->IsEndOfValidWord();
    }

private:
    class TrieEntry;
    std::array< std::unique_ptr< TrieEntry >, 26 > trieEntries;

    void IngestWord( const std::string word ) {
        TrieEntry *entry = nullptr;
        for( auto ch : word ) {
            if( entry == nullptr ) {
                if( !trieEntries[ ch - 'a' ] ) {
                    trieEntries[ ch - 'a' ] = std::make_unique< TrieEntry >( ch );
                }
                entry = trieEntries[ ch - 'a' ].get();
            }
            else {
                if( entry->Exists( ch ) ) {
                    entry = entry->Get( ch );
                }
                else {
                    entry = entry->AddNext( ch );
                }
            }
        }
        entry->SetValidWord();
    }

    class TrieEntry {
    public:
        TrieEntry( const char ch ) : ch( ch ), endOfValidWord( false ){ }

        bool Exists( const char c ) {
            return c >= 'a' && c <= 'z' && nextCh[ c - 'a' ];
        }

        TrieEntry* AddNext( const char ch ) {
            if( Exists( ch ) ) {
                return nextCh[ ch - 'a' ].get();
            }

            nextCh[ ch - 'a' ] = std::make_unique< TrieEntry >( ch );
            return nextCh[ ch - 'a' ].get();
        }

        TrieEntry* Get( const char ch ) {
            assert( Exists( ch ) );
            return nextCh[ ch - 'a' ].get();
        }

        void SetValidWord() {
            endOfValidWord = true;
        }

        bool IsEndOfValidWord() { return endOfValidWord; }

    private:
        char ch;
        bool endOfValidWord;
        std::array< std::unique_ptr< TrieEntry >, 26 > nextCh;
    };
};

std::string SpaceOutMyWay1( const Trie &trie, const std::string &str ) {
    std::stringstream output, tmp;
    for( auto i = 0; i < str.size(); ++i ) {
        tmp << str[ i ];
        if( trie.Exists( tmp.str() ) ) {
            output << tmp.str() << " ";
            tmp.str( "" );
        }
    }

    return output.str();
}

std::vector<int> GetWordIndexes( const std::set< std::string > &dictionary, const std::string &str ) {

    std::vector<int> result( str.size(), -1 );
    for( auto i = 0; i < str.size(); ++i ) {
        for( auto j = i; j < str.size(); ++j ) {
            auto subStr = str.substr( i, j - i + 1 );
            if( dictionary.find( subStr ) != dictionary.end() ) {
                result[ i ] = j - i + 1;
                i = j;
                break;
            }
        }
    }
    return std::move( result );
}

std::string SpaceOutGreedy( const std::set< std::string > &dictionary, const std::string &str ) {

    auto wordIndexes = GetWordIndexes( dictionary, str );
    std::stringstream result;

    auto i = 0;
    while( i < wordIndexes.size() ) {
        if( wordIndexes[ i ] == -1 ) {
            auto j = i + 1;
            while( j < wordIndexes.size() && wordIndexes[ j ] == -1 ) {
                ++j;
            }
            result << "\"";
            result << str.substr( i, j - i ) << "\" ";
            i = j;
            continue;
        }
        auto subStr = str.substr( i, wordIndexes[ i ] );
        result << subStr << " ";
        i += wordIndexes[ i ];
    }

    return result.str();
}

int main( int argc, char *argv[] ) {

    //Trie trie{ std::vector< std::string >{ "i", "reset", "the", "computer", "it", "still", "didnt", "boot" } };
    //std::cout << SpaceOutMyWay1( trie, "iresetthecomputeritstilldidntboot" );
    const std::set< std::string > dictionary{ "i", "reset", "the", "computer", "it", "still", "didnt", "boot" };
    std::cout << SpaceOutGreedy( dictionary, "iresetthecomputeritstilldidntfuckingboot" );
    return 0;
}