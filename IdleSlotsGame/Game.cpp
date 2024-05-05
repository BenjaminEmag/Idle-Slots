#include "Game.h"
#include "raylib.h"
#include <cassert>

#include "GraphicsObjectManager.h"

#include "SlotMachine.h"

Game* Game::mpsInstance = nullptr;

Game::~Game()
{
	cleanup();
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

	mpGraphicsObjectManager->cleanup();
	delete mpGraphicsObjectManager;

	mInit = false;
}


void Game::startLoop()
{
	while (!WindowShouldClose())
	{
		pollInputs();
		update();
		BeginDrawing();
		DrawFPS(10, 0);

		draw();
		ClearBackground(RAYWHITE);

		EndDrawing();
	}
}

void Game::init(int width, int height, int fps) 
{
	mWidth = width;
	mheight = height;

	mpGraphicsObjectManager = new GraphicsObjectManager();
	mpGraphicsObjectManager->init();



	//Start Window
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);
	InitWindow(width, height, "Idle Slots");

	createSlotMachine();

	mInit = true;
}

void Game::createSlotMachine()
{
	Vector2 pos{ GetScreenWidth() * 0.4 , GetScreenHeight() * 0.4 };

	const std::string KEY = "slotmachine";
	const std::string ASSETS_FOLDER = R"(..\Assets\)";
	const std::string SLOT_FILENAME = R"(SlotSheets.png)";

	int numReels = 3;
	int lenght = 3;
	int spriteCount = 4;

	Vector2 spriteDimension{ 96, 96 };

	Vector2 machineDimesion{ spriteDimension.x * numReels, spriteDimension.y * lenght };
	mpGraphicsObjectManager->createAndManageGraphics(KEY, ASSETS_FOLDER + SLOT_FILENAME);


	mSlotMachine = new SlotMachine(pos, numReels, lenght, mpGraphicsObjectManager, KEY, machineDimesion, spriteDimension, spriteCount);

}

void Game::pollInputs()
{
	if (IsKeyPressed(KEY_SPACE))
		mSlotMachine->setState(SlotMachine::SPIN);
}

void Game::update()
{
	mSlotMachine->update();
}

void Game::draw()
{
	// Debug Box
	Vector2 pos{ GetScreenWidth() * 0.4 , GetScreenHeight() * 0.4 };
	int numReels = 3;
	int lenght = 3;
	int spriteCount = 4;
	Vector2 spriteDimension{ 96, 96 };
	Vector2 machineDimesion{ spriteDimension.x * numReels, spriteDimension.y * lenght };
	DrawRectangle(pos.x, pos.y, machineDimesion.x, machineDimesion.y, BLUE);



	mSlotMachine->draw();
}
