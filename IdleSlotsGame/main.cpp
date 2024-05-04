#include "raylib.h"
#include "Game.h"

int main(void) 
{
	const int SCREEN_WIDTH = 1600;
	const int SCREEN_HEIGHT = 900;
	const int TARGET_FPS = 60;

	Game::createInstance();
	Game* pGame = Game::getInstance();

	pGame->init(SCREEN_WIDTH, SCREEN_HEIGHT, TARGET_FPS);

	pGame->startLoop();
	pGame->cleanup();
	pGame->destroyInstance();

	CloseWindow();
}
