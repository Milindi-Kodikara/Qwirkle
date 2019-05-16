
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>
#include "TileCodes.h"

#define RESET   "\033[0m"
#define RED_OUTPUT     "\033[91m"
#define ORANGE_OUTPUT	"\033[38;5;202m"
#define YELLOW_OUTPUT  "\033[93m"
#define GREEN_OUTPUT   "\033[92m"
#define BLUE_OUTPUT    "\033[96m"
#define PURPLE_OUTPUT	"\033[95m"

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

	std::string getLabel(bool colouredOutput);
};

#endif // ASSIGN2_TILE_H
