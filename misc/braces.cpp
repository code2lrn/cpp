//
// Created by Ranga on 7/10/16.
//

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>

std::vector< std::string > braces( std::vector< std::string > &values ) {
    std::vector< std::string > output;
    std::for_each( values.begin(), values.end(), [ &output ] ( const std::string &expr ) {
        std::stack< char > state;
        bool isValidExpr = true;
        std::for_each( expr.begin(), expr.end(), [ &state, &isValidExpr ] ( const char ch ) {
            if( !isValidExpr ) {
                return;
            }

            switch( ch ) {
                case '(' :
                case '{' :
                case '[' :
                    state.push( ch );
                    break;
                case ')' :
                case '}' :
                case ']' : {
                    auto prevBrace = state.top();
                    if( ( ch == ')' && prevBrace == '(' )
                        || ( ch == '}' && prevBrace == '{' )
                        || ( ch == ']' && prevBrace == '[' ) ) {
                        state.pop();
                    }
                    else {
                        isValidExpr = false;
                    }
                    break;
                }
                default:
                    isValidExpr = false;
            }
        } );

        if( isValidExpr && state.size() == 0 ) {
            output.push_back( "YES" );
        }
        else {
            output.push_back( "NO" );
        }
    } );

    return output;
}

int main( int argc, char *argv[] ) {

    std::vector< std::string > input;
    int numTestCases;
    std::cin >> numTestCases;
    while( numTestCases-- ) {
        std::string expression;
        std::cin >> expression;
        input.push_back( expression );
    }

    auto output = braces( input );
    std::copy( output.begin(), output.end(), std::ostream_iterator< std::string >( std::cout, "\n" ) );

    return 0;
}