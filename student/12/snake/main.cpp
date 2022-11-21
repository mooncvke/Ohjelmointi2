/*
####################################################################
# COMP.CS.110 Programming 2: Structures, 2022                      #
#                                                                  #
# Project4: Snake                                                  #
# Program description: Implements a game called Snake.             #
#                                                                  #
# File: main.cpp                                                   #
# Description: Starts executing the program.                       #
#                                                                  #
# Author: First Last, s.num., first.last@tuni.fi                   #
####################################################################
*/

#include "gameboard.hh"
#include <cctype> // required for std::isdigit
#include <iostream>
#include <string>

// Constants for special commands
const char QUIT = 'q';
const char HELP = 'h';

// Gets a string from the player.
// Returns the text, the player wrote after the prompt.
std::string getInput(const std::string& prompt = "> ")
{
    std::cout << prompt;
    std::string input;
    getline(std::cin, input);
    return input;
}

// Returns true if the given string is a valid command.
bool checkCommand(const std::string& command)
{
    if(command.size() < 1)
    {
        return false;
    }
    for (const char& cmd : {UP, LEFT, DOWN, RIGHT, QUIT, HELP})
    {
        if (command.at(0) == cmd)
        {
            return true;
        }
    }
    return false;
}

// Prints a block of help text to aid with the game.
void printHelp()
{
    // ## No bugs have been planted here, this might help with debugging. ##
    std::cout << "\nWelcome to Snake!\n\n"
        << "Your aim is to guide the snake to the food around the field\n"
        << "while avoiding the walls and the ever-growing snake itself.\n\n"
        << "The snake can't make 180 degree turns, which means that\n"
        << "it can't go directly back to the square it came from,\n"
        << "unless the snake occupies only one square in total.\n\n"
        << "Symbols and their meanings:\n"
        << HEAD << " head, " << BODY << " body, " << TAIL << " tail,\n"
        << WALL << " wall, " << FOOD << " food\n\n"
        << "You have the following commands at your disposal:\n"
        << UP << ": Move the snake up\n"
        << LEFT << ": Move the snake left\n"
        << DOWN << ": Move the snake down\n"
        << RIGHT << ": Move the snake right\n"
        << QUIT << ": Stop the game\n"
        << HELP << ": Print this text again\n\n" << std::endl;
}

// Asks the player for a random seed.
// Returns the given seed or current time.
unsigned int getRandomSeed()
{
    const std::string seed = getInput("Give a seed for random numbers: ");

    // Converting (as much of) the string to a number if possible.
    if (not seed.empty() and std::isdigit(seed.front()))
    {
        return static_cast<unsigned int>(std::stoi(seed));
    }

    // Using current time as a seed if the given seed isn't a number.
    return time(NULL);
}

// Gets a sensible width or height for a gameboard,
// prompt tells the player what to write.
// Returns the given size.
int getFieldSize(const std::string& prompt)
{
    int size = 0;
    while (size < 3 or size > 10)
    {
        const std::string input = getInput(prompt);

        // Converting (as much of) the string to a number if possible.
        if (not input.empty() and std::isdigit(input.front()))
        {
            size = std::stoi(input);
        }
    }
    return size;
}

int main()
{
    // Creating a field of desired size.
    const int width = getFieldSize("Field width (between 3 and 10): ");
    const int height = getFieldSize("Field height (between 3 and 10): ");
    //std::default_random_engine rng(getRandomSeed());
    GameBoard field(width, height, getRandomSeed());

    // Printing the help text when starting the game.
    printHelp();
    field.print();

    // Asking for input until the game stops.
    while (not field.gameOver())
    {
        // Getting and validating the input.
        const std::string command = getInput();
        if (not checkCommand(command))
        {
            std::cout << "Unknown command! Try command 'help'." << std::endl;
            continue;
        }

        // Executing the given command.
        if (command.at(0) == QUIT)
        {
            break;
        }
        else if (command.at(0) == HELP)
        {
            printHelp();
        }
        else
        {
            field.moveSnake(command);
        }

        // Printing the current state of the game.
        field.print();
    }

    // Printing a message if the game wasn't stopped with 'quit'.
    if (field.gameLost())
    {
        std::cout << "Snek is ded. Better luck next time ;)" << std::endl;
    }
    else if (field.gameWon())
    {
        std::cout << "Well done! The snake has been satisfied, for now..."
            << std::endl;
    }

    return EXIT_SUCCESS;
}
