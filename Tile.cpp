#include "Tile.h"

Tile::Tile(Colour colour, Shape shape)
{
	this->colour = colour;
	this->shape = shape;
	label = "";
	label += colour;
	label += std::to_string(shape);
}