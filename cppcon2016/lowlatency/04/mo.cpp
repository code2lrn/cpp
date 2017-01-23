//
// Created by Ranga on 9/18/16.
//

struct B {
    int shared;

    B(int init = {}) : shared{init} {
    }
};

struct B0 : virtual B {
    int f() const { return shared + 1; }
};

struct B1 : virtual B {
    int g() const { return shared + 2; }
};

struct D : B0, B1 {
    D() : B{2} {}
};

#include <iostream>

int main() {
    using namespace std;
    cout << "sizeof B : " << sizeof(B) << endl;
    cout << "sizeof B0 : " << sizeof(B0) << endl; // <--
    cout << "sizeof B1 : " << sizeof(B1) << endl; // <--
    cout << "sizeof D : " << sizeof(D) << endl;
}
