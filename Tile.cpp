#include "Tile.h"
#include <iostream>
#include <sstream>

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

std::string Tile::getLabel(bool displayColour)
{
	std::string output;
	std::string outputColour;

	if (colour == RED)
	{
		outputColour = RED_OUTPUT;
	}
	else if (colour == ORANGE)
	{
		outputColour = ORANGE_OUTPUT;
	}
	else if (colour == YELLOW)
	{
		outputColour = YELLOW_OUTPUT;
	}
	else if (colour == GREEN)
	{
		outputColour = GREEN_OUTPUT;
	}
	else if (colour == BLUE)
	{
		outputColour = BLUE_OUTPUT;
	}
	else if (colour == PURPLE)
	{
		outputColour = PURPLE_OUTPUT;
	}

	if(displayColour)
	{
		output =  outputColour + this->label + RESET ;
	}
	else output = this->label;

	return output;

}