#include "Questionmark.h"

//returns the fee applied to the player
int Questionmark::getFee() {
	return fee;
}

// Only Constructor for Questionmark
Questionmark::Questionmark(const int& pos_x, const int& pos_y, const std::string & description, const int& fee) :Card(pos_x, pos_y, description), fee(fee) {}
