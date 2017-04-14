// Program to print all permutations of a string in sorted order.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cmath>

std::string NumToBase26( int num ) {
    std::string base26;
    char digitChars[] = "zabcdefghijklmnopqrstuvwxy";
    while( true ) {
        base26 += digitChars[ num % strlen( digitChars ) ];
        if( num > 26 ) {
            num -= 26;
        }
        else {
            break;
        }
    }

    return base26;
}

std::string NumToBase26Alternate( int num ) {
    std::string base26;
    char digitChars[] = "abcdefghijklmnopqrstuvwxyz";
    while( true ) {
        auto rem = num % strlen( digitChars );
        base26 = digitChars[ rem ] + base26;
        num /= 26;
        if( num == 0 ) {
            break;
        }
    }

    return base26;
}


// Driver program to test above function
int main()
{
    //char str[] = "abc";
    //sortedPermutations( str );
    unsigned num = 54;
    std::cout << NumToBase26( num ) << " " << NumToBase26Alternate( num ) << std::endl;
    return 0;
}


