//
// Created by Ranga on 9/18/16.
//

#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <functional>
#include "highrestimer.h"
using namespace std;

int main() {
    enum { N = 100'000'000 };
    vector< double > v(N);
    iota( begin( v ), end( v ), 1 );
    auto run1 = HighResTimer( []( vector< double > vd ) { transform( begin( vd ), end( vd ), begin( vd ), []( double d ){ return sqrt( d ); } ); return vd.back(); }, v );
    std::cout << "That took " << PrintMicroSecs( run1.second ) << endl;
    auto run2 = HighResTimer( []( vector< double > &vd ) { transform( begin( vd ), end( vd ), begin( vd ), []( double d ){ return sqrt( d ); } ); return vd.back(); }, std::ref( v ) );
    std::cout << "That took " << PrintMicroSecs( run2.second ) << endl;
    return 0;
}

