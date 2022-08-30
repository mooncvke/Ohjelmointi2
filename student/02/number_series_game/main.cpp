#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";

    int amount;
    std::cin >> amount;

    int num =1;
    while (num <= amount) {
        if ( num % 3 == 0 and num % 7 == 0 ) {
            std::cout << "zip boing" << std::endl;
        }
        if ( num % 3 == 0) {
            std::cout<<"zip" << std::endl;
        }
        if ( num % 7 == 0) {
            std::cout << "boing" << std::endl;
        }

        std::cout<<num<<std::endl;
        ++num;
    }

    return 0;
}
