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
    return result;
}

unsigned long int probability (int total, int drawn ) {
    unsigned long int n = factorial(total);
    int n_p = total - drawn;
    unsigned long int minus = factorial(n_p);
    unsigned long int p = factorial(drawn);
    unsigned long int result = (n / (minus * p));

    return result;
}


int main()
{
    cout << "Enter the total number of lottery balls: ";
    int total;
    cin >> total;

    cout << "Enter the number of drawn balls: ";
    int drawn;
    cin >> drawn;

    if (total < 1 or drawn < 1) {
        cout << "The number of balls must be a positive number." << endl;

    } else if (drawn > total){
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;


    } else {


    unsigned long int prob = probability(total, drawn);

    cout << "The probability of guessing all " << drawn << " balls correctly is 1/"<< prob << endl;
    }

}
