#include "guess.hh"

Guess::Guess(guess_vector& guesses):
    guesses_(guesses){

}

// get input from user
guess_vector Guess::get_input(std::vector<char>& correct_colors, std::vector< std::vector< int >>& amount_guessed)
{

    std::vector<char> colors;
    std::string answer;
    std::cout << "ROW> ";
    std::cin >> answer;

    // input is in string -> it is changed to vector
    for (char i : answer ) {
        colors.push_back(i);
    }
    // use check_if_ok function to check if the user input is ok
    bool is_ok;
    is_ok = check_if_ok(colors);
    // if user input is ok
    if (is_ok == true) {
        // use check_if_correct function to check if user guessed correctly
        check_if_correct(colors, correct_colors, amount_guessed);
        // put guessed colors in the guesses_ vector
        guesses_.push_back(colors);
    }
    // function returns vector including guesses
    return guesses_;
}

// check if guess was correct
guess_amount_vector Guess::check_if_correct(std::vector<char>& colors, std::vector<char>& correct_colors, std::vector < std::vector <int >>& amount_guessed)
{
    // define variables used
    int i = 0;
    int guessed_correctly = 0;
    int guessed_color_correctly = 0;

    std::vector < int > one_guessed;
    std::vector <int> used_colors;

    // go through colors guessed
    for( char color : colors ) {
        // if guessed color is in same place and is same color as in correct colors
        if ( color == correct_colors.at(i)) {
            // user guessed color and place correctly and 1 is added to guessed_correctly variable
            guessed_correctly += 1;

            if (std::find(used_colors.begin(), used_colors.end(), color) != used_colors.end()) {
                if ( guessed_color_correctly > 1) {
                    guessed_color_correctly -= 1;


            }
            used_colors.push_back(color);
        // didn't guess place and color correctly
        } else {
            //if color isn't already in guessed colors
            if (std::find(used_colors.begin(), used_colors.end(), color) == used_colors.end()) {
                // use check_if_correct_color function to check if color was guessed correctly
                int amount = check_if_correct_color(correct_colors, color, guessed_color_correctly, i);
                guessed_color_correctly = amount;
                // add color to used colors
                used_colors.push_back(color);
            }
            }
        }
        ++i;
    }
    // add guessed correctly and guessed only color correctly to amount_guessed vector
    one_guessed.push_back(guessed_correctly);
    one_guessed.push_back(guessed_color_correctly);
    amount_guessed.push_back(one_guessed);

    // return amount_guessed
    return amount_guessed;
}

// check if user guessed correct color
int Guess::check_if_correct_color(std::vector<char>& correct_colors, char guessed_color, int guessed_color_correctly, int i)
{
    // go through correct colors
    for(char color : correct_colors) {
        // if guessed color is same as correct color
        if ( color == guessed_color) {
            if( guessed_color == correct_colors.at(i)) {
                // if guessed color and place correctly -> nothing happens
            } else {
                // if guessed only color correctly -> 1 is added to guessed_color_correctly variable
                guessed_color_correctly += 1;
            }
        }
    }
    // returns amount of colors guessed correctly
    return guessed_color_correctly;
}

// check if user input is okay
bool Guess::check_if_ok(std::vector<char> &colors)
{

    std::vector<char>::size_type length = 0;
    length = colors.size();

    // go through user input
    for( char color : colors ) {
        // change color to uppercase letter to make easier to checking it
        color = toupper(color);
        // if length of the color combination is not 4
        if ( length != 4) {
            std::cout << "Wrong size" << std::endl;
            return false;
        }
        // if color is not color used in this game
        if (!( color == 'B' || color == 'R' || color == 'Y' || color == 'G' || color == 'O' || color == 'V')) {
            std::cout << "Unknown color" << std::endl;
            return false;
        }
    }
    // if input is okay function returns true, if not okay function returns false
    return true;
}

