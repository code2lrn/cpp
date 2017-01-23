#include <iostream>
using namespace std;
template <class T>
void printsz(const T &arg) {
   cout << sizeof arg << ' ';
}
template <class T, class ... Ts>
void printsz(const T &arg, Ts ... args) {
   printsz(arg);
   printsz(args...);
}
int main() {
   printsz(3, "I love my teacher", 3.14159);
}
