#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";

    double temp;
    cin >> temp;

    cout << temp << " degrees Celsius is " << temp *1.8 +32 << " dergrees Fahrenheit" << endl;
    cout << temp << " degrees Fahrenheit is " << (temp - 32 )/1.8<< " dergrees Celsius" << endl;


    return 0;
}
