#include <cstdio>
template <class T>
  constexpr T sum(T arg) {
    return arg;
  }
template <class T, class ... Ts>
  constexpr auto sum(T arg, Ts ... args) {
     return arg + sum(args...);
  }
int main() {
  constexpr auto result = sum(2,3,5,7,11,10);
  static_assert( result == 40, "Math gone wrong" );
  std::printf("%d", result);
}