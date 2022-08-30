#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";

    int amount;
    std::cin >> amount;

    int num =1;
    while (num <= amount) {

        std::cout<<num<<std::endl;
        ++num;
    }

    return 0;
}
