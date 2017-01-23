#include <memory>
using namespace std;
static_assert(sizeof(double*)==sizeof(unique_ptr<double>),
              "...");
class X {
  ~X() = default;
  friend struct Y;
};
struct Y {
   void operator()(const X*p) { delete p; }
};
static_assert(sizeof(X*)==sizeof(unique_ptr<X,Y>), "...");
int main() {
    // X x; // no, X::~X() is private
    unique_ptr<X,Y> p{ new X }; // fine
}
