#include <memory>
#include <cstdio>

class X {
    int val;
public:
    X(int val) : val{val} {
    }

    int f(int n) const {
        return n + val;
    }
};

auto f(std::unique_ptr<X> p) {
    int arr[]{2, 3, 5, 7, 11};
    int sum = 0;
    for (auto n : arr)
        sum += p->f(n);
    return sum;
}

int main() {
    std::printf("%d", f(std::unique_ptr<X>{new X{3}}));
}