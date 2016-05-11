//
// Created by shiva on 5/11/16.
//

#include <iostream>
#include <string>

int main ()
{
    std::string name;
    unsigned foo;
    std::cin >> foo;
    std::getline (std::cin,name); // how do I avoid the \n after foo was read?
    std::cout << "Please, enter your full name: ";
    std::getline (std::cin,name);
    std::cout << "Hello, " << name << "!\n";

    return 0;
}