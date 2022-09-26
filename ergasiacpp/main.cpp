#include "graphics.h"
#include "Game.h"
#include "Config.h"
#include "Questionmark.h"
#include <iostream>

using namespace graphics;
using namespace std;

void update(float ms)
{
    Game* game = reinterpret_cast<Game*>(getUserData());
    game->update();

}

void draw()
{
    Game* game = reinterpret_cast<Game*>(getUserData());
    game->draw();
}

int main()
{
    Game maingame;
    createWindow(WINDOW_WIDTH, WINDOW_HEIGHT,"MonOPAly");

    setUserData(&maingame);

    setDrawFunction(draw);
    setUpdateFunction(update);

    setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    setCanvasScaleMode(CANVAS_SCALE_FIT);

    maingame.init();
    startMessageLoop();

    return 0;

}