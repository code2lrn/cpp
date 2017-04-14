//
// Created by Ranga on 3/5/17.
//

#include <string>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <memory>
#include <algorithm>
#include <map>
#include <iterator>
#include <cstring>
#include <iomanip>

class Abbreviations {
public:
    Abbreviations( const std::initializer_list< std::string > &initList ) {
        for( auto str : initList ) {
            shortWords.insert( str );
        }
    }

    bool IsAbbreviation( const std::string &str ) const {
        return shortWords.find( str ) != shortWords.end();
    }

private:
    std::unordered_set< std::string > shortWords;
};

class SpecialString {
public:

    SpecialString( const Abbreviations &a ) : abbreviations( a ) { }

    bool ConcludesSentence() {
        return !abbreviations.IsAbbreviation( str ) && EndsWithFullStop();
    }

    std::string GetSanitizedWord() {
        if( abbreviations.IsAbbreviation( str ) ) {
            return str;
        }

        return SpecialString::Sanitize( str );
    }

    friend std::istream& operator >>( std::istream &in, SpecialString &s ) {
        in >> s.str;
        return in;
    }

    friend std::ostream& operator <<( std::ostream &out, const SpecialString &s ) {
        out << s.str;
        return out;
    }

private:
    std::string str;
    const Abbreviations &abbreviations;

    bool EndsWithFullStop() {
        return str.find_last_of( "." ) == str.size() - 1;
    }

    static std::string Sanitize( const std::string &str ) {
        std::string returnStr;
        std::remove_copy_if( str.begin(), str.end(), std::back_inserter( returnStr ),
                             []( const auto &ch ) { return !isalnum( ch ); } );
        std::for_each( returnStr.begin(), returnStr.end(), []( auto &ch ) { ch = tolower( ch ); } );
        return std::move( returnStr );
    }
};

std::string NumToBase26( unsigned num ) {
    std::string base26;
    char digitChars[] = "zabcdefghijklmnopqrstuvwxy";
    while( true ) {
        base26 += digitChars[ num % strlen( digitChars ) ];
        if( num > 26 ) {
            num -= 26;
        }
        else {
            break;
        }
    }

    return base26;
}

void PrintOutput( const std::string &word, const std::vector< unsigned > &occurences, const unsigned &wordNum, const unsigned wordNumWidth, const unsigned longestWordLength ) {
    std::cout << std::setw( wordNumWidth ) << std::left << NumToBase26( wordNum ) + ".";
    std::cout << std::setw( longestWordLength ) << std::left << word << " ";
    std::cout << "{" << occurences.size() << ":";
    std::copy( occurences.begin(), occurences.end() - 1, std::ostream_iterator< unsigned >( std::cout, "," ) );
    std::copy( occurences.end() - 1, occurences.end(), std::ostream_iterator< unsigned >( std::cout, "" ) );
    std::cout << "}" << std::endl;

}

int main( int argc, char *argv[] ) {

    std::string line;
    Abbreviations abr{ "i.e.", "etc.", "Mr.", "Mrs." };
    SpecialString word{ abr };
    unsigned sentencesSeen = 0;
    std::map< std::string, std::vector< unsigned > > occurencesByWord;
    while( std::getline( std::cin, line, '\n' ) ) {
        if( sentencesSeen == 0 ) {
            ++sentencesSeen;
        }

        std::stringstream ss( line );
        while( ss >> word ) {
            auto sanitizedWord = word.GetSanitizedWord();
            if( sanitizedWord.size() == 0 ) {
                continue;
            }
            auto it = occurencesByWord.find( sanitizedWord );
            if( it == occurencesByWord.end() ) {
                occurencesByWord.insert( it, std::make_pair( sanitizedWord, std::vector< unsigned >{ sentencesSeen } ) );
            }
            else {
                it->second.push_back( sentencesSeen );
            }
            if( word.ConcludesSentence() ) {
                ++sentencesSeen;
            }
        }
    }

    unsigned wordNumWidth = (unsigned)NumToBase26( occurencesByWord.size() ).size(), longestWordLength = 0;
    std::for_each( occurencesByWord.begin(), occurencesByWord.end(), [ &longestWordLength ] ( const auto &it ) {
        longestWordLength = std::max( longestWordLength, (unsigned)it.first.length() );
    } );

    unsigned wordNum = 0;
    std::for_each( occurencesByWord.begin(), occurencesByWord.end(), [ &wordNum, wordNumWidth, longestWordLength ]( const auto &it ) {
        PrintOutput( it.first, it.second, ++wordNum, wordNumWidth + 2, longestWordLength );
    } );

    return 0;
}