#include <memory>
#include <cstdio>
int main() {
  using namespace std;
  auto p = unique_ptr<int>{ new int{ 3 }};
  printf("%d", *p);
}