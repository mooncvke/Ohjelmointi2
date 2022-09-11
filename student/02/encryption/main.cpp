#include <iostream>

using namespace std;

int main()
{
    cout << "Enter the encryption key: " ;
    string key;
    cin >> key;

    if ( key.length() < 26) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return 0;
    }

    int length = key.length();

    for ( int i = 0; i < length; i++ ) {
        if ( islower(key[i]) == false ) {
            cout << "Error! The encryption key must contain only lower case characters" << endl;
            return 0;
        }
    }

    string alphabet = "";
    for ( char letter = 'a'; letter <= 'z'; ++letter) {
        alphabet += letter;
    }

    cout << alphabet << endl;

    if (key != alphabet ) {
        cout << "Error! The encryption key must contain all alphabets a-z." << endl;
        return 0;
    }



    cout << "Enter the text to be encrypted: " << endl;
    string text;
    cin >> text;
}
