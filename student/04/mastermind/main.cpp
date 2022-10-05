/* Mastermind
 *
 * Desc:
 *   This program implements a Mastermind game. First a secret series of
 * four colors is either given or drawn. The series can have several
 * identical colors, but none of the four positions can be empty.
 * The user tries to guess which colors the secret series has and in which
 * order they occur there. For this purpose, the user gives their own
 * series of four colors, and the program tells how many colors in the
 * guess was totally correct (correct color in correct position) and how
 * many of them were correct in color (but incorrect in position). After
 * that the user guesses again and so on.
 *   At first, the user is asked, if the game board will be filled with
 * randomly drawn colors, or with user-given ones. (The latter way is not
 * very sensible, but it is useful in testing purposes.) In the first
 * option, a seed value for the random number generator will be asked next.
 * In the latter option, the user is asked to input four colors (the first
 * letters of the colors, i.e. a string consisting of four characters).
 *   On each round, the user is asked for a new guess. The player wins if
 * all colors in the guess are totally correct. The player loses if they
 * have used the maximum number (10) of guesses without the right one.
 *   The program checks if the user-given colors are among accepted ones.
 * When the game ends, the program tells if the player won or lost.
 *
 * Program author
 * Name: Tuuli Silvennoinen
 * Student number: 15018558
 * UserID: kftusi
 * E-Mail: tuuli.silvennoinen@tuni.fi
 *
 *
 * */

#include "guess.hh"
#include <iostream>
#include <vector>
#include <random>
#include <string>

using namespace std;

// Maximum number of guesses
const unsigned int GUESS_MAX = 10;

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


// get random correct colors
vector<char> get_correct_colors(int seed, vector<char> correct_colors) {
    // get random colors using seed number asked from user
    default_random_engine gen(seed);
    uniform_int_distribution<int> distr(1, 6);
    char letter;
    int i = 0;
    // function gives random number from 1 to 6, based this number is given a color
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
        // colors is put in correct_colors vector
        correct_colors.push_back(letter);
        i += 1;
    }
    // function returns correct colors
    return correct_colors;
}

// get user input
vector<char> get_input(vector<char> correct_colors)
{
    cout << "Enter an input way (R = random, L = list): ";
    string input_str = "";
    cin >> input_str;

    // if input random -> get seed value with is used to generate random colors
    if(input_str == "R" or input_str == "r")
    {
        cout << "Enter a seed value: ";
        int seed = 0;
        cin >> seed;

        // use correct_colors function to get random colors
        correct_colors = get_correct_colors(seed, correct_colors);

    // if input list, user lists the colors to be used as correct colors
    } else if(input_str == "L" or input_str == "l") {
        bool accepted = false;
        while(not accepted)
        {
            cout << "Enter four colors (four letters without spaces): ";
            string colors = "";
            cin >> colors;

            string::size_type length = 0;
            length = colors.length();

            // quit the program
            if ( colors == "q" || colors == "Q") {
                accepted = true;
                continue;
            } else {
                //check if input is okay
                for (char color : colors) {
                    // change color to uppercase letter to make checking it easier
                    color = toupper(color);
                    // if color combination given by user is not 4 letters, will be asked for a new input
                    if ( length != 4) {
                        cout << "Wrong size" << endl;
                        break;
                    // if given color is not in colors given in the beginning, new input will be asked
                    } if ( !( color == 'B' || color == 'R' || color == 'Y' || color == 'G' || color == 'O' || color == 'V')) {
                        cout << "Unknown color" << endl;
                        break;
                    } else {
                    accepted = true;
                    }
                }
                // given colors are added to correct_colors vector
                for( char color : colors) {
                    correct_colors.push_back(color);
                }
            }
        }
    } else {
        // if input is not 'r' or 'l', new input will be asked
        cout << "Bad input" << endl;
        // Below the function itself is called recursively, which makes the
        // above code executed until an acceptable input_str is given,
        // but instead you can enclose the above code inside a loop structure.
        get_input(correct_colors);
    }
    // function returns the correct_colors
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
void print_all(const vector< vector < char> > all_guesses, vector < vector <int >> amount_guessed)
{   // use print_line_with_char function to print line before guessed colors
    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);

    int i = 0;
    // go throug vector include all he guesses and print the guesses
    for (vector<char> one_guesses : all_guesses) {
            cout << "| ";
        for ( char color : one_guesses) {
            color = toupper(color);
            cout << color << " ";
        }
        cout << "|";
        // print after the guesses how many of them were correct on the same line
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
    // define vector including correct_colors
    vector<char> correct_colors;
    // print info text in the beginning of the program
    cout << INFO_TEXT << endl;
    print_line_with_char('*', INFO_TEXT.size());

    // get the row of the correct colors
    correct_colors = get_input(correct_colors);

    // if correct_colors vector is empty, quit the program.
    // vector is empty when user gives input 'q'
    if ( correct_colors.empty()) {
        return 0;
    }

    // define vector including all the guesses and class guess
    // that handles everything about the user's guesses
    vector< vector < char> >  all_guesses;
    Guess guess(all_guesses);
    // define vector including amount of correct guesses
    vector < vector <int >> amount_guessed;

    bool can_guess = true;
    // i helps to keep track in while-loop if user input was correct
    unsigned long int i = 0;

    while(can_guess) {
        // get user input from class guess with function get_input
        all_guesses = guess.get_input(correct_colors, amount_guessed);

        vector<vector<char>>::size_type guess_amount;
        guess_amount = all_guesses.size();

        // guess_amount vector size is different than i when user input wasn't okay.
        // then guesses won't be printed and new input will be asked from the user
        if(guess_amount == i +1 ) {
            // when user input was okay, print_all function is used to print all guesses
            print_all(all_guesses, amount_guessed);

            vector<vector<char>>::size_type guess_amount;
            guess_amount = all_guesses.size();
            // if guess_amount vector has more guesses than the maximun value is,
            // user loses the game and program quits
            if ( guess_amount >= GUESS_MAX) {
                cout << "You lost: Maximum number of guesses done" << endl;
                can_guess = false;
            // if user guessed all four colors correctly and in correct places, they win and program quits
            } if (amount_guessed.back().at(0) == 4) {
                cout << "You won: Congratulations!" << endl;
                can_guess = false;
            }
        // if guess_amount vector size is different than i, 1 is reduced from i to make
        // it same size as guess_amount
        } else {
            i -= 1;
        }
        // in the end of the loop 1 is added to i, to keep it same as guess_amount
        ++i;
    }

    return 0;
}

