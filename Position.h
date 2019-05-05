//
// Created by Milindi Kodikara on 2019-04-30.
//

#ifndef APT_ASSIGNMENT_2_POSITION_H
#define APT_ASSIGNMENT_2_POSITION_H
#define BOARD_SIZE  26


#include <string>

class Position {
public:
    //requires string conversion functionality
    Position();
    Position(int x, int y);

    static Position* labelToPosition(std::string positionLabel);

    Position operator+(const Position& position);
    Position& operator+=(const Position& position);

    int x;
    int y;

};

#endif //APT_ASSIGNMENT_2_POSITION_H
