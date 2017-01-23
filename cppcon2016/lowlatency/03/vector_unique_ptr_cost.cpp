#include <vector>
#include <memory>
#include <iostream>
#include <chrono>
#include "highrestimer.h"
#include <iostream>

using namespace std;

vector<int*> f(vector<int*> v) {
   vector<int*> w;
   w.reserve(v.size());
   for (auto & p : v) {
      w.push_back(p); // two MOV + push_back code
      p = {};         // if we count this one
   }
   return w;
}
vector<unique_ptr<int>> f(vector<unique_ptr<int>> v) {
   vector<unique_ptr<int>> w;
   w.reserve(v.size());
   for (auto & p : v)
      w.push_back(std::move(p)); // three MOV + push_back...
   return w;
}

int main() {
   enum { N = 1'000'000 };
   {
      vector<int *> v;
      for (int i = 0; i < N; ++i)
         v.push_back(new int{ i });
      auto res = HighResTimer([&v] { v = f(std::move(v)); return *v.back(); });
      cout << "vector<int*>\n\tGot " << res.first << " in "
         << duration_cast<microseconds>(res.second).count() << " us." << endl;
      for (auto p : v) delete p;
   }
   {
      vector<unique_ptr<int>> v;
      for (int i = 0; i < N; ++i)
         v.push_back(make_unique<int>(i));
      auto res = HighResTimer([&v] { v = f(std::move(v)); return *v.back(); });
      cout << "vector<unique_ptr<int>>\n\tGot " << res.first << " in "
         << duration_cast<microseconds>(res.second).count() << " us." << endl;
   }
}
