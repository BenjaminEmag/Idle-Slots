#pragma once
class Game 
{
private:
	static Game* mpsInstance;
	Game() {};
	~Game();

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