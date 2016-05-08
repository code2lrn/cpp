//
// Created by Ranga on 5/7/16.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <iterator>

int main( int argc, char *argv[] ) {

    std::cout << "Enter the text, type \"quit\" to stop:\n";
    std::map< std::string, std::vector< std::string > > anagrams;

    while(true) {
        std::string line;
        std::getline(std::cin, line, '\n');
        if(line == "quit")
            break;

        std::stringstream ss(line);
        std::string inputstr;
        while(ss >> inputstr) {
            std::string str;
            std::remove_copy_if(inputstr.begin(), inputstr.end(), back_inserter(str), [](const auto ch){ return !isalnum(ch);} );
            inputstr = str;
            std::sort(str.begin(), str.end());
            auto hit = anagrams.find(str);
            if(hit == anagrams.end()) {
                std::vector<std::string> words{inputstr};
                anagrams.insert(std::make_pair(str, words));
            }
            else {
                anagrams[str].push_back(inputstr);
            }
        }
    }

    std::cout << "The anagram words are:\n";
    for( const auto entry : anagrams ) {
        auto words = entry.second;
        std::sort(words.begin(), words.end());
        std::unique_copy(words.begin(), words.end(), std::ostream_iterator<std::string>(std::cout, ", "));
        std::cout << std::endl;
    }

    sleep(5);
    return(0);
}