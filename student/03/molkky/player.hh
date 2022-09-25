#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>
#include <iostream>

using namespace std;

class Player
{
public:
    Player(string const &name);
    string get_name();
    int get_points();
    void add_points(int points);
    bool has_won();


private:
    string name_;
    int points_;
};

#endif // PLAYER_HH
