//
// Created by Ranga on 5/14/16.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

enum IncomingQuoteRecord {
    TIMESTAMPID = 0, CURRENCYPAIR, BANK, BUYRATE, SELLRATE, TOTALFIELDS
};
enum Quote {
    BUY, SELL
};
using Bank    = std::string;
using CcyPair = std::string;

struct CcyPairQuote {
    CcyPair pair;
    double buyRate;
    double sellRate;

    CcyPairQuote() = default;

    CcyPairQuote( const CcyPair &cp, const double &bR, const double &sR ) : pair( cp ), buyRate( bR ),
                                                                            sellRate( sR ) { }
};

using LatestBankQuotes = std::map< Bank, std::map< CcyPair, CcyPairQuote > >;

struct BankQuoteRate {
    Bank bank;
    Quote quote;
    double price;

    BankQuoteRate() = default;
    BankQuoteRate( const Bank &b, const Quote &q, const double &p ) : bank( b ), quote( q ), price( p ) { }
};

using BestCcyQuotes = std::map< CcyPair, BankQuoteRate >;

class QuoteManager {
public:
    void ProcessRecord( const std::vector< std::string > &record ) {
        if( record.size() != IncomingQuoteRecord::TOTALFIELDS ) {
            return;
        }

        Bank bank = record[ IncomingQuoteRecord::BANK ];
        CcyPair ccyPair = record[ IncomingQuoteRecord::CURRENCYPAIR ];
        double buyRate = atof( record[ IncomingQuoteRecord::BUYRATE ].c_str() );
        BankQuoteRate buyQuote( bank, Quote::BUY, buyRate );
        double sellRate = atof( record[ IncomingQuoteRecord::SELLRATE ].c_str() );
        BankQuoteRate sellQuote( bank, Quote::SELL, sellRate );

        RecordBankQuotes( latestBankQuotes, bank, ccyPair, buyRate, sellRate );
        UpdateQuote( highestBuyRates, ccyPair, buyQuote, SelectionStrategy::HIGHEST );
        UpdateQuote( lowestSellRates, ccyPair, sellQuote, SelectionStrategy::LOWEST );

        std::cout << "Best " << ccyPair << " Buy = " << highestBuyRates[ ccyPair ].price << " from " <<
        highestBuyRates[ ccyPair ].bank << std::endl;
        std::cout << "Best " << ccyPair << " Sell = " << lowestSellRates[ ccyPair ].price << " from " <<
        lowestSellRates[ ccyPair ].bank << std::endl;
    }

private:
    BestCcyQuotes highestBuyRates;
    BestCcyQuotes lowestSellRates;
    LatestBankQuotes latestBankQuotes;

    void RecordBankQuotes( LatestBankQuotes &bankQuotes, const Bank &bank, const CcyPair &ccyPair,
                           const double &buyRate, const double &sellRate ) {
        auto foundBank = bankQuotes.find( bank );
        if( foundBank == bankQuotes.end() ) {
            std::map< CcyPair, CcyPairQuote > tmp{ { std::make_pair( ccyPair, CcyPairQuote( ccyPair, buyRate, sellRate ) ) } };
            bankQuotes.insert( std::make_pair( bank, tmp ) );
        }
        else {
            auto foundBankCcyPair = foundBank->second.find( ccyPair );
            if( foundBankCcyPair == foundBank->second.end() ) {
                foundBank->second.insert( std::make_pair( ccyPair, CcyPairQuote( ccyPair, buyRate, sellRate ) ) );
            }
            else {
                bankQuotes[ bank ][ ccyPair ] = CcyPairQuote( ccyPair, buyRate, sellRate );
            }
        }
    }

    enum SelectionStrategy {
        HIGHEST, LOWEST
    };

    const BankQuoteRate GetBestQuoteFromHistory( const CcyPair &ccyPair, const Quote &quote, const SelectionStrategy &strategy ) {
        auto bankCcyPairItr = this->latestBankQuotes.begin();
        auto bestRate = ( strategy == SelectionStrategy::HIGHEST ? std::numeric_limits< double >::min() : std::numeric_limits< double >::max() );
        Bank bank;
        for( ; bankCcyPairItr != this->latestBankQuotes.end(); ++bankCcyPairItr ) {
            auto ccyPairFound = bankCcyPairItr->second.find( ccyPair );
            if( ccyPairFound == bankCcyPairItr->second.end() ) {
                continue;
            }
            switch( quote ) {
                case Quote::BUY:
                    if( bestRate < ccyPairFound->second.buyRate ) {
                        bestRate = ccyPairFound->second.buyRate;
                        bank = bankCcyPairItr->first;
                    }
                    break;
                case Quote::SELL:
                    if( bestRate > ccyPairFound->second.sellRate ){
                        bestRate = ccyPairFound->second.sellRate;
                        bank = bankCcyPairItr->first;
                    }
                    break;
            }
        }
        return( BankQuoteRate( bank, quote, bestRate ) );
    }

    const BankQuoteRate &UpdateQuote( BestCcyQuotes &quotes, const CcyPair &ccyPair, const BankQuoteRate &quote,
                                  const SelectionStrategy &strategy ) {
        auto foundQuote = quotes.find( ccyPair );
        if( foundQuote == quotes.end() ) {
            quotes.insert( std::make_pair( ccyPair, quote ) );
            // We now want to make sure there isn't a better quote
        }
        else {
            if( foundQuote->second.bank == quote.bank ) {
                BankQuoteRate bqr = GetBestQuoteFromHistory( ccyPair, quote.quote, strategy );
                quotes[ ccyPair ] = bqr;
            }
            else {
                switch( strategy ) {
                    case SelectionStrategy::HIGHEST:
                        if( foundQuote->second.price < quote.price )
                            quotes[ ccyPair ] = quote;
                        break;
                    case SelectionStrategy::LOWEST:
                        if( foundQuote->second.price > quote.price )
                            quotes[ ccyPair ] = quote;
                        break;
                }
            }
        }

        return ( quotes[ ccyPair ] );
    }
};

int main( int argc, char *argv[] ) {
    // Initialization
    //
    // In this part of the program you can perform any kind of
    // initialization routine before processing the stream
    // of data.

    std::string line;
    std::vector< std::string > quote;
    std::string item;
    QuoteManager quoteManager;
    while( std::getline( std::cin, line ) ) {
        if( !line.empty() ) {
            quote.clear();
            std::istringstream ss( line );
            while( std::getline( ss, item, '|' ) ) {
                quote.push_back( item );
            }

            quoteManager.ProcessRecord( quote );
        }
    }

    return 0;
}