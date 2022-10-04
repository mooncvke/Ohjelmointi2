#include "guess.hh"

Guess::Guess(guess_vector& guesses):
    guesses_(guesses), guess_amount_()
{

}

guess_vector Guess::get_input(std::vector<char>& correct_colors, std::vector< std::vector< int >>& amount_guessed)
{

    std::vector<char> colors;
    std::string answer;
    std::cout << "ROW: ";
    std::cin >> answer;


    for (char i : answer ) {
        colors.push_back(i);
    }
    bool is_ok;
    is_ok = check_if_ok(colors);

    if (is_ok == true) {
        check_if_correct(colors, correct_colors, amount_guessed);

        guesses_.push_back(colors);

        return guesses_;
    }
    return guesses_;

}

guess_amount_vector Guess::check_if_correct(std::vector<char>& colors, std::vector<char>& correct_colors, std::vector < std::vector <int >>& amount_guessed)
{
    std::cout << "here in guess.ccp " << std::endl;

    int i = 0;
    int guessed_correctly = 0;
    int guessed_color_correctly = 0;
    std::vector < int > one_guessed;

    for( char color : colors ) {

        if ( color == correct_colors.at(i)) {

            // guessed color and place correctly
            guessed_correctly += 1;
        } else {
            //check if guessed color correctly
            int amount = check_if_correct_color(correct_colors, color, guessed_color_correctly, i);
            guessed_color_correctly = amount;
        }
        ++i;
    }
    one_guessed.push_back(guessed_correctly);
    one_guessed.push_back(guessed_color_correctly);
    amount_guessed.push_back(one_guessed);

    return amount_guessed;

}

int Guess::check_if_correct_color(std::vector<char>& correct_colors, char guessed_color, int guessed_color_correctly, int i)
{
    std::cout << "checking if correct color " << std::endl;

    for(char color : correct_colors) {
        if ( color == guessed_color) {
            if( guessed_color == correct_colors.at(i)) {
                // if guessed color and place correctly
            } else { // puuttuu tarkastelu jos sitä väriä onkin useampia
                // if guessed only color correctly
                guessed_color_correctly += 1;
            }
        }
    }

    return guessed_color_correctly;
}

bool Guess::check_if_ok(std::vector<char> &colors)
{
    for( char color : colors ) {
        if ( !isupper(color)   ) {
            std::cout << "Wrong size" << std::endl;
            return false;
        }if (!( color == 'B' || color == 'R' || color == 'Y' || color == 'G' || color == 'O' || color == 'V')) {
            std::cout << "Unknown color" << std::endl;
            return false;
        }
    }
    return true;
}

