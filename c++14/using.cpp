//
// Created by Ranga on 6/23/16.
//

#include <iostream>

class Base {
protected:
    void func( char p ) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

public:
    void func( int p ) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

class Derived : public Base {
public:
    using Base::func;
};

int main( int argc, char *argv[] ) {
    Derived d;
    d.func( 10 );
    d.func( 'a' );
    return 0;
}
