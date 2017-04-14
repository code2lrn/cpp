//
// Created by Ranga on 3/6/17.
//

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>

/*
using Page = std::vector< std::string >;
using Book = std::vector< Page >;
using OccurencesByWord = std::map< std::string, std::vector< unsigned > >;

void Ingest( const std::string &word, unsigned pageNum, OccurencesByWord &occurencesByWord ) {
    auto it = occurencesByWord.find( word );
    if( it == occurencesByWord.end() ) {
        occurencesByWord.insert( it, std::make_pair( word, { pageNum } ) );
    }
    else {
        it->second.push_back( pageNum );
    }
}
*/

std::string GetPageNumsAsString( const std::vector< unsigned > &pageNumbers ) {
    std::stringstream ss;
    if( pageNumbers.size() == 0 ) {
        return "";
    }

    auto priorNum = pageNumbers[ 0 ], lastNum = pageNumbers[ pageNumbers.size() - 1 ];
    unsigned runLength = 1;
    ss << priorNum;
    std::for_each( pageNumbers.begin() + 1, pageNumbers.end(), [ &priorNum, &runLength, lastNum, &ss ]( auto num ) {
        if( num > priorNum + 1 ) {
            if( runLength > 1 ) {
                ss << "-" << priorNum;
            }
            ss << ", " << num;
            runLength = 1;
        }
        else {
            ++runLength;
            if( num == lastNum ) {
                ss << "-" << num;
            }
        }
        priorNum = num;
    } );

    return ss.str();
}

/*
void PrintWordCount( const std::string &book, const Book &content ) {

    OccurencesByWord occurencesByWord;
    unsigned pageNum = 0;
    for( const auto &page : content ) {
        ++pageNum;
        for( const auto &line : page ) {
            std::stringstream ss( line );
            std::string word;
            while( ss >> word ) {
                Ingest( word, pageNum, occurencesByWord );
            }
        }
    }

    for( auto &entry : occurencesByWord ) {
        auto newEnd = std::unique( entry.second.begin(), entry.second.end() );
        entry.second.erase( newEnd, entry.second.end() );
        std::cout << entry.first << " " << GetPageNumsAsString( entry.second );
    }
}
*/

int main(int argc, char *argv[]) {

    std::cout << GetPageNumsAsString( { } ) << std::endl;
    return 0;
}