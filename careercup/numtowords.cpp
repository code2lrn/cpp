//
// Created by Ranga on 2/14/17.
//

#include <iostream>
#include <array>
#include <algorithm>

class StringTrimmer {
public:
    static std::string Trim( const std::string &str ) {

        std::string trimmed = str.substr( str.find_first_not_of( ' ' ), str.find_last_not_of( ' ' ) );
        auto updatedEnd = std::unique( trimmed.begin(), trimmed.end(), []( const auto &ch1, const auto &ch2 ) { return ch1 == ' ' && ch1 == ch2; } );
        trimmed.erase( updatedEnd, trimmed.end() );

        return trimmed;
    }
};

class NumToWords {
public:

    static std::string Convert( int num ) {
        static const std::array< std::string, 4 > thousands{ "", "thousand", "million", "billion" };

        bool isNegative = num < 0;
        num = std::abs( num );
        unsigned thousandsFactor = 0;
        std::string numInWords;
        while( num > 0 ) {
            numInWords = NumToWords::ConvertInternal( num % 1000 ) + " " + thousands[ thousandsFactor++ ] + " " + numInWords;
            num = num / 1000;
        }

        numInWords = StringTrimmer::Trim( numInWords );
        return isNegative ? "-" + numInWords : numInWords;
    }

private:

    static std::string ConvertInternal( int num ) {
        static const std::array< std::string, 10 > ones  { "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
        static const std::array< std::string, 10 > teens { "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
        static const std::array< std::string, 10 > tens  { "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };

        std::string str;

        unsigned onesPlace = num % 10;
        unsigned tensPlace = ( num / 10 ) % 10;
        if( tensPlace == 1 ) {
            str = teens[ onesPlace ];
        }
        else {
            str = ones[ onesPlace ];
            str = tens[ tensPlace ] + " " + str;
        }

        unsigned hundredsPlace = ( num / 100 ) % 10;
        if( hundredsPlace > 0 ) {
            str = ones[ hundredsPlace ] + " hundred and " + str;
        }

        return str;
    }
};

int main( int argc, char *argv[] ) {

    int num;

    while( std::cin >> num ) {
        std::cout << NumToWords::Convert( num ) << std::endl;
    }

    return 0;
}
