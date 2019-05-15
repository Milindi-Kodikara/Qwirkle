#include "Position.h"
#include "GameEngine.h"
#include <sstream>
#include <iostream>

Position::Position()
{
    this->x = 0;
    this->y = 0;
}

Position::Position(int x, int y)
{
    this->x = x;
    this->y = y;
}

Position* Position::labelToPosition(std::string label)
{
    Position* position = nullptr;
    int tempX;
    int tempY;

    if (label.size() == 2 || label.size() == 3)
    {
        //Convert char y coordinate to signed int
        tempY = label[0] - 'A';
        //Checks if the coordinate is within range
        if (tempY < BOARD_SIZE && tempY >= 0)
        {
            //Convert char x coordinate to signed int
			std::istringstream iss(label.substr(1, 2));
			iss >> tempX;
            //Checks if the coordinate is within range
            if (!iss.bad() && tempX < BOARD_SIZE && tempX >= 0)
            {
                position = new Position(tempX, tempY);
            }
        }
    }
    return position;
}

Position Position::operator+(const Position& position)
{
    int tempX = this->x + position.x;
    int tempY = this->y + position.y;
    return Position(tempX, tempY);
}

Position& Position::operator+=(const Position &position)
{
    this->x += position.x;
    this->y += position.y;
    return *this;
}
