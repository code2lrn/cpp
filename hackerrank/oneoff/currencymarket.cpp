//
// Created by Ranga on 5/14/16.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

/*
 * Logic:
 *      The program will remember:
 *      A. Only the LATEST Buy & Sell values for every Currency Pair submitted by each Bank
 *      B. An up to date recollection of the best Buy & Sell rates per Currency Pair as of the last input record
 *
 *      For every input record received, these 4 steps will happen:
 *      1. Parse input record in individual fields
 *      2. Save the latest Bank=>( CCY Pair=>Buy & Sell ) mapping
 *      3. Update
 *          3.a Best Buy Price: CCY Pair => { Bank, Rate }
 *          3.b Best Sell Price: CCY Pair => { Bank, Rate }
 *      4. Printing the required output
 */

enum IncomingQuoteRecord {
    TIMESTAMPID = 0, CURRENCYPAIR, BANK, BUYRATE, SELLRATE, TOTALFIELDS
};

/*
 * Class: QuoteManager
 *
 * The following class encapsulates the data structures & algorithm
 * required to implement the above requirement.
 */

class QuoteManager {
public:
    void ProcessRecord( const std::vector< std::string > &record ) {
        if( record.size() != IncomingQuoteRecord::TOTALFIELDS ) {
            return;
        }

        // Step 1
        Bank bank = record[ IncomingQuoteRecord::BANK ];
        CcyPair ccyPair = record[ IncomingQuoteRecord::CURRENCYPAIR ];
        double buyRate = atof( record[ IncomingQuoteRecord::BUYRATE ].c_str() );
        BankQuoteRate buyQuote( bank, BuyOrSell::BUY, buyRate );
        double sellRate = atof( record[ IncomingQuoteRecord::SELLRATE ].c_str() );
        BankQuoteRate sellQuote( bank, BuyOrSell::SELL, sellRate );

        // Step 2 -- For the future: It is imperative that function be executed before UpdateBestQuote()
        RecordBankQuotes( latestBankQuotes, bank, ccyPair, buyRate, sellRate );

        // Step 3
        auto &bestBuyQuote  = UpdateQuote( highestBuyRates, ccyPair, buyQuote, SelectionStrategy::HIGHEST );
        auto &bestSellQuote = UpdateQuote( lowestSellRates, ccyPair, sellQuote, SelectionStrategy::LOWEST );

        // Step 4
        std::cout << "Best " << ccyPair << " Buy = " << bestBuyQuote.price << " from " << bestBuyQuote.bank << std::endl;
        std::cout << "Best " << ccyPair << " Sell = " << bestSellQuote.price << " from " << bestSellQuote.bank << std::endl;
    }

private:

    // ------- Private Enumerations/Type Definitions --------
    enum BuyOrSell { BUY, SELL };
    using Bank    = std::string;
    using CcyPair = std::string;

    struct BankQuoteRate {
        Bank bank;
        BuyOrSell buyOrSell;
        double price;

        BankQuoteRate() = default;
        BankQuoteRate( const Bank &b, const BuyOrSell &bos, const double &p ) : bank( b ), buyOrSell( bos ), price( p ) { }
    };
    using BestCcyQuotes = std::map< CcyPair, BankQuoteRate >;
    // ------ END Private Enumerations/Type Definitions -----

    // Used to keep track of the best Buy Rates. Pls refer to step 3a from above
    BestCcyQuotes highestBuyRates;
    // Used to keep track of the best Sell Rates. Pls refer to step 3b from above
    BestCcyQuotes lowestSellRates;

    // ------- Private Enumerations/Type Definitions --------
    struct CcyPairQuote {
        CcyPair pair;
        double buyRate;
        double sellRate;

        CcyPairQuote() = default;
        CcyPairQuote( const CcyPair &cp, const double &bR, const double &sR ) : pair( cp ), buyRate( bR ), sellRate( sR ) { }
    };
    using LatestBankQuotes = std::map< Bank, std::map< CcyPair, CcyPairQuote > >;
    // ------ END Private Enumerations/Type Definitions -----

    // Used to keep track of every bank's latest rates for a currency pair. Pls refer to step 2 from above
    LatestBankQuotes latestBankQuotes;

    /*
     * Helper function to keep the latestBankQuotes refreshed/populated
     */

    void RecordBankQuotes( LatestBankQuotes &bankQuotes, const Bank &bank, const CcyPair &ccyPair, const double &buyRate, const double &sellRate ) {
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

    /*
     * Helper function that look @ latest rates submitted by every bank for a particular currency pair
     * Returns: Depending on what we are looking for, the best Buy or Sell rate
     */
    const BankQuoteRate GetBestQuoteFromHistory( const CcyPair &ccyPair, const BuyOrSell &quote, const SelectionStrategy &strategy ) {
        auto bankCcyPairItr = this->latestBankQuotes.begin();
        auto bestRate = ( strategy == SelectionStrategy::HIGHEST ? std::numeric_limits< double >::min() : std::numeric_limits< double >::max() );
        Bank bank;
        for( ; bankCcyPairItr != this->latestBankQuotes.end(); ++bankCcyPairItr ) {
            auto ccyPairFound = bankCcyPairItr->second.find( ccyPair );
            if( ccyPairFound == bankCcyPairItr->second.end() ) {
                continue;
            }
            switch( quote ) {
                case BuyOrSell::BUY:
                    if( bestRate < ccyPairFound->second.buyRate ) {
                        bestRate = ccyPairFound->second.buyRate;
                        bank = bankCcyPairItr->first;
                    }
                    break;
                case BuyOrSell::SELL:
                    if( bestRate > ccyPairFound->second.sellRate ){
                        bestRate = ccyPairFound->second.sellRate;
                        bank = bankCcyPairItr->first;
                    }
                    break;
            }
        }
        // Defensive Error Handling missing
        // This will be required in case order of function invocation is changed in ProcessRecord()
        return( BankQuoteRate( bank, quote, bestRate ) );
    }

    /*
     * Helper function to maintain, both, the best Buy & Sell rates
     * Returns: a reference to the best rate for a given CCY Pair & BuyOrSell
     */
    const BankQuoteRate& UpdateQuote( BestCcyQuotes &quotes, const CcyPair &ccyPair, const BankQuoteRate &quote, const SelectionStrategy &strategy ) {
        auto foundQuote = quotes.find( ccyPair );
        if( foundQuote == quotes.end() ) {
            quotes.insert( std::make_pair( ccyPair, quote ) );
        }
        else {
            if( foundQuote->second.bank == quote.bank ) {
                quotes[ ccyPair ] = GetBestQuoteFromHistory( ccyPair, quote.buyOrSell, strategy );
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
        return quotes[ ccyPair ];
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

    /*
     * FUTURE Improvements that will/may be required:
     * 1. Error/Exception Handling - This WILL be required once we determine strategy to handle bad records/missing data
     * 2. Thread Safety - The QuoteManager's internal data structures are not locked while being updated.
     *                    Inconsistent reads are likely to occur in a multi-threaded environment
     * 3. Efficiency - After profiling with a larger production sample, we could
     *                 a) Use custom allocators if we are spending most time in memory allocation
     *                 b) Choose an alternate implementation for maintaining QuoteManager's state. Possibly an
     *                      implementation that keeps track of input records and provides abstract interface from a
     *                      Currency Pair or Bank point of view when required
     * 4. QuoteManager should probably be a singleton or at least be able to share its data structures if required
     *      in other parts of the program. All of the QuoteManager's internal state can be moved to a separate class
     */

    return 0;
}