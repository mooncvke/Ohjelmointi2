#include "guess.hh"

Guess::Guess(guess_vector& guesses):
    guesses_(guesses){

}

guess_vector Guess::get_input(std::vector<char>& correct_colors, std::vector< std::vector< int >>& amount_guessed)
{

    std::vector<char> colors;
    std::vector<std::vector<char>> empty_colors;
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

    }
    return guesses_;
}

guess_amount_vector Guess::check_if_correct(std::vector<char>& colors, std::vector<char>& correct_colors, std::vector < std::vector <int >>& amount_guessed)
{

    int i = 0;
    int guessed_correctly = 0;
    int guessed_color_correctly = 0;
    std::vector < int > one_guessed;

    std::vector <char> used_colors;

    for( char color : colors ) {

        if ( color == correct_colors.at(i)) {

            // guessed color and place correctly
            guessed_correctly += 1;
        } else {
            //check if guessed color correctly
            if (std::find(used_colors.begin(), used_colors.end(), color) == used_colors.end()) {
                int amount = check_if_correct_color(correct_colors, color, guessed_color_correctly, i);
                guessed_color_correctly = amount;
                used_colors.push_back(color);
            }

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
    for(char color : correct_colors) { // katotaan onko color arvatuissa eli guessed_color

        if ( color == guessed_color) { // arvattu väri sama kuin yksi oikeasta värisarjasta
            if( guessed_color == correct_colors.at(i)) {
                // if guessed color and place correctly
            } else {
                // if guessed only color correctly
                guessed_color_correctly += 1;
            }
        }
    }
    return guessed_color_correctly;
}

bool Guess::check_if_ok(std::vector<char> &colors)
{

    std::vector<char>::size_type length = 0;
    length = colors.size();

    for( char color : colors ) {
        color = toupper(color);
        if (!( color == 'B' || color == 'R' || color == 'Y' || color == 'G' || color == 'O' || color == 'V')) {
            std::cout << "Unknown color" << std::endl;
            return false;
        }if ( length != 4) {
            std::cout << "Wrong size" << std::endl;
            return false;
        }
    }
    return true;
}

