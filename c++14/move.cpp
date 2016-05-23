//
// Created by Ranga on 5/17/16.
//

#include <iostream>

struct Param {
    Param( int &i ) {
        std::cout << __PRETTY_FUNCTION__ << " called with " << i << std::endl;
        val = i;
    }
    Param( int &&i ) {
        std::cout << __PRETTY_FUNCTION__ << " called with " << i << std::endl;
        val = i;
    }
    Param( const Param &other ) {
        std::cout << __PRETTY_FUNCTION__ << " called with " << other.val << std::endl;
        val = other.val;
    }
    Param( const Param &&other ) {
        std::cout << __PRETTY_FUNCTION__ << " called with " << other.val << std::endl;
        val = other.val;
    }
    ~Param() {
        std::cout << __PRETTY_FUNCTION__ << " called for " << val << std::endl;
    }

private:
    int val;
};

Param GetAParam() {
    Param p1( 10 );
    return p1;
}

int main( int argc, char *argv[] ) {

    int i = 0;
    //Param p1( i ), p2( i + 1 );
    Param p3( GetAParam() );
    //Param p4( p3 );
    return 0;
}
