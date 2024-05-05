#pragma once
class GraphicsObjectManager;
class SlotMachine;

class Game 
{
private:
	static Game* mpsInstance;
	Game() {};
	~Game();

	GraphicsObjectManager* mpGraphicsObjectManager = nullptr;

	SlotMachine* mSlotMachine = nullptr;

	void pollInputs();
	void update();
	void draw();
	void createSlotMachine();

	int mWidth = 0.0;
	int mheight = 0.0;
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