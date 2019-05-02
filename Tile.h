
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>

typedef char Colour;
typedef int Shape;

class Tile 
{
public:
	Tile(Colour colour, Shape shape);

    Colour colour;
    Shape  shape;
	std::string label;
};

#endif // ASSIGN2_TILE_H
