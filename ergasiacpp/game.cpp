#include "Game.h"
#include "graphics.h"
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <random>

using namespace graphics;
int counter = 0 , i, price;
bool isOwnedbyPlayer1 = false, ongoingPayment = false, cantpurchase = false, feetoplayer = false, gameover = false;
bool not_q = true;
std::string desc,q_desc="";

// update()
void Game::update() {
	if (status == STATUS_START)
	{
		updateStartScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		updateLevelScreen();
	}
}

// draw()
void Game::draw() {
	if (status == STATUS_START)
	{
		drawStartScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		drawLevelScreen();
	}
	else
		drawOverScreen();
}

// init()
void Game::init() {
	player1 = new Player("cap.png");
	player1->setPos_x(730);
	player1->setPos_y(450);
	player1->setBalance(700);
	player1->setprevPos_x(730);
	player1->setprevPos_y(450);
	
	player2 = new Player("car.png");
	player2->setPos_x(730);
	player2->setPos_y(480);
	player2->setBalance(700);
	player2->setprevPos_x(730);
	player2->setprevPos_y(480);

	setFont(std::string(ASSET_PATH) + "font.ttf");
	playMusic(std::string(ASSET_PATH) + "soundtrack.mp3",0.1f,false,4000);

}

void Game::updateStartScreen()
{
	if (getKeyState(SCANCODE_RETURN))
		status = STATUS_PLAYING;

}

void Game::drawStartScreen()
{
	Brush br;
	br.texture = std::string(ASSET_PATH) + "board.png";
	br.outline_opacity = 0.0f;
	drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	
	char info[40];
	sprintf_s(info, "Press ENTER to start");
	drawText(CANVAS_WIDTH / 2 - 115, CANVAS_HEIGHT / 2 - 30, 30, info, br);
}

