#ifndef GUESS_H
#define GUESS_H

#include <vector>
#include <iostream>
#include <algorithm>

class Guess;
using guess_vector = std::vector< std::vector < char > >;
using guess_amount_vector = std::vector< std::vector < int > >;



class Guess
{
public:
    Guess(guess_vector& guesses);

    guess_vector get_input(std::vector<char>& correct_colors, std::vector < std::vector <int >>& amount_guessed);
    guess_amount_vector check_if_correct(std::vector<char>& colors, std::vector<char>& correct_colors, std::vector < std::vector <int >>& amount_guessed);
    int check_if_correct_color(std::vector<char>& correct_colors, char guessed_color, int guessed_color_correctly, int i);
    bool check_if_ok(std::vector<char>& colors);

private:
    guess_vector& guesses_;
    guess_amount_vector guess_amount_;


};

#endif // GUESS_H
