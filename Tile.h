
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>
#include "TileCodes.h"

#define RESET   "\033[0m"
#define RED_OUTPUT     "\033[31m"
#define ORANGE_OUTPUT	"\033[91m"
#define YELLOW_OUTPUT  "\033[33m"
#define GREEN_OUTPUT   "\033[32m"
#define BLUE_OUTPUT    "\033[34m"
#define PURPLE_OUTPUT	"\033[35m"

typedef char Colour;
typedef int Shape;

class Tile 
{
public:
	Tile(Colour colour, Shape shape);

	static Tile* stringToTile(char x, char y);

    Colour colour;
    Shape  shape;
	std::string label;

	std::string colourOutput(Colour colour);
};

#endif // ASSIGN2_TILE_H