void Game::updateLevelScreen()
{
	MouseState ms;
	getMouseState(ms);
	float mx = windowToCanvasX(ms.cur_pos_x);
	float my = windowToCanvasY(ms.cur_pos_y);

	if (counter % 2 == 0)
	{
		cur_player = player1;
		next_player = player2;
	}
	else
	{
		cur_player = player2;
		next_player = player1;
	}

	if (cur_player->contains(mx, my))
		active_player = cur_player;

	//moving a player
	if (ms.dragging && active_player)
	{
		if (mx > 225 && mx < 772 && my < 490 && my > 10) //restricting the player within the borders
		{
			if (my > 445 || my < 40 && mx >300 && mx < 710 || mx < 300 || mx >710)
			{
				if (mx < active_player->getprevPos_x() && my > 445 || mx < 300 && my < active_player->getprevPos_y() || my < 40 && mx > active_player->getprevPos_x() || mx > 710 && my > active_player->getprevPos_y())
				{
					active_player->setPos_x(mx);
					active_player->setPos_y(my);
					desc = "";
				}
			}
		}
	}

	if (ms.button_left_released && active_player)
	{
		not_q = true;
		cur_player->setprevPos_x(mx);
		cur_player->setprevPos_y(my);

		// "shuffle" the cards (just change the position)
		
		for (int i = 0; i < 20; i++)
		{
			size_t j = i + rand() / (RAND_MAX / (20 - i) + 1);
			float tempX = assets[j].getX();
			float tempY = assets[j].getY();
			assets[j].setX(assets[i].getX());
			assets[j].setY(assets[i].getY());
			assets[i].setX(tempX);
			assets[i].setY(tempY);
		}

		// if the player is on a Questionmark card
		if ((mx < 570 && mx>480) || (my < 320 && my>255))
		{
			not_q = false;
			// get a random Questionmark card
			size_t random_pos = i + rand() / (RAND_MAX / (8 - i) + 1);
			q_desc = questionmarks.at(random_pos).getDescription();

			if (cur_player == player1)
			{
				player1->setBalance(player1->getBalance() + questionmarks.at(random_pos).getFee());
			}
			else
			{
				player2->setBalance(player2->getBalance() + questionmarks.at(random_pos).getFee());
			}
			// if it is a GET task
			if (questionmarks.at(random_pos).getFee() > 0)
			{
				playSound(std::string(ASSET_PATH) + "good.mp3", 0.3f, false);
			}
			// if it is a PAY task
			else
			{
				playSound(std::string(ASSET_PATH) + "bad.mp3", 0.3f, false);
			}
		}
		// else he is on an Asset card
		else
		{
			for (int i = 0; i < 20; i++)
			{
				if (mx > assets[i].getX() - 30 && mx<assets[i].getX() + 40 && my>assets[i].getY() - 40 && my < assets[i].getY() + 30) {
					cur_asset = &assets[i];
					desc = cur_asset->getDescription();
					price = cur_asset->getPrice();
					isOwnedbyPlayer1 = cur_asset->getIsOwnedbyPlayer1();
					ongoingPayment = true;
					cantpurchase = false;
					feetoplayer = false;
				}
			}
		}

		counter++;
		active_player->setActive(false);
		active_player = nullptr;

		if (next_player->getBalance() <= 0)
		{
			status = STATUS_OVER;
			gameover = true;
		}
	}

	if (not_q)
	{
		// if the property is owned
		if (cur_asset->getIsOwned() && ongoingPayment)
		{
			playSound(std::string(ASSET_PATH) + "bad.mp3", 0.3f, false);

			// +- price*0.3 for each player (you can change it if you want the game to be faster)
			if (isOwnedbyPlayer1)
			{
				if (next_player == player1)
				{
					player1->setBalance(player1->getBalance() + (cur_asset->getPrice() * 0.3));
					player2->setBalance(player2->getBalance() - (cur_asset->getPrice() * 0.3));
					feetoplayer = true;
				}
			}
			else
			{
				if (next_player == player2)
				{
					player1->setBalance(player1->getBalance() - (cur_asset->getPrice() * 0.3));
					player2->setBalance(player2->getBalance() + (cur_asset->getPrice() * 0.3));
					feetoplayer = true;
				}
			}
			ongoingPayment = false;
		}
		// if it is available
		else if (ongoingPayment && !cur_asset->getIsOwned())
		{
			if (getKeyState(SCANCODE_Y))
			{
				playSound(std::string(ASSET_PATH) + "good.mp3", 0.3f, false);
				// next_player = the player who just left the left mouse click
				// ex.: if player 1 just played -> cur_player = player2 & next_player = player1
				if (next_player->getBalance() >= price)
				{
					ongoingPayment = false;
					cur_asset->setIsOwned();
					next_player->setBalance(next_player->getBalance() - cur_asset->getPrice());

					if (next_player == player1)
						cur_asset->setIsOwnedbyPlayer1();
				}
				else
					cantpurchase = true;
			}
		}

	}
}

