#ifndef GUESS_H
#define GUESS_H

#include <vector>
#include <iostream>

class Guess;
using colors = std::vector< std::vector < Guess > >;



class Guess
{
public:
    Guess(colors);

    colors give_colors(int seed);
};

#endif // GUESS_H
