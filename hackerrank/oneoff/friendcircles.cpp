//
// Created by Ranga on 5/9/16.
//

#include <vector>
#include <string>
#include <iostream>

using MatrixInput = std::vector< std::string >;

class Matrix {
public:
    Matrix( int N, const MatrixInput &input ) {
        this->N = N;
        data = new int *[N];
        for( auto i = 0; i < N; ++i ) {
            data[ i ] = new int[N];
            for( auto j = 0; j < N; ++j ) {
                data[ i ][ j ] = input[ i ][ j ] == 'Y';
            }
        }
    }

    Matrix( int N, int initValue ) {
        this->N = N;
        data = new int *[N];
        for( auto i = 0; i < N; ++i ) {
            data[ i ] = new int[N];
            for( auto j = 0; j < N; ++j ) {
                data[ i ][ j ] = initValue;
            }
        }
    }

    const int operator()( int x, int y ) const {
        return data[ x ][ y ];
    }

    int &operator()( int x, int y ) {
        return data[ x ][ y ];
    }

private:
    int N;
    int **data;
};

void MarkFriends( int N, const Matrix &friends, std::vector< bool > &visited, int row ) {
    for( auto i = 0; i < N; ++i ) {
        if( !visited[ i ] && i != row && friends( row, i ) == 1 ) {
            visited[ i ] = true;
            MarkFriends( N, friends, visited, i );
        }
    }
}

int GetFriendCircles( int N, const Matrix &friends ) {
    int circles = 0;

    std::vector< bool > visited( N, false );
    for( auto i = 0; i < N; ++i ){
        if( !visited[ i ] ) {
            circles++;
            visited[ i ] = true;
            MarkFriends( N, friends, visited, i );
        }
    }

    return circles;
}

int main( int argc, char *arv[] ) {
    int N;
    std:
    std::cin >> N;
    MatrixInput inputMatrix;
    for( auto i = 0; i < N; ++i ) {
        std::string line;
        std::cin >> line;
        inputMatrix.push_back( line );
    }
    Matrix friends( N, inputMatrix ), traversed( N, 0 );

    auto numCircles = GetFriendCircles( N, friends );
    std::cout << "The number of circles is " << numCircles << std::endl;

    return 0;
}
