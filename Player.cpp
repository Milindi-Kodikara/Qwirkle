#include "Player.h"

Player::Player(std::string name)
{
    this->name = name;
    score = 0;
	difficulty = HUMAN;
}