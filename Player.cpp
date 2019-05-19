#include "Player.h"

Player::Player(std::string name)
{
    this->name = name;
    score = 0;
    difficulty = HUMAN;
}

bool Player::compare(Player* p1, Player* p2)
{
    return p1->score < p2->score;
}


