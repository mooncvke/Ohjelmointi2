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
    previous = ints.at(0);

    for(int i : ints) {
        if (i >= previous) {
            previous = i;
            continue;
        } else if( i < previous) {
            return false;
        }
    }
    return true;


}

bool is_arithmetic_series(std::vector< int >& ints) {
    int previous;
    previous = ints.at(0);
    int diff;
    diff = ints.at(1) - ints.at(0);

    for (int i : ints) {
        if ( i == previous) {
            continue;
        }
        int r1;
        r1 = i - previous;
        previous  = i;
        if ( r1 == diff) {
            continue;

        } else {
            return false;
        }
    }
    return true;
}

bool is_geometric_series(std::vector< int >& ints) {
    int first_int;
    first_int = ints.at(0);

    if ( first_int == 0) {
        return false;
    }

    double ratio;
    ratio = ints.at(1) / ints.at(0);


    for ( int i : ints) {
        if ( i == first_int ) {
            continue;
        }

        double r1;
        r1 = i / first_int;
        first_int = i;

        if ( r1 == ratio) {
            continue;
        } else {
            return false;
        }
    }
    return true;

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
