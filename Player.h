#ifndef APT_ASSIGNMENT_2_PLAYER_H
#define APT_ASSIGNMENT_2_PLAYER_H


#include <string>
#include "LinkedList.h"

enum Difficulty
{
    EASY,
    MEDIUM,
    HARD,
    HUMAN
};

class Player
{
public:
    Player(std::string name);

    std::string name;
    int score;
    LinkedList hand;
    Difficulty difficulty;

    static bool compare(Player* p1, Player* p2);
};


#endif //APT_ASSIGNMENT_2_PLAYER_H