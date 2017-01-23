#include <type_traits>
template <class T> constexpr T absolute(T val) {
   return val < 0? -val : val;
}
template <class T>
   constexpr T threshold = static_cast<T>(0.000001);
template <class T>
   std::enable_if_t<std::is_floating_point_v<T>, T>
      constexpr close_enough(T a, T b) {
         return absolute(a - b) <= threshold<T>;
      }
template <class T>
   std::enable_if_t<!std::is_floating_point_v<T>, T>
      constexpr close_enough(T a, T b) {
         return a==b;
      }
int main() {
   static_assert(close_enough(3,3), "...");
   static_assert(!close_enough(3.1,3.0), "...");
   static_assert(close_enough(3.000000000001,3.0), "...");
}
