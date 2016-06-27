//
// Created by Ranga on 6/25/16.
//

struct A {
    int a;
};

struct B {
    int b;
    static int si;
    enum { e } ;
};

struct C : B, virtual A {
};

struct D : B, virtual A {
};

struct E : C, D{
};

int main() {
    E *e = new E;

    e->a = 10; // works because "A" is inherited virtually
    //e->b = 10; // ambiguous request
    //e->si = 10; // The book is wrong; B::si has to be defined before using
    const int i = e->e;
    return 0;
}