#include "Game.h"
#include "raylib.h"
#include <cassert>
#include "GraphicsObjectManager.h"
#include "SlotMachine.h"
#include "HUD.h"
#include "Money.h"
#include "SlotMachineState.h"
#include <iostream>

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
		draw();
	}
}

void Game::init(int width, int height, int fps) 
{
	mWidth = width;
	mheight = height;

	mpGraphicsObjectManager = new GraphicsObjectManager();
	mpGraphicsObjectManager->init();

	mpHud = new HUD();

	//Start Window
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);
	InitWindow(width, height, "Idle Slots");

	createSlotMachine();
	mpHud->init(mWidth, mheight, mSlotMachine->getRec());
	mInit = true;
}

void Game::createSlotMachine()
{
	Vector2 pos{ GetScreenWidth() * 0.05f , GetScreenHeight() * 0.05f };

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
		mSlotMachine->spin();

	if (IsKeyPressed(KEY_ENTER))
		mSlotMachine->showLines();
}

void Game::update()
{
	mUpdateTimer.update();

	if (mUpdateTimer.isTimerDone()) 
	{
		mSlotMachine->update();
		mUpdateTimer.startTimer(mUpdateInterval);
	}
}

void Game::draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	mSlotMachine->draw();
	mpHud->draw(HUD::GAME_INFO);

	EndDrawing();
}
