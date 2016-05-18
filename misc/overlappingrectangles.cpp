//
// Created by Ranga on 5/18/16.
//

#include <string>
#include <iostream>
#include <sstream>

class Rectangle {
public:
    Rectangle( int x, int y, unsigned width, unsigned height )
            : corner1( Coordinates( x, y ) ), corner2( Coordinates( x + width, y + height ) ) { }

    bool Overlaps( const Rectangle &other ) {

        if(    ( corner1.IsLeftOf( other.corner1 ) && corner2.IsLeftOf( other.corner1 ) ) // No Overlap; on the left
            || ( corner1.IsRightOf( other.corner2 ) && corner2.IsRightOf( other.corner2 ) ) // No Overlap; on the right
            || ( corner1.IsBelow( other.corner1 ) && corner2.IsRightOf( other.corner1 ) ) // No Overlap; this below the other
            || ( corner1.IsAbove( other.corner1 ) && corner1.IsAbove( other.corner2 ) ) ) {// No Overlap; this above the other
            return false;
        }

        return true;
    }

private:
    struct Coordinates {
        int x, y;
        Coordinates( int a, int b ) : x( a ), y( b ){ }
        Coordinates( Coordinates &&c ) {
            x = c.x;
            y = c.y;
        }

        bool IsLeftOf( const Coordinates &other )  const { return x < other.x; }
        bool IsRightOf( const Coordinates &other ) const { return x > other.x; }
        bool IsAbove( const Coordinates &other )   const { return y > other.y; }
        bool IsBelow( const Coordinates &other )   const { return y < other.y; }
    };

    Coordinates corner1, corner2;
};

int main( int argc, char *argv[] ) {

    std::string line;
    while( std::getline( std::cin, line ) ) {
        std::stringstream ss( line );
        int x1, y1, x2, y2;
        unsigned width1, height1, width2, height2;
        ss >> x1 >> y1 >> width1 >> height1 >> x2 >> y2 >> width2 >> height2;
        Rectangle r1{ x1, y1, width1, height1 }, r2{ x2, y2, width2, height2 };
        std::cout << std::boolalpha << r1.Overlaps( r2 ) << std::endl;
    }

    return 0;
}

