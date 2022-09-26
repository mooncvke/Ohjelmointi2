#include <cstdlib>
#include <iostream>
#include <vector>


// Reads as many integers as the parameter count indicates
// and stores them into the parameter vector ints.
void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}

// TODO: Implement your solution here

bool same_values(std::vector< int >& ints) {
    int first = ints.at(0);
    unsigned int value = 0;

    for (int i : ints) {
        if  ( i == first) {
            value += 1;
        }
    }

    if (value == ints.size())  {
        return true;
    } else {
        return false;
    }

}

bool is_ordered_non_strict_ascending(std::vector< int >& ints) {
    int previous;
    int first = 0;
    unsigned int value = 0;

    for (int i : ints) {
        if  ( first == 0) {
            first += 1;
            value += 1;
            previous = i;
        } else {
            if(i >= previous) {
                value += 1;
                previous = i;
            } else {
                previous = i;
            }
        }
    }

    if (value == ints.size())  {
        return true;
    } else {
        return false;
    }

}

bool is_arithmetic_series(std::vector< int >& ints) {
    int previous;
    int first = 0;
    unsigned int value = 0;
    int diff;
    int newdiff;

    for (int i : ints) {
        if ( first == 0) {
            first += 1;
            previous = i;
        } if ( first == 1) {
            first += 1;
            diff = i - previous;
            previous = i;
        } else {
            newdiff = i - previous;
            if (newdiff == diff) {
                value += 1;
                diff = newdiff;
                previous = i;
            } else {
                diff = newdiff;
                previous = i;
            }
        }
    }

    if (value == ints.size() - 2)  {
        return true;
    } else {
        return false;
    }
}

bool is_geometric_series(std::vector< int >& ints) {
    int previous;
    int first = 0;
    unsigned int value = 0;
    int div;
    int newdiv;

    for (int i : ints) {
        if ( first == 0) {
            first += 1;
            previous = i;
        } if ( first == 1) {
            first += 1;
            div = i / previous;
            previous = i;
        } else {
            newdiv = i / previous;
            if (newdiv == div) {
                value += 1;
                div = newdiv;
                previous = i;
            } else {
                div = newdiv;
                previous = i;
            }
        }
    }

    if (value == ints.size() - 2)  {
        return true;
    } else {
        return false;
    }
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
