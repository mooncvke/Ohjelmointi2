#include "guess.hh"

Guess::Guess(guess_vector& guesses):
    guesses_(guesses)
{

}

guess_vector Guess::get_input()
{
    std::vector<std::string> row;
    std::string answer;
    std::cout << "ROW: ";
    std::cin >> answer;

    row.push_back(answer);

    guesses_.push_back(row);

    for ( std::vector<std::string> j : guesses_) {
        for (std::string i : j) {
            std::cout << "test print: " << i << std::endl;
        }
    }

    return guesses_;

}

