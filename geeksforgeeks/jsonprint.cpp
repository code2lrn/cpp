//
// Created by Ranga on 6/18/16.
//

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <iterator>

std::string GetIndentation( int indentationLevel ) {
    std::string retVal;
    for( auto i = 0; i < indentationLevel; ++i ) {
        retVal += '\t';
    }
    return retVal;
}

int main( int argc, char *argv[] ) {

    std::string input = "{A:\"B\",C:{D:\"E\",F:{G:\"H\",I:\"J\"}}}";
    input = "[\"foo\", {\"bar\":[\"baz\",null,1.0,2]}]";
    std::stringstream ss( input );
    std::string line;
    std::vector< std::string > lines;
    char ch;
    unsigned indentationLevel = 0;
    while( ss >> ch ) {
        switch( ch ) {
            case '{' :
            case '[' :
            case '}' :
            case ']' :
                if( line.length() > 0 ) {
                    lines.push_back( GetIndentation( indentationLevel ).append( line ) );
                    line.clear();
                }
                if( ch == '{' || ch == '[' ){
                    lines.push_back( GetIndentation( indentationLevel++ ) + ch );
                }
                else {
                    lines.push_back( GetIndentation( --indentationLevel ) + ch );
                }
                line.clear();
                break;
            case ',':
                line += ch;
                lines.push_back( GetIndentation( indentationLevel ).append( line ) );
                line.clear();
                break;
            default:
                line += ch;
        }
    }

    std::copy( lines.begin(), lines.end(), std::ostream_iterator< std::string >( std::cout, "\n" ) );
    return 0;
}