//
// Created by Ranga on 9/13/16.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

struct Quote {
    std::string strDate;
    double      dPrice;
    Quote( std::string s, double d ) : strDate( s ), dPrice( d ) { }
};

std::ostream& operator << ( std::ostream &out, const Quote& quote ) {
    out << quote.strDate << ": " << quote.dPrice;
    return out;
}

using Quotes    = std::vector< Quote >;
using BestPrice = std::pair< Quote, Quote >;

Quotes ReadQuotes( const std::string strInputFile ) {
    std::ifstream finputFile{ strInputFile, std::ifstream::in };
    std::string strInputLine;
    Quotes quotes;
    while( std::getline( finputFile, strInputLine ) ) {
        // Date,Open,High,Low,Close,Volume,Adj Close
        // 2016-09-12,42.279999,43.650002,42.18,43.459999,10767000,43.459999
        std::string strDate;
        double      dClosePrice, dUnused;
        std::stringstream ss( strInputLine );
        ss >> strDate >> dClosePrice;
        quotes.push_back( Quote( strDate, dClosePrice ) );
    }
    return( quotes );
}

int main(int argc, char *argv[] ) {
    //std::cout << "Enter name of input file from yahoo.com: ";
    std::string strInputFile = "/home/shiva/Downloads/s1.csv";
    //std::cin >> strInputFile;
    Quotes quotes = ReadQuotes( strInputFile );
    //std::copy( quotes.rbegin(), quotes.rend(), std::ostream_iterator< Quote >( std::cout, "\n" ) );
    Quote minVal{ "Initial", std::numeric_limits< double >::max() }, maxVal{ "Initial", std::numeric_limits< double >::min() };
    BestPrice bestPrice = std::make_pair( maxVal, minVal );
    std::for_each( quotes.begin(), quotes.end(), [ &minVal, &maxVal, &bestPrice ] ( const Quote &q ) {
        if( q.dPrice < minVal.dPrice )
            minVal = Quote( q.strDate, q.dPrice );

        std::cout << "minValue " << minVal << std::endl;

        if( abs( bestPrice.first.dPrice ) - abs( bestPrice.second.dPrice ) < abs( maxVal.dPrice ) - abs( minVal.dPrice ) )
            bestPrice = std::make_pair( maxVal, minVal );

        std::cout << "bestPrice1 " << bestPrice.first << " => " << bestPrice.second << std::endl;

        if( q.dPrice > maxVal.dPrice ) {
            maxVal = Quote( q.strDate, q.dPrice );
            minVal = Quote( q.strDate, q.dPrice );
        }

        std::cout << "minValue " << minVal << std::endl;
        std::cout << "maxValue " << maxVal << std::endl;

        if( abs( bestPrice.first.dPrice ) - abs( bestPrice.second.dPrice ) < abs( maxVal.dPrice ) - abs( minVal.dPrice ) )
            bestPrice = std::make_pair( maxVal, minVal );

        std::cout << "bestPrice2 " << bestPrice.first << " => " << bestPrice.second << std::endl;
    } );

    std::cout << "Buy at " << bestPrice.second << std::endl;
    std::cout << "Sell at " << bestPrice.first << std::endl;
    return 0;
}
