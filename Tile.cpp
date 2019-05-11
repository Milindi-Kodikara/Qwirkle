#include "Tile.h"

Tile::Tile(Colour colour, Shape shape)
{
	this->colour = colour;
	this->shape = shape;
	label = "";
	label += colour;
	label += std::to_string(shape);
}

Tile* Tile::stringToTile(char x, char y)
{
	Tile* tile = nullptr;
	int colour = x;
	int shape = y;

	if (colour == RED || colour == ORANGE || colour == YELLOW ||
		colour == GREEN || colour == BLUE || colour == PURPLE)
	{
		if (shape == CIRCLE || shape == STAR_4 || shape == DIAMOND
			|| shape == SQUARE || shape == STAR_6 || shape == CLOVER)
		{
			tile = new Tile(colour, shape);
		}
	}
	
	return tile;
}