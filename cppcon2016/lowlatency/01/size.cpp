//
// Created by Ranga on 9/17/16.
//

#include <iostream>

template <class T, std::size_t N>
constexpr
std::size_t csize(const T (&)[N]) {
    return N;
}

int main( ) {
    // classic array size trick
    int arr[] { 2,3,5,7,11 };
    enum { N = sizeof(arr) / sizeof(arr[0]) };
    // C++11 is cool

    std::cout << "Size old is " << N << ". New way is " << csize( arr ) << std::endl;
}
