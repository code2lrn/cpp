//
// Created by Ranga on 3/12/17.
//

#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <iterator>

class Trie {
public:
    Trie( const std::vector< std::string > &words ) {
        std::fill( trieNodes.begin(), trieNodes.end(), nullptr );
        std::for_each( words.begin(), words.end(), [ this ]( const auto &str ){ this->Ingest( str ); } );
    }

    std::string GetSmallestPrefix( const std::string &str ) {
        std::stringstream ss;
        TrieNode *entry = nullptr;
        for( auto ch : str ) {
            if( entry == nullptr ) {
                entry = trieNodes[ ch - 'a' ];
                if( entry == nullptr ) {
                    return "";
                }
                ss << ch;
            }
            else {
                if( entry->Exists( ch ) ) {
                    ss << ch;
                    entry = entry->Get( ch );
                }
                else {
                    return "";
                }
            }

            if( entry->GetUseCount() == 1 ) {
                break;
            }
        }

        return ss.str();
    }

private:
    class TrieNode {
    public:
        static TrieNode* CreateNode( char c ) { auto *ptr = new TrieNode( c ); return ptr; }
        void SetValidWord() { validWord = true; }
        bool GetValidWord() { return validWord; }
        bool Exists( char c ) { return c >= 'a' && c <= 'z' && nextCh[ c - 'a' ] != nullptr; }
        void IncrementUseCount() { ++useCount; }
        int  GetUseCount() { return useCount; }
        TrieNode* Get( char c ) { return nextCh[ c - 'a' ]; }
        TrieNode* AddNext( char c ) { nextCh[ c - 'a' ] = TrieNode::CreateNode( c ); return nextCh[ c - 'a' ]; }

    private:
        TrieNode( char c ) : ch ( c ), validWord( false ), useCount(1) { std::fill( nextCh.begin(), nextCh.end(), nullptr ); }

        char ch;
        bool validWord;
        int  useCount;
        std::array< TrieNode*, 26 > nextCh;
    };

    void Ingest( const std::string &str ) {
        TrieNode *entry = nullptr;
        for( auto ch : str ) {
            if( entry == nullptr ) {
                if( trieNodes[ ch - 'a' ] == nullptr ){
                    trieNodes[ ch - 'a' ] = TrieNode::CreateNode( ch );
                    entry = trieNodes[ ch - 'a' ];
                }
                else {
                    entry = trieNodes[ ch - 'a' ];
                    entry->IncrementUseCount();
                }
            }
            else {
                if( entry->Exists( ch ) ) {
                    entry = entry->Get( ch );
                    entry->IncrementUseCount();
                }
                else {
                    entry = entry->AddNext( ch );
                }
            }
        }
        if( entry != nullptr ) {
            entry->SetValidWord();
        }
    }

    std::array< TrieNode*, 26 > trieNodes;
};

int main( int argc, char *argv[] ) {

    std::vector< std::string > words{ "zebra", "dog", "duck", "dove" };
    Trie trie( words );
    std::vector< std::string > prefixes;
    std::for_each( words.begin(), words.end(), [ &trie, &prefixes ]( const auto &word ){
        prefixes.push_back( trie.GetSmallestPrefix( word ) );
    } );
    std::copy( prefixes.begin(), prefixes.end(), std::ostream_iterator< std::string >( std::cout, " " ) );

    return 0;
}