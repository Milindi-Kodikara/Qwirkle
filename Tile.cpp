#include "Tile.h"
#include <iostream>

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
	int shape = y - '0';

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

std::string Tile::colourOutput(Colour colour)
{
	std::string output;

	if (colour == RED)
	{
		output = RED_OUTPUT;
	}
	else if (colour == ORANGE)
	{
		output = ORANGE_OUTPUT;
	}
	else if (colour == YELLOW)
	{
		output = YELLOW_OUTPUT;
	}
	else if (colour == GREEN)
	{
		output = GREEN_OUTPUT;
	}
	else if (colour == BLUE)
	{
		output = BLUE_OUTPUT;
	}
	else if (colour == PURPLE)
	{
		output = PURPLE_OUTPUT;
	}
	return output;

}