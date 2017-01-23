#include <memory>
#include <cstdio>

int main() {
    using namespace std;
    auto p = make_unique<int>(3);
    printf("%d", *p);
}