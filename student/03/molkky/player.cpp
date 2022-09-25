#include "player.hh"


Player::Player(const string &name):
    name_(name), points_(0)
{

}

string Player::get_name()
{
    return name_;
}

int Player::get_points()
{
    return points_;
}
void Player::add_points(int points)
{
    points_ += points;

    if (points_ > 50) {
        std::cout << name_ << " gets penalty points!" << std::endl;
        points_ = 25;
    }

}

bool Player::has_won()
{
    if (points_ == 50) {
        return true;
    } else {
        return false;
    }
}

