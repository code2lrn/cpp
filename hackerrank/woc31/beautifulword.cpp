//
// Created by Ranga on 4/13/17.
//

#include <algorithm>
#include <iostream>

int main(int argc, char *argv[] ) {

    std::string str;
    std::cin >> str;
    auto isBeautiful = true;
    auto IsConflict = [] ( const char a, const char b ) {
        return a == b || ( ( a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u' || a == 'y' ) && ( b == 'a' || b == 'e' || b == 'i' || b == 'o' || b == 'u' || b == 'y' ) );
    };
    for( auto itr = str.begin() + 1; itr != str.end(); ++itr ) {
        auto prevCh = *( itr - 1 ), ch = *itr;
        if( IsConflict( prevCh, ch ) ) {
            isBeautiful = false;
            break;
        }
    }

    //std::cout << str << " is" << ( isBeautiful ? "" : " NOT" ) << " a beautiful word\n";
    std::cout << ( isBeautiful ? "Yes" : "No" ) << std::endl;
    return 0;
}