#include <memory>
#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <utility>
using namespace std;
using namespace std::chrono;
struct X {
   double denom;
   X(double denom) : denom{ denom } { // assert(denom)
   }
   double f(double num) const {
      return num / denom;
   }
};
template <class F, class ... Args>
auto test(F f, Args && ... args) {
   auto before = high_resolution_clock::now();
   auto res = f(std::forward<Args>(args)...);
   auto after = high_resolution_clock::now();
   return make_pair(res, after - before);
}
int main() {
   enum { N = 1'000'000 };
   vector<double> v(N);
   iota(begin(v), end(v), 1.0);
   { // raw pointer test
      X *p{ new X{ static_cast<double>(N) } };
      auto res = test([](auto first, auto last, const X *p) {
         return accumulate(first, last, 0.0, [&p](double so_far, double x) {
            return so_far + p->f(x);
         });
      }, begin(v), end(v), p);
      cout << "Raw pointer. Computed " << res.first << " in " << duration_cast<microseconds>(res.second).count() << " us." << endl;
      delete p;
   }
   { // unique_ptr test (naive)
      unique_ptr<X> p{ new X{ static_cast<double>(N) } };
      auto res = test([](auto first, auto last, const unique_ptr<X> &p) {
         return accumulate(first, last, 0.0, [&p](double so_far, double x) {
            return so_far + p->f(x);
         });
      }, begin(v), end(v), p);
      cout << "unique_ptr (naive). Computed " << res.first << " in " << duration_cast<microseconds>(res.second).count() << " us." << endl;
   }
   { // unique_ptr test (realistic)
      unique_ptr<X> p{ new X{ static_cast<double>(N) } };
      auto res = test([](auto first, auto last, const X *p) {
         return accumulate(first, last, 0.0, [&p](double so_far, double x) {
            return so_far + p->f(x);
         });
      }, begin(v), end(v), p.get());
      cout << "unique_ptr (realistic). Computed " << res.first << " in " << duration_cast<microseconds>(res.second).count() << " us." << endl;
   }
}