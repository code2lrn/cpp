#include <cstddef> // std::size_t
template <class T, std::size_t N>
class Table {
public:
   using value_type = T;
   using size_type = std::size_t;
private:
   value_type vals[N];
public:
   constexpr Table() : vals{ {} }
   {
   }
   constexpr const value_type& operator[](size_type n) const {
      return vals[n];
   }
   constexpr value_type& operator[](size_type n) {
      return vals[n];
   }
};
class Zut {};
constexpr unsigned long long facto(int n) {
   return n < 0 ? throw Zut{} : n == 0 ? 1ULL : n * facto(n - 1);
}
template <std::size_t N>
constexpr auto generate_table() {
   Table<unsigned long long, N> res;
   for (std::size_t i = 0; i != N; ++i)
      res[i] = facto(i);
   return res;
}
template <class T, std::size_t N>
constexpr auto price_is_right(const Table<T, N> &tab, const T &val) {
   // precondition : tab is sorted
   for (std::size_t i = 0; i != N; ++i)
      if (tab[i] == val || (i != N - 1 && tab[i + 1] > val))
         return i;
   return N;
}
int main() {
   constexpr const auto factorials = generate_table<20>();
   constexpr const auto n = price_is_right(factorials, 120ULL);
   static_assert(n == 5, "Suspect...");
}