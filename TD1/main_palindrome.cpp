//
// Created by Tom on 06/09/2021.
//

#include <string>
#include <iostream>

int main()
{
    std::string str;
    std::getline(std::cin, str);

    std::cout << (str == std::string(str.rbegin(), str.rend()) ? "Palindrome" : "Pas palindrome") << std::endl;

    return 0;
}