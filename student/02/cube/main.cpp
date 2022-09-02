#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a number: ";
    int num;
    cin >> num;

    int cube;
    cube = num * num * num;

    if (cube < 0 or cube / num / num != num) {
        cout << "Error! The cube of " << num << " is not " << cube << "." << endl;
    } else {
        cout << "The cube of " << num << " is " << cube << "." << endl;
    }

}
