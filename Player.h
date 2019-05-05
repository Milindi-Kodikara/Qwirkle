//
// Created by Milindi Kodikara on 2019-04-30.
//

#ifndef APT_ASSIGNMENT_2_PLAYER_H
#define APT_ASSIGNMENT_2_PLAYER_H


#include <string>
#include "LinkedList.h"

class Player
{

public:
    Player(std::string name);

    std::string name;
    int score;
    LinkedList hand;

};


#endif //APT_ASSIGNMENT_2_PLAYER_H
