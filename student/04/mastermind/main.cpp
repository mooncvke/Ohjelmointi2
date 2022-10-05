// TODO: Include your header file of the class describing a series of four colors
#include "guess.hh"
#include <iostream>
#include <vector>
#include <random>

using namespace std;

// Maximum number of guesses
// (Not used in the template code)
const unsigned int GUESS_MAX = 10; // Not in use, yet

// Number of colors in a series
const unsigned int SIZE = 4;

// Length of the suffix part when printing a row.
// The suffix consists of three vertical lines ('|') and two digits, where one
// tells the amount of totally correct colors and the other tells the amount
// of correct colors in incorrect positions.
const unsigned int SUFFIX_LENGTH_IN_PRINT = 5;



// Text printed at the beginning of the program
const string INFO_TEXT = "Colors in use: \
B = Blue, R = Red, Y = Yellow, G = Green, O = Orange, V = Violet";

// TODO: Do you need more constants?

// Reads the input way, either random or listing way,
// and fills the color series in the user-desired way.
// Repeats the question until the user enters either R or L.

vector<char> get_correct_colors(int seed, vector<char> correct_colors) {
    default_random_engine gen(seed);
    uniform_int_distribution<int> distr(1, 6);
    char letter;
    int i = 0;
    while( i < 4) {
        if ( distr(gen) == 1 ) {
           letter = 'B';
        }if ( distr(gen) == 2 ) {
            letter = 'R';
        }if ( distr(gen) == 3 ) {
            letter = 'Y';
        }if ( distr(gen) == 4 ) {
            letter = 'G';
        }if ( distr(gen) == 5 ) {
            letter = 'O';
        }if ( distr(gen) == 6 ) {
            letter = 'V';
        }
        correct_colors.push_back(letter);
        i += 1;
    }

    return correct_colors;
}

vector<char> get_input(vector<char> correct_colors)
{
    cout << "Enter an input way (R = random, L = list): ";
    string input_str = "";
    cin >> input_str;
    if(input_str == "R" or input_str == "r")
    {
        cout << "Enter a seed value: ";
        int seed = 0;
        cin >> seed;

        correct_colors = get_correct_colors(seed, correct_colors);


    }
    else if(input_str == "L" or input_str == "l")
    {
        bool accepted = false;
        while(not accepted)
        {
            cout << "Enter four colors (four letters without spaces): ";
            string colors = "";
            cin >> colors;

            if ( colors == "q" || colors == "Q") {
                accepted = true;
                continue;
            } else {
                //check if okay
                for (char color : colors) {
                    if ( !isupper(color)) {
                        cout << "Wrong size" << endl;
                        break;
                    } if ( !( color == 'B' || color == 'R' || color == 'Y' || color == 'G' || color == 'O' || color == 'V')) {
                        cout << "Unknown color" << endl;
                        break;
                    } else {
                    accepted = true;
                    }
                }

                for( char color : colors) {
                    correct_colors.push_back(color);
                }
        }

        }
    }
    else
    {
        cout << "Bad input" << endl;
        // Below the function itself is called recursively, which makes the
        // above code executed until an acceptable input_str is given,
        // but instead you can enclose the above code inside a loop structure.
        get_input(correct_colors);
    }
        return correct_colors;
}


// Prints a line consisting of the given character c.
// The length of the line is given in the parameter line_length.
void print_line_with_char(char c, unsigned int line_length)
{
    for(unsigned int i = 0; i < line_length; ++i)
    {
        cout << c;
    }
    cout << endl;
}

// Prints all color series.
// (Not called in the template code.)
void print_all(vector< vector < char> > all_guesses, vector < vector <int >> amount_guessed)
{
    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);

    int i = 0;
    cout << "| ";
    for ( vector< char > one_guesses : all_guesses) {
        for ( char color : one_guesses) {
            cout << color << " ";
        }
        cout << "|";
        for ( int guessed_correct : amount_guessed.at(i) ) {
            cout << " " << guessed_correct << " |";
        }
        cout << endl;
        i += 1;
    }
    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);
}


int main()
{
    vector<char> correct_colors;
    cout << INFO_TEXT << endl;
    print_line_with_char('*', INFO_TEXT.size());

    // get the row of the correct colors
    correct_colors = get_input(correct_colors);

    if ( correct_colors.empty()) {
        return 0;
    }


    vector< vector < char> >  all_guesses;
    Guess guess(all_guesses);

    vector < vector <int >> amount_guessed;


    bool can_guess = true;

    while(can_guess) {

        all_guesses = guess.get_input(correct_colors, amount_guessed);

        if(not all_guesses.back().empty() ) {
            print_all(all_guesses, amount_guessed);

            vector<vector<char>>::size_type guess_amount;
            guess_amount = all_guesses.size();

            if ( guess_amount >= GUESS_MAX) {
                cout << "You lost: Maximum number of guesses done" << endl;
                can_guess = false;
            } if (amount_guessed.back().at(0) == 4) {
                cout << "You won: Congratulations!" << endl;
                can_guess = false;
            }

        } else {
            can_guess = true;
        }


    }


    return 0;
}

