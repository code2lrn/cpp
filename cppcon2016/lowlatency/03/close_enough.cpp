#include <type_traits>
#include <memory>

class exact {
};

class floating_point {
};

template<class T>
constexpr T absolute(T val) { return val < 0 ? -val : val; }

template<class T> constexpr T threshold = static_cast<T>(0.000001);

template<class T>
constexpr bool close_enough(T a, T b, exact) { return a == b; }

template<class T>
constexpr bool close_enough(T a, T b, floating_point) {
    return absolute(a - b) <= threshold<T>;
}

template<class T>
constexpr bool close_enough(T a, T b) {
    return close_enough(a, b, std::conditional_t<
            std::is_floating_point<T>::value, floating_point, exact
    >{});
}

int main() {
    static_assert(sizeof(double *) == sizeof(std::unique_ptr<double>), "...");
    static_assert(close_enough(3, 3), "...");
    static_assert(!close_enough(3.1, 3.0), "...");
    static_assert(close_enough(3.000000000001, 3.0), "...");
}
