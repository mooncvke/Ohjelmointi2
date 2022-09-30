#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function
using split_string = std::vector<std::string>;

split_string split(const std::string &line, const char sep, bool value = false) {

    split_string parts = {};
    std::string word = "";

    // go through the line
    for ( char c : line) {
        if (c == sep) {
            if (!(word.empty() && value)) {
               parts.push_back(word);
            }
            word.clear();

            } else {
                word += c;
            }

    }

    parts.push_back(word);
    return parts;
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
