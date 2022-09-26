#pragma once
#include "Gameobject.h"
#include <string>

class Card : public GameObject{
protected:
	// x and y 
	float pos_x, pos_y;
	// the name of the Asset or the paragraph of the Questionmark
	std::string description;

public:
	void update();
	void draw() override;
	void init() override;
	float getX();
	void setX(float x);
	float getY();
	void setY(float y);
	std::string getDescription();
	Card(const int& pos_x, const int& pos_y, const std::string&);

};