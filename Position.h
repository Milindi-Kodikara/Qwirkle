//
// Created by Milindi Kodikara on 2019-04-30.
//

#ifndef APT_ASSIGNMENT_2_POSITION_H
#define APT_ASSIGNMENT_2_POSITION_H


#include <string>

class Position {

    Position(std::string xy);
    Position(int x, int y);

public:
    int x;
    int y;

//requires string conversion functionality
};


#endif //APT_ASSIGNMENT_2_POSITION_H
