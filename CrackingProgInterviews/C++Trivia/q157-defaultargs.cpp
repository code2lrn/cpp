//
// Created by Ranga on 6/25/16.
//

#include <iostream>

int i = 0;

int funcA( int i ) {
    return i;
}

int funcB( int j = funcA( i ) ) {
    return j;
}

int funcC() {
    i = 1;
    std::cout << funcB() << std::endl;
}

int main() {
    funcC();
    return 0;
}