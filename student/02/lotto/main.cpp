#include <iostream>

using namespace std;

unsigned long int factorial( int amount) {
    unsigned long int result = 1;
    unsigned long int num = 1;

    while(amount > 0) {
        result = result * num;
        --amount;
        ++num;
    }
    cout << result << endl;
    return result;
}

unsigned long int probability (unsigned long int total, unsigned long int drawn ) {
    unsigned long int n = factorial(total);
    unsigned long int n_p = total - drawn;
    unsigned long int minus = factorial(n_p);
    unsigned long int p = factorial(drawn);
    unsigned long int result = (n / (minus * p));

    return result;
}


int main()
{
    cout << "Enter the total number of lottery balls: ";
    unsigned long int total;
    cin >> total;

    cout << "Enter the number of drawn balls:";
    unsigned long int drawn;
    cin >> drawn;


/*
    if (total < 1) {
        cout << "The number of balls must be positive number." << endl;

    } else if (drawn < 1){
        cout << "The number of balls must be positive number." << endl;


    }
*/


    cout << "The probability of guessing all " << drawn << " balls correctly is 1/"<< probability(total, drawn) << endl;

}
