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
    std::stringstream latestCharSeq;
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
                auto seq = latestCharSeq.str();
                auto repeatCount = priorNumbers.top();
                std::stringstream tmp;
                while (repeatCount--) {
                    tmp << seq;
                }
                priorNumbers.pop();
                if (priorStrings.size() == 0) {
                    priorStrings.push(tmp.str());
                } else {
                    auto prefix = priorStrings.top();
                    priorStrings.pop();
                    priorStrings.push(prefix + tmp.str());
                }
                break;
            }
            default:
                if( ch >= '0' && ch <= '9' ) {
                    auto seq = latestCharSeq.str();
                    if( seq.size() > 0 ) {
                        priorStrings.push( seq );
                        latestCharSeq.clear();
                    }
                    latestNumber = latestNumber * 10 + ( ch - '0' );
                }
                else if( ch >= 'a' && ch <= 'z' ) {
                    latestCharSeq << ch;
                }
        };
    }

    if( priorNumbers.size() || priorStrings.size() != 1 )
        return "Something wrong";

    auto returnStr = priorStrings.top();
    return returnStr;
}

int main( int argc, char *argv[] ) {

    std::string str;
    while( std::cin >> str ) {
        std::cout << Decode( str ) << "\n";
    }
    return 0;
}
