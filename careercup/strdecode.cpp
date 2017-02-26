//
// Created by Ranga on 1/30/17.
//

#include <iostream>
#include <sstream>
#include <stack>

std::string Decode(const std::string &str ) {
    std::stringstream ss;
    std::stack< unsigned > priorNumbers;
    std::stack< std::string > priorStrings;
    std::string latestCharSeq;
    unsigned latestNumber = 0;
    for( size_t i = 0; i < str.size(); ++i ) {
        auto ch = str[ i ];
        switch( ch ) {
            case '[' :
                priorNumbers.push( latestNumber );
                latestNumber = 0;
                break;
            case ']' : {
                //
                auto repeatCount = priorNumbers.top();
                std::stringstream tmp;
                while (repeatCount--) {
                    tmp << latestCharSeq;
                }
                priorNumbers.pop();
                if (priorStrings.size() == 0) {
                    latestCharSeq = tmp.str();
                } else {
                    auto prefix = priorStrings.top();
                    priorStrings.pop();
                    latestCharSeq = prefix + tmp.str();
                }
                break;
            }
            default:
                if( ch >= '0' && ch <= '9' ) {
                    if( latestCharSeq.size() > 0 ) {
                        priorStrings.push( latestCharSeq );
                        latestCharSeq = "";
                    }
                    latestNumber = latestNumber * 10 + ( ch - '0' );
                }
                else if( ch >= 'a' && ch <= 'z' ) {
                    latestCharSeq += ch;
                }
        };
    }

    if( priorNumbers.size() || priorStrings.size() )
        return "Something wrong";

    return latestCharSeq;
}

int main( int argc, char *argv[] ) {

    //std::string str{ "2[a2[c]d]" };
    std::string str{ "3[a2[bd]g4[ef]h]" };

    std::cout << Decode( str ) << "\n";
/*
    while( std::cin >> str ) {
        std::cout << Decode( str ) << "\n";
    }
*/
    return 0;
}
