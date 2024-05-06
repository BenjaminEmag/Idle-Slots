#include <vector>
#include <raylib.h>
#include <string>
#include "SlotMachineState.h";
class GraphicsObjectManager;
class GraphicsObject;
class Reel;

class SlotMachine
{
public:
	SlotMachine(Vector2 position, int numReels, int lenght, GraphicsObjectManager* graphicsObjManager, const std::string key, Vector2 machinDim, Vector2 spriteDim, int spriteCount);
	void start();
	void spin();
	void stopSpin();
	void draw();
	void update();
	void setState(SlotMachineState state) { mState = state; };

	void calculateSpinResult();
private:
	Rectangle mRectangle; // Defines size of slot machine 
	Vector2 mPos;
	std::vector<Reel> mReels;
	SlotMachineState mState = SlotMachineState::START;
	GraphicsObjectManager* mpGrapicObjManagers = nullptr;

	int mNumReels;
	int mLenght;
	std::vector<Rectangle> mSlotSpriteRects; // defines the sprites 

	float mSpinSpeed = 50.0f;
	float mTotalSpinLenght = 1.5f;


};