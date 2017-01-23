#include <memory>
using namespace std;
class X {
   ~X() = default; // private
public:
   void destroy() const { delete this; }
   // ...
};
void destroyer(const X *p) { if (p) p->destroy(); }
// ...
int main() {
   // decltype(&destroyer) is void(*)(const X*)
   unique_ptr<X, decltype(&destroyer)> p{
      new X, destroyer
   };
   static_assert(sizeof p > sizeof(X*), "...");
   // ...
}
