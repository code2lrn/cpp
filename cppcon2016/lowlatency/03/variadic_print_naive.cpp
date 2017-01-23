#include <iostream>
#include <functional>

using namespace std;

template<class T>
void print(T && arg) {
    cout << sizeof( arg  )<< " ";
}

template<class T, class ... Ts>
void print(T && arg, Ts && ... args) {
    print( std::forward<T>(arg) );
    print( std::forward<Ts>(args)... );
}

int main() {
    print(3, "I love my teacher", 3.14159);
}