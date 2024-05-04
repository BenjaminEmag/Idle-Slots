#include "Game.h"
#include "raylib.h"
#include <cassert>

Game* Game::mpsInstance = nullptr;

Game::~Game()
{
}

void Game::createInstance()
{
	if (mpsInstance == nullptr)
		mpsInstance = new Game;
}

void Game::destroyInstance()
{
	delete mpsInstance;
	mpsInstance = nullptr;
}

Game* Game::getInstance()
{
	assert(mpsInstance != nullptr);
	return mpsInstance;
}

void Game::cleanup()
{
	if (mInit == false)
		return;


	mInit = false;
}


void Game::startLoop()
{
	while (!WindowShouldClose())
	{
		BeginDrawing();

		DrawFPS(10, 0);
		ClearBackground(RAYWHITE);

		EndDrawing();
	}
}

void Game::init(int width, int height, int fps)
{
	//Start Window
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(fps);
	InitWindow(width, height, "Idle Slots");

	mInit = true;
}


