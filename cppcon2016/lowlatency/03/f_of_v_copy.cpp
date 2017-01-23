#include <chrono>
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <cmath>
using namespace std;
using namespace std::chrono;
vector<double> f(vector<double> v) {
  transform(begin(v), end(v),
            begin(v), [](double x) {
    return sqrt(x);
  });
  return v;
}
template <class F, class ... Args>
  auto test(F f, Args && ... args) {
    auto pre = high_resolution_clock::now();
    auto res = f(std::forward<Args>(args)...);
    auto post = high_resolution_clock::now();
    return make_pair(res, post-pre);
  }
int main() {
  enum { N = 10'000'000 };
  vector<double> v(N);
  iota(begin(v), end(v), 1.0);
  auto res = test([v]() mutable {
      v = f(v);
      return v.back();
  });
  cout << "f(v) where v.size() == " << v.size() << " completed in " << duration_cast<microseconds>(res.second).count() << " us." << endl;
}