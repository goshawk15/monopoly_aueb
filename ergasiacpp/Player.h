#pragma once
#include "Gameobject.h"
#include <string>
#include "Asset.h"

class Player : public GameObject{
private:
	float pos_x, pos_y, prevPosx, prevPosy;
	float startingPos_x, startingPos_y;
	float balance;
	std::string icon_name;
	bool active = false;
	int i = 0;

public:
	void update() override;
	void draw() override;
	void init() override;

	float getBalance();
	void setBalance(float x);

	float getPos_x();
	float getPos_y();
	void setPos_x(float x);
	void setPos_y(float y);

	float getprevPos_x();
	float getprevPos_y();
	void setprevPos_x(float x);
	void setprevPos_y(float y);

	void setActive(bool x);
	
	Player(const std::string&);
	Player(const std::string&, float y);

	bool contains(float x, float y);
};