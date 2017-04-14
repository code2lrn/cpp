//
// Created by Ranga on 3/11/17.
//

#include <vector>
#include <iostream>
#include <algorithm>

std::vector< unsigned  > SieveOfEratosthenes( unsigned N ) {
    if( N == 1 ) {
        return {};
    }

    std::vector< std::pair< unsigned, bool > > sieve( N - 1 );
    unsigned num = 2;
    std::for_each( sieve.begin(), sieve.end(), [ &num ] ( auto &v ) { v = std::make_pair( num++, true ); } );
    for( auto it1 = sieve.begin(); it1 != sieve.end(); ++it1 ) {
        if( (*it1).second == false ) {
            continue;
        }

        std::for_each( it1 + 1, sieve.end(), [ &it1 ] ( auto &v ) {
            if( v.first % (*it1).first == 0 ) {
                v.second = false;
            }
        } );
    }

    std::vector< unsigned > primes;
    std::for_each( sieve.begin(), sieve.end(), [ &primes ]( const auto &i ){ if( i.second ) { primes.push_back( i.first ); } } );
    return primes;
}

std::vector< unsigned > GetPrimes( unsigned N ) {
    static unsigned maxN = 2;
    static std::vector< unsigned > cachedPrimes;

    std::vector< unsigned > output;
    if( N < 3 ) {
        return output;
    }

    if( maxN < N ) {
        for( unsigned i = maxN; i < N; ++i ) {
            if( i == 2 || i == 3 ) {
                cachedPrimes.push_back( i );
                continue;
            }

            if( i % 2 == 0 || i % 3 == 0 ) {
                continue;
            }

            bool isPrime = true;
            unsigned sqrtI = sqrt( i );
            for( unsigned j = 5; j <= sqrtI; j += 6 ) {
                if( i % j == 0 || i % ( j + 2 ) == 0 ) {
                    isPrime = false;
                    break;
                }
            }
            if( isPrime ) {
                cachedPrimes.push_back( i );
            }
        }
        maxN = N;
    }

    for( auto prime : cachedPrimes ) {
        if( prime < N ) {
            output.push_back( prime );
        }
        else {
            break;
        }
    }

    return output;
}

int main( int argc, char *argv[] ) {

    unsigned N = 16777214;
    //auto sot = SieveOfEratosthenes( N );
    std::cout << "run1\n";
    auto sot = GetPrimes( N );
    for( auto it1 = sot.begin(); it1 != sot.end(); ++it1 ) {
        auto required = N - *it1;
        auto found = std::lower_bound( it1, sot.end(), required );
        if( found != sot.end() && *found == required ) {
            std::cout << "Found " << *it1 << " and " << required << std::endl;
            break;
        }
    }
    std::cout << "run2\n";
    sot = GetPrimes( N );
    for( auto it1 = sot.begin(); it1 != sot.end(); ++it1 ) {
        auto required = N - *it1;
        auto found = std::lower_bound( it1, sot.end(), required );
        if( found != sot.end() && *found == required ) {
            std::cout << "Found " << *it1 << " and " << required << std::endl;
            break;
        }
    }
    return 0;
}