#include "Card.h"
#include "Config.h"
#include "graphics.h"
#include <string>
using namespace graphics;


void Card::update()
{
}

void Card::draw()
{
}

void Card::init()
{
}

float Card::getX()
{
	return pos_x;
}

void Card::setX(float x)
{
	pos_x = x;
}

float Card::getY()
{
	return pos_y;
}

void Card::setY(float y)
{
	pos_y = y;
}

// if the Card object is Asset, returns the name, else (if Questionmark) returns the paragraph 
std::string Card::getDescription()
{
	return description;
}

Card::Card(const int& pos_x, const int& pos_y, const std::string& description ): pos_x(pos_x), pos_y(pos_y), description(description) {}
