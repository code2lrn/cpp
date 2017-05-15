//
// Created by Ranga on 5/15/17.
//

#include <initializer_list>
#include <string>
#include <vector>
#include <set>
#include <tuple>
#include <sstream>
#include <set>
#include <algorithm>
#include <iostream>
#include <iterator>

class Logins {
public:
    Logins( const std::initializer_list< std::string > &logins ) {
        int i = 0;
        std::string priorDate;
        std::set< int > priorCustomerIds;
        for( auto login : logins ) {
            std::string date;
            std::set< int > customerIds;
            std::tie( date, customerIds ) = ParseLoginInfo( login );
            ++i;

            if( i != 1 ) {
                std::set< int > repeatCustomerIds;
                std::set_intersection( priorCustomerIds.begin(), priorCustomerIds.end(), customerIds.begin(), customerIds.end(),
                                       std::inserter( repeatCustomerIds, repeatCustomerIds.end() ) );
                repeatCustLogins.push_back( std::make_pair( priorDate, repeatCustomerIds ) );
            }
            priorDate = date;
            priorCustomerIds = customerIds;

            if( i == logins.size() ) {
                repeatCustLogins.push_back( std::make_pair( date, customerIds ) );
            }
        }
    }

    void PrintRepeatCustomers( const int thresholdDays ) {
        std::cout << "All repeat customers:\n";
        for( auto p : repeatCustLogins ) {
            std::cout << p.first << ": ";
            std::copy( p.second.begin(), p.second.end(), std::ostream_iterator< int >( std::cout, " " ) );
            std::cout << std::endl;
        }

        std::cout << "Customers for " << thresholdDays << " consecutive days:\n";
        for( int j = thresholdDays - 1; j < repeatCustLogins.size(); ++j ) {
            std::set< int > result{ repeatCustLogins[ j ].second };
            for( int i = j - 1; i > j - thresholdDays; --i ) {
                std::set< int > tmp;
                std::set_intersection( result.begin(), result.end(),
                                       repeatCustLogins[ i ].second.begin(), repeatCustLogins[ i ].second.end(),
                                       std::inserter( tmp, tmp.end() ) );
                result = tmp;
            }
            std::cout << repeatCustLogins[ j ].first << ": ";
            std::copy( result.begin(), result.end(), std::ostream_iterator< int >( std::cout, " " ) );
            std::cout << std::endl;
        }
    }

private:
    std::vector< std::pair< std::string, std::set< int > > > repeatCustLogins;

    std::pair< std::string, std::set< int > > ParseLoginInfo( const std::string &login ) {
        std::stringstream ss( login );
        std::string date;
        std::set< int > customerIds;
        ss >> date;
        int customerId;
        while( ss >> customerId )
            customerIds.insert( customerId );

        return std::make_pair( date, customerIds );
    }
};

int main( int argc, char *argv[] ) {

    Logins l{ "0501 101 102 103", "0502 102 104 105", "0503 102 103 104", "0504 102 103 104 105", "0505 105 104 103" };
    l.PrintRepeatCustomers( 2 );
    return 0;
}