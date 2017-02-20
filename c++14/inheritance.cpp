//
// Created by Range on 2/18/17.
//

#include <iostream>

template< typename T >
class Base {
public:
    Base() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

protected:
    struct Foo {
        T x;
    };

    Foo a;
};

template< typename T >
class Derived : public Base< T > {
public:
    Derived() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    void DoSomething( const T &t ) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        (this->a).x = t;

        using Base< T >::Foo;
    }
};

int main( int argc, char *argv[] ) {

    Derived< int > d;
    d.DoSomething( 10 );

    return 0;
}

