#include <iostream>

using namespace std;
#include <cmath>

int main()
{
    cout << "Enter a positive number: ";

    int num;
    cin >> num;

    if (num <= 0) {
        cout << "Only positive numbers accepted" << endl;
    } else {
        int testnum = sqrt(num);

        while ( num % testnum != 0 ) {
            testnum--;

        }
        cout << num << " = " << testnum << " * " << num / testnum << endl;    }

    return 0;
}
