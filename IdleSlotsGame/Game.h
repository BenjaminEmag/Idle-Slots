#pragma once
#include "Timer.h"

class GraphicsObjectManager;
class SlotMachine;
class HUD;

class Game 
{
private:
	static Game* mpsInstance;
	Game() {};
	~Game();

	GraphicsObjectManager* mpGraphicsObjectManager = nullptr;
	HUD* mpHud = nullptr;
	SlotMachine* mSlotMachine = nullptr;

	void pollInputs();
	void update();
	void draw();
	void createSlotMachine();

	int mWidth = 0.0;
	int mheight = 0.0;

	Timer mUpdateTimer;
	const float mUpdateInterval = 1.0 / 60.0f;
public:
	static void createInstance();
	static void destroyInstance();
	static Game* getInstance();
	void cleanup();
	void startLoop();
	void init(int width, int height, int fps);
	bool mInit = false;
};
extern Game* gpGame;