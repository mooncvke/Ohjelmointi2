#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
  RECURSIVE_FUNC
  // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
  // ------------

    int n = 0;
    std::string::size_type size = 0;
    size = s.length();

    if ( size == 1) {
        return true;
    }
    if ( size == 0){
        return true;
    }

    if (s.at(n) == s.at(size - 1)) {
        s.erase(size -1 , 1);
        s.erase(0, 1);

        return palindrome_recursive(s);
    }

    else{
        return false;
    }
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
