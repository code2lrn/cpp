//
// Created by Ranga on 3/19/17.
//

#include <string>
#include <iostream>
#include <deque>

bool IsOperator( const char c ) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool IsTransitiveOperator( const char c ) {
    return c == '+' || c == '*';
}

std::string Normalize( std::string &postfixExpr ) {
    std::deque< std::string > operands;
    std::string output;
    for( auto ch : postfixExpr ) {
        if( !IsOperator( ch ) ) {
            operands.push_back( std::string( 1, ch ) );
        }
        else {
            auto op1 = operands.back();
            operands.pop_back();
            auto op2 = operands.back();
            operands.pop_back();
            if( IsTransitiveOperator( ch ) ) {
                operands.push_back( std::min( op1, op2 ) + std::max( op1, op2 ) + std::string( 1, ch ) );
            }
            else {
                operands.push_back( op1 + op2 + std::string( 1, ch ) );
            }
        }
    }
    while( !operands.empty() ) {
        output.append( operands.front() );
        operands.pop_front();
    }

    return output;
}

bool AreEquivalentExpressions( std::string postfixExpr1, std::string postfixExpr2 ) {
    postfixExpr1 = Normalize( postfixExpr1 );
    postfixExpr2 = Normalize( postfixExpr2 );
    return postfixExpr1 == postfixExpr2 ;
}

int main( int argc, char *argv[] ) {

    //std::string postfixExpr1{ "abc+de+**" }, postfixExpr2{ "ade+bc+**" };
    std::string postfixExpr1{ "ba+c+" }, postfixExpr2{ "abc++" };
    std::cout << std::boolalpha << AreEquivalentExpressions( postfixExpr1, postfixExpr2 ) << std::endl;
    return 0;
}