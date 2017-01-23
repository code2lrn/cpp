#include <type_traits>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>

class implicit {};
class text_dest {};
class text_text {};
class general {};

template <class>
struct is_text : std::false_type {
};
template <class C>
struct is_text<std::basic_string<C>> : std::true_type {
};
template <class C>
struct is_text<const std::basic_string<C>&> : std::true_type {
};
template <class C>
struct is_text<std::basic_string<C>&> : std::true_type {
};

template <class D, class S>
struct conv_traits {
   using type = std::conditional_t<
      std::is_same<D, S>::value || std::is_convertible<S, D>::value,
      implicit,
      std::conditional_t<
         is_text<D>::value,
         std::conditional_t<
            is_text<S>::value,
            text_text,
            text_dest
         >,
         general
      >
   >;
};

template <class D, class S>
using conv_traits_t = typename conv_traits<D, S>::type;


template <class D, class S>
D lexical_cast(S &&src, general) {
   std::stringstream sstr;
   sstr << src;
   D dest;
   sstr >> dest;
   return dest;
}
template <class D, class S>
D lexical_cast(S &&src, text_dest) {
   using value_type = typename D::value_type;
   std::basic_stringstream<value_type> sstr;
   sstr << src;
   return sstr.str();
}
template <class D, class S>
D lexical_cast(S &&src, text_text) {
   return D(begin(src), end(src));
}
template <class D, class S>
D lexical_cast(S &&src, implicit) {
   return std::forward<S>(src);
}

//#include <iostream>
//template <class T, class U>
//   void diag () {
//      using namespace std;
//      cout << typeid(T).name() << " <-- \n\t" << typeid(U).name() << endl;
//      cout << "\tSame type? " << is_same<T,U>::value << endl;
//      cout << "\t" << typeid(conv_traits<T, U>::type()).name() << endl;
//   }

template <class D, class S>
D lexical_cast(S &&src) {
   //diag<D, S>();
   return lexical_cast<D, S>(std::forward<S>(src), conv_traits_t<D, S>{});
}
#include <iostream> 
using namespace std;

class X {};
istream& operator >> (istream &is, X&) {
   return is;
}
ostream& operator<<(ostream &os, const X&) {
   return os;
}

struct Y {
   Y() = default;
   Y(const X&) {};
};
istream& operator >> (istream &is, Y&) {
   return is;
}
ostream& operator<<(ostream &os, const Y&) {
   return os;
}

int main() {
   string s = "3";
   auto i = lexical_cast<int>(s);
   s = lexical_cast<string>(i);
   s = lexical_cast<string>(s);
   auto ws = lexical_cast<wstring>(s);
   X x;
   Y y;
   y = lexical_cast<Y>(x);
   x = lexical_cast<X>(y);
}