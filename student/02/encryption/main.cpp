#include <iostream>

using namespace std;

int main()
{
    cout << "Enter the encryption key: " ;
    string key;
    cin >> key;

    if ( key.length() < 26) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return 1;
    }

    int length = key.length();

    for ( int i = 0; i < length; i++ ) {
        if ( islower(key[i]) == false ) {
            cout << "Error! The encryption key must contain only lower case characters" << endl;
            return 1;
        }
    }

    string alphabet = "";
    for ( char letter = 'a'; letter <= 'z'; letter++) {
        if(key.find(letter)<key.length()) {
        } else {
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            return 1;
        }
    }


    cout << "Enter the text to be encrypted: ";
    string text;
    cin >> text;

    int text_length = text.length();

    for ( int i = 0; i < text_length; i++ ) {
        if ( islower(text[i]) == false ) {
            cout << "Error! The text to be encrypted must contain only lower case characters." << endl;
            return 1;
        } else {
            continue;
        }
    }


    string encrypted ="";
    int a_value = static_cast< int >('a');

    for ( int i = 0; i < text_length; i++) {
        int value = static_cast< int >(text[i]);
        encrypted += key[value - a_value];
    }

    cout << "Encrypted text: " << encrypted << endl;


}
