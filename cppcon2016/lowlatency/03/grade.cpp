#include <type_traits>
class exact{}; class floating_point{};
template <class T>
   constexpr T absolute(T val) { return val < 0? -val : val; }
template <class T> constexpr T threshold = static_cast<T>(0.000001);
template <class T>
  constexpr bool close_enough(T a, T b, exact){ return a==b; }
template <class T>
  constexpr bool close_enough(T a, T b, floating_point) {
    return absolute(a - b) <= threshold<T>;
  }
template <class T>
   constexpr bool close_enough(T a, T b) {
      return close_enough(a, b, std::conditional_t<
        std::is_floating_point<T>::value, floating_point, exact
      >{});
   }
//
//
//
class invalid_grade {};
class Grade {
public:
  using value_type = int;
private:
  value_type val;
  static constexpr value_type minval() {
    return 0;
  }
  static constexpr value_type maxval() {
    return 100;
  }
  static constexpr bool is_valid(value_type candidate) {
    return minval() <= candidate && candidate <= maxval();
  }
  static constexpr value_type validate(value_type candidate) {
    return is_valid(candidate)? candidate : throw invalid_grade{};
  }
public:
  constexpr value_type value() const noexcept {
    return val;
  }
  static constexpr value_type passing_grade() {
    return 60;
  }
  constexpr Grade() noexcept : val { minval() } {
  }
  constexpr Grade(value_type val) : val { validate(val) } {
  }
  constexpr bool operator==(const Grade &g) const noexcept {
    return close_enough(value(), g.value());
  }
  constexpr bool operator!=(const Grade &g) const noexcept {
    return !(*this == g);
  }
};
int main() {
  static constexpr int PASSING_GRADE = 60;
  static_assert(close_enough(PASSING_GRADE, Grade::passing_grade()),
                "...");
}