void Game::drawLevelScreen()
{
	Brush br;
	br.texture = std::string(ASSET_PATH) + "board.png";
	br.outline_opacity = 0.0f;

	// draw background
	drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	br.fill_color[0] = 0;
	br.fill_color[1] = 0;
	br.fill_color[2] = 0;

	char p[70];

	//draw balance & owned cards
	if (player1 && player2)
	{
		sprintf_s(p, "Balance: %6.1f  EUR", player1->getBalance());
		drawText(30, 80, 20, p, br);

		sprintf_s(p, "Balance: %6.1f  EUR", player2->getBalance());
		drawText(820, 80, 20, p, br);

		sprintf_s(p, "Assets owned");
		drawText(40, 120, 25, p, br);

		sprintf_s(p, "Assets owned");
		drawText(825, 120, 25, p, br);

		// draw Owned Asset Lists
		int ar = 0, dex = 0;
		for (int j = 0; j < 20; j++) {
			sprintf_s(p, "%s", assets[j].getDescription().c_str());

			// if asset is owned by player1
			if (assets[j].getIsOwnedbyPlayer1())
			{
				drawText(40, 150 + ar, 20, p, br);
				ar = ar + 20;
			}
			// if asset is owned by player2
			else if (!assets[j].getIsOwnedbyPlayer1() && assets[j].getIsOwned())
			{
				drawText(830, 150 + dex, 20, p, br);
				dex = dex + 20;
			}
		}
	}

	// draw asset on the board
	for (int i = 0; i < 20; i++) {
		br.fill_color[0] = 0;
		br.fill_color[1] = 0;
		br.fill_color[2] = 0;

		assets[i].draw();
		// if the asset's description is bigger than 10 letters
		if (assets[i].getDescription().length() > 10)
		{
			sprintf_s(p, "%s", assets[i].getDescription().c_str());
			drawText(assets[i].getX() - 32, assets[i].getY() - 10, 10, p, br);
		}
		else
		{
			sprintf_s(p, "%s", assets[i].getDescription().c_str());
			drawText(assets[i].getX() - 20, assets[i].getY() - 10, 12, p, br);
		}

		sprintf_s(p, "EUR  %s", std::to_string(assets[i].getPrice()).c_str());
		drawText(assets[i].getX() - 25, assets[i].getY() + 20, 15, p, br);

	}

	// draw player
	if (player1 && player2) {
		player1->draw();
		player2->draw();
	}

	// draw messages at the center of the board
	if (player1 && player2)
	{
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 1.0f;

		char info[70];

		// if game is over
		if (gameover)
		{
			sprintf_s(info, "You run out of cash!");
			drawText(348, 190, 22, info, br);
		}
		else
		{
			// if the card is an Asset
			if (not_q)
			{
				// question for acquisition
				if (cur_asset->getIsOwned() == false)
				{
					if (cantpurchase)
					{
						sprintf_s(info, "Not enough funds");
						drawText(355, 190, 37, info, br);
					}
					else
					{
						sprintf_s(info, "Do you want to Buy ");
						drawText(348, 190, 22, info, br);
						sprintf_s(info, "Y (for Yes)");
						drawText(470, 220, 15, info, br);

						br.fill_color[0] = 0;
						br.fill_color[1] = 0;
						br.fill_color[2] = 0;
						sprintf_s(info, "%s", desc.c_str());
						// if the asset's description is big
						if (desc.length() > 10)
						{
							drawText(510, 190, 20, info, br);
						}
						else
						{
							drawText(520, 190, 30, info, br);
						}
					}
				}
				// message for payment
				else
				{
					if (feetoplayer)
					{
						sprintf_s(info, "You pay%6.1f  EUR", cur_asset->getPrice() * 0.1);
						drawText(390, 190, 30, info, br);
						sprintf_s(info, "to the other player");
						drawText(420, 220, 20, info, br);
					}
					else
					{
						sprintf_s(info, "You own the property");
						drawText(350, 190, 37, info, br);
					}
				}
			}
			// else, if the card is a Questionmark
			else
			{
				std::string s = q_desc.c_str();
				std::string half = s.substr(0, s.length() - 11);
				std::string otherHalf = s.substr(s.length() - 11);

				sprintf_s(info, "%s", half.c_str());
				drawText(348, 190, 20, info, br);
				sprintf_s(info, "%s", otherHalf.c_str());
				drawText(430, 220, 28, info, br);

			}

			// whose turn it is next
			if (cur_player == player1)
				sprintf_s(info, "cap move");
			else
				sprintf_s(info, "car move");
			drawText(445, 270, 30, info, br);
		}
	}

}

void Game::drawOverScreen()
{
	Brush br;
	char p[50];
	playSound(std::string(ASSET_PATH) + "game_over.mp3", 0.1f, false);
	sprintf_s(p, "GAME OVER");
	drawText(420, 220, 37, p, br);
}

// Constructor
Game::Game()
{
}

// Destructor
Game::~Game()
{
	if (player1 && player2) {
		delete player1;
		delete player2;
	}
}