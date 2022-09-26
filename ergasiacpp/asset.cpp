#include "Asset.h"
#include "graphics.h"
using namespace graphics;

void Asset::draw()
{
	Brush br;
	if (region == 0) {
		br.fill_color[0] = 0.58f;
		br.fill_color[1] = 0.32f;
		br.fill_color[2] = 0.2f;
	}
	else if(region==1)
	{
		br.fill_color[0] = 0.67f;
		br.fill_color[1] = 0.86f;
		br.fill_color[2] = 0.99f;
	}
	else if (region == 2)
	{
		br.fill_color[0] = 0.85f;
		br.fill_color[1] = 0.22f;
		br.fill_color[2] = 0.6f;
	}
	else if (region == 3)
	{
		br.fill_color[0] = 0.97f;
		br.fill_color[1] = 0.58f;
		br.fill_color[2] = 0.1f;
	}
	else if (region == 4)
	{
		br.fill_color[0] = 0.94f;
		br.fill_color[1] = 0.1f;
		br.fill_color[2] = 0.13f;
	}
	else if (region == 5)
	{
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.94f;
		br.fill_color[2] = 0;
	}
	else if (region == 6)
	{
		br.fill_color[0] = 0.15f;
		br.fill_color[1] = 0.69f;
		br.fill_color[2] = 0.36f;
	}
	else if (region == 7)
	{
		br.fill_color[0] = 0.01f;
		br.fill_color[1] = 0.44f;
		br.fill_color[2] = 0.73f;
	}
	br.fill_opacity = 0.6f;
	br.outline_opacity = 0.0f;
	drawRect(pos_x, pos_y, 71, 65, br);
}


// returns the price of the asset
int Asset::getPrice()
{
	return price;
}

// returns the region of the asset (integer from 1 to 6) 
int Asset::getRegion()
{
	return region;
}




// returns true if the asset is owned by a player

bool Asset::getIsOwned()
{
	return IsOwned;
}



// sets IsOwned true, when someone buys this asset
void Asset::setIsOwned()
{
	IsOwned = true;
}

bool Asset::getIsOwnedbyPlayer1()
{
	return IsOwnedbyPlayer1;
}

void Asset::setIsOwnedbyPlayer1()
{
	IsOwnedbyPlayer1 = true;
}


// Only Constructor for Asset objects
Asset::Asset(const int& pos_x, const int& pos_y, const std::string& description, const int& price, const int& region):Card(pos_x,pos_y,description), price(price), region(region){}
