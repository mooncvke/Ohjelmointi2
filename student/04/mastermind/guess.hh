#ifndef GUESS_H
#define GUESS_H

#include <vector>
#include <iostream>

class Guess;
using guess_vector = std::vector< std::vector < std::string > >;



class Guess
{
public:
    Guess(guess_vector& guesses);

    guess_vector get_input();

private:
    guess_vector guesses_;

};

#endif // GUESS_H
