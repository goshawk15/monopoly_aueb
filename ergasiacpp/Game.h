#pragma once
#include "graphics.h"
#include "Config.h"
#include "Player.h"
#include "Asset.h"
#include "Questionmark.h"

class Game {
	// the Game has:
	// 
	// 2 players

	typedef enum{ STATUS_PLAYING, STATUS_START, STATUS_OVER} status_t;
	status_t status = STATUS_START;

protected:


	int counter = 0;

	Player *player1 = nullptr;
	Player *player2 = nullptr;

	Player* cur_player = nullptr;
	Player* next_player = nullptr;
	Player* active_player = nullptr;

	// 28 cards in total
	
	// 20 asset Cards
	// Brown ( region = 0 )
	Asset brown1 = Asset(670, 479, "WC", 45, 0);
	Asset brown2 = Asset(607, 479, "Elevator", 50, 0);
	// Ligh Blue ( region = 1 )
	Asset lightblue1 = Asset(470, 479, "LAB_1", 70, 1);
	Asset lightblue2 = Asset(402, 479, "LAB_2", 75, 1);
	Asset lightblue3 = Asset(332, 479, "LAB_3", 80, 1);
	// Pink ( region = 2 )
	Asset pink1 = Asset(258, 415, "IT_secr", 150, 2);
	Asset pink2 = Asset(258, 350, "DET_secr", 140, 2);
	// Orange ( region = 3 )
	Asset orange1 = Asset(258, 220, "A_21", 100, 3);
	Asset orange2 = Asset(258, 154, "A_22", 100, 3);
	Asset orange3 = Asset(258, 87, "A_23", 100, 3);
	// Red ( region = 4 )
	Asset red1 = Asset(332, 22, "Amph_A", 250, 4);
	Asset red2 = Asset(402, 22, "Amph_B", 200, 4);
	Asset red3 = Asset(470, 22, "Amph_C", 200, 4);
	// Yellow ( region = 5 )
	Asset yellow1 = Asset(607, 22, "Library", 180, 5);
	Asset yellow2 = Asset(670, 22, "Restaurant", 170, 5);
	// Green ( region = 6 )
	Asset green1 = Asset(742, 87, "D_21", 120, 6);
	Asset green2 = Asset(742, 154, "D_22", 120, 6);
	Asset green3 = Asset(742, 220, "D_23", 120, 6);
	// Blue ( region = 7 )
	Asset blue1 = Asset(742, 350, "Amph_Derigni", 300, 7);
	Asset blue2 = Asset(742, 415, "Amph_Antoniadou", 300, 7);

	std::vector<Asset> assets = { brown1,brown2,lightblue1,lightblue2,lightblue3,pink1,pink2,orange1,orange2,orange3,red1,red2,red3,yellow1,yellow2,green1,green2,green3,blue1,blue2 };
	// initialize the pointer
	Asset* cur_asset = &assets[1];

	// AND
	// 8 questionmark Cards
	Questionmark q1 = Questionmark(538, 479, "You received Ioannis Kabouras Award GET 100 EUR", 100);
	Questionmark q2 = Questionmark(258, 278, "OPA decides to clean the graffitis  PAY 50 EUR", -50);
	Questionmark q3 = Questionmark(538, 22, "For the monthly meals of the other player  PAY 40 EUR", -40);
	Questionmark q4 = Questionmark(742, 278, "Your parents are happy with your grades  GET 20 EUR", 20);
	Questionmark q5 = Questionmark(538, 479, "IT needs more computers  PAY 50 EUR", -50);
	Questionmark q6 = Questionmark(258, 278, "A student wants your help with his project  GET 80 EUR", 80);
	Questionmark q7 = Questionmark(538, 22, "A student wants your notes, GET 30 EUR", 30);
	Questionmark q8 = Questionmark(742, 278, "For your friends coffee  PAY 10 EUR ", -10);

	std::vector<Questionmark> questionmarks = { q1,q2,q3,q4,q5,q6,q7,q8 };

public:
	
	void update();
	void draw();
	void init();

	void updateLevelScreen();
	void updateStartScreen();

	void drawLevelScreen();
	void drawStartScreen();
	void drawOverScreen();
	

	Game();
	~Game();
};
