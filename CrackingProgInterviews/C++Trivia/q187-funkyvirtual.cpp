//
// Created by Ranga on 6/25/16.
//

#include <iostream>

struct Base {
    virtual void func() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

struct Derived : Base {
private:
    void func() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

int main() {
    Derived d;
    Base *b = &d;
    b->func();
    return 0;
}