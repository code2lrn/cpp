//
// Created by Ranga on 5/11/16.
//

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using BoardContent = std::vector< std::vector< char > >;
using Positions = std::vector< std::pair< unsigned, unsigned > >;

class Piece {
public:
    Piece( unsigned r, unsigned c ) : rows( r ), cols( c ) { }

    virtual Positions NextPossibleMoves( unsigned r, unsigned c ) = 0;

protected:
    unsigned rows, cols;

    bool IsValidPosition( int x, int y ) {
        return 0 <= x && x < rows && 0 <= y && y < cols;
    }
};

class Knight : public Piece {
public:
    Knight( unsigned r, unsigned c ) : Piece( r, c ) { }

    virtual Positions NextPossibleMoves( unsigned r, unsigned c ) override {
        Positions moves;

        int possibleDirections[8][2] = { { 2,  -1 }, // Right & Up
                                         { 2,  1 },  // Right & Down and so on
                                         { -2, -1 },
                                         { -2, 1 },
                                         { 1,  -2 },
                                         { 1,  2 },
                                         { -1, -2 },
                                         { -1, 2 } };
        for( auto i = 0; i < 8; ++i ) {
            auto newR = r + possibleDirections[ i ][ 0 ];
            auto newC = c + possibleDirections[ i ][ 1 ];
            if( IsValidPosition( newR, newC ) ) {
                moves.push_back( std::make_pair( newR, newC ) );
            }
        }
        return moves;
    }
};

class Bishop : public Piece {
public:
    Bishop( unsigned r, unsigned c ) : Piece( r, c ) { }

    virtual Positions NextPossibleMoves( unsigned r, unsigned c ) override {
        Positions moves;

        for( auto i = 0; i < this->rows; ++i ) {
            for( auto j = 0; j < this->cols; ++j ) {
                if( i != j || ( i == r && j == c ) )
                    continue;
                auto rowBack = -1 * i + r, rowFront = i + r;
                auto colBack = -1 * j + c, colFront = j + c;
                if( IsValidPosition( rowBack, colBack ) ) {
                    moves.push_back( std::make_pair( rowBack, colBack ) );
                }
                if( IsValidPosition( rowBack, colFront ) ) {
                    moves.push_back( std::make_pair( rowBack, colFront ) );
                }
                if( IsValidPosition( rowFront, colBack ) ) {
                    moves.push_back( std::make_pair( rowFront, colBack ) );
                }
                if( IsValidPosition( rowFront, colFront ) ) {
                    moves.push_back( std::make_pair( rowFront, colFront ) );
                }
            }
        }
        return moves;
    }
};

class Board {
public:
    Board( const BoardContent &boardContent, unsigned rows, unsigned cols, std::string piece, unsigned phoneNumLength, const std::vector< unsigned > &validStartingDigits ) {
        this->boardContent = boardContent;
        this->rows = rows;
        this->cols = cols;
        if( piece == "knight" ) {
            this->piece = new Knight( this->rows, this->cols );
        }
        else if( piece == "bishop" ) {
            this->piece = new Bishop( this->rows, this->cols );
        }
        this->phoneNumLength = phoneNumLength;
        this->validStartingDigits = validStartingDigits;
    }

    unsigned GetPossiblePhoneNumbers() {
        std::vector< std::string > phoneNumbers;
        for( auto r = 0; r < this->rows; ++r ) {
            for( auto c = 0; c < this->cols; ++c ) {
                std::string phoneNumber;
                GeneratePhoneNumbers( r, c, phoneNumber, phoneNumbers );
            }
        }
        std::sort( phoneNumbers.begin(), phoneNumbers.end() );
        std::vector< std::string > uniquePhoneNumbers;
        std::unique_copy( phoneNumbers.begin(), phoneNumbers.end(), back_inserter( uniquePhoneNumbers ) );
        //std::copy( uniquePhoneNumbers.begin(), uniquePhoneNumbers.end(), std::ostream_iterator< std::string >( std::cout, ", " ) );

        return uniquePhoneNumbers.size();
    }

    void GeneratePhoneNumbers( unsigned r, unsigned c, std::string phoneNumber, std::vector< std::string > &phoneNumbers ) {

        if( phoneNumber.length() >= this->phoneNumLength ) {
            return;
        }

        auto ch = this->boardContent[ r ][ c ];
        if( !isdigit( ch ) ) {
            return;
        }

        auto goodChar = phoneNumber.length() != 0
                        || ( std::find( this->validStartingDigits.begin(), this->validStartingDigits.end(), (unsigned)(ch - '0') ) != this->validStartingDigits.end() );
        if( isdigit( ch ) && goodChar ) {
            phoneNumber.push_back( ch );
        }

        if( phoneNumber.length() == this->phoneNumLength ) {
            phoneNumbers.push_back( phoneNumber );
            return;
        }

        Positions possibleMoves = piece->NextPossibleMoves( r, c );
        for( auto i = 0; i < possibleMoves.size(); ++i ) {
            GeneratePhoneNumbers( possibleMoves[ i ].first, possibleMoves[ i ].second, phoneNumber, phoneNumbers );
        }
    }

private:
    BoardContent boardContent;
    unsigned    rows, cols, phoneNumLength;
    Piece       *piece;
    std::vector< unsigned > validStartingDigits;
};

int main( int argc, char *argv[] ) {
    // knight or bishop
    std::string piece;
    std::cin >> piece;

    if( piece != "knight" && piece != "bishop" ) {
        return 1;
    }

    unsigned phoneNumLength;
    std::cin >> phoneNumLength;

    // All valid starting digits from a single line
    std::vector< unsigned > validStartingDigits;
    std::string startingDigitsString;
    std::getline( std::cin, startingDigitsString ); // Doing this twice to consume the newline in the stream
    std::getline( std::cin, startingDigitsString );
    std::stringstream ss( startingDigitsString );
    unsigned u;
    while( ss >> u ) {
        validStartingDigits.push_back( u );
    }

    // Rows & Cols
    unsigned rows, cols;
    std::cin >> rows >> cols;

    // Board
    BoardContent boardContent;
    for( auto i = 0; i < rows; ++i ) {
        std::vector< char > row;
        for( auto j = 0; j < cols; ++j ) {
            char ch;
            std::cin >> ch;
            row.push_back( ch );
        }
        boardContent.push_back( row );
    }

    Board b{ boardContent, rows, cols, piece, phoneNumLength, validStartingDigits };
    std::cout << b.GetPossiblePhoneNumbers() << std::endl;

    return 0;
}