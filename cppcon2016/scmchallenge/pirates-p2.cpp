//
// Created by Ranga on 9/18/16.
//

/*

Once you have accessed the secret cove, the next step is to unlock a safe. This requires understanding the safe's combination. Since C++ Pirates are more clever than your average pirate, the trick is not really to decode what sequence of numbers is required to unlock the safe, but to find a way to ensure all three outputs in main() below give precisely the same output, given that all three values passed to trick are integers found inclusively between 0 and 9 (you are not expected to validate these inputs).

*/

#include <string>
#include <iostream>
#include <tuple>
#include <sstream>

using namespace std;

struct combination {
    int first, second, third;
    constexpr combination( int f, int s, int t ) noexcept : first( f ), second( s ), third( t ) { }
    constexpr bool operator ==( const combination &c ) const noexcept { return first == c.first && second == c.second && third == c.third; }
    constexpr bool operator !=( const combination &c ) const noexcept { return *this == c; }
};

ostream& operator <<( ostream &out, const combination &c ) {
    out << c.first << c.second << c.third << endl;
    return out;
}

// ===============================================



// ===============================================

int main() {
    string str = { 1, 2, 3};
    cout << str << endl;
    //string      str_comb      = trick( 1, 2, 3 );
    //int         int_comb      = trick( 1, 2, 3 );
    //combination comb_comb     = trick( 1, 2, 3 );

    //cout << str_comb << endl;
    //cout << int_comb << endl;
    //cout << comb_comb << endl;
    return 0;
}