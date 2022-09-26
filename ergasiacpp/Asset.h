#pragma once
#include "Card.h"

class Asset : public Card {

protected:
	// price = amount of cash & region = color/quality of the card
	int price, region;
	

	// IsOwned -> true if it is not available, false if it is
	bool IsOwned = false;
	bool IsOwnedbyPlayer1 = false;

public:
	void draw() override;
	int getPrice();
	int getRegion();
	int getRank();
	void upgradeRank();
	bool getIsOwned();
	void setIsOwned();
	bool getIsOwnedbyPlayer1();
	void setIsOwnedbyPlayer1();


	Asset(const int&, const int&, const std::string&, const int&, const int&);

};