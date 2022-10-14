#include <iostream>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

using namespace std;

void print_vertical(unsigned int num)
{
    RECURSIVE_FUNC
    // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
    // ------------


    // Add your implementation here

    string s = to_string(num);

    cout << s.at(0) << endl;

    if ( s.length() == 0) {
        return;
    } else {
        s.erase(0,1);
        if ( s.length() == 0) {
            return;
        } else {
            if ( s.at(0) == '0') {
                int number = stoi(s);
                number = 0 + number;

                return print_vertical(number);
            } else {
                int number = stoi(s);
                return print_vertical(number);
            }

        }
    }

}


// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    unsigned int number = 0;
    cout << "Enter a number: ";
    cin >> number;
    cout << "The given number (" << number << ") written vertically:" << endl;
    print_vertical(number);
    return 0;
}
#endif
