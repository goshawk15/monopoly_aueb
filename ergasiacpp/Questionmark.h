#pragma once
#include "Card.h"

class Questionmark : public Card {
protected:
	// fee = the amount of money that the card asks or gives
	int fee;

public:
	int getFee();
	Questionmark(const int&, const int&, const std::string&, const int& fee);
};