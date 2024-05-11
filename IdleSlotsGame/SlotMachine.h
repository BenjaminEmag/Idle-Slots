#include <vector>
#include <raylib.h>
#include <string>
#include "SlotMachineState.h"
#include <map>
#include <utility>
#include "GraphicsObjectManager.h"
#include "Reel.h"
#include "EventListener.h"

class GraphicsObjectManager;
class GraphicsObject;
class Reel;

class SlotMachine : EventListener
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
	void showLines();
	Rectangle getRec() { return mRectangle; };
private:
	Rectangle mRectangle; // Defines size of slot machine 
	Vector2 mPos;
	std::vector<Reel> mReels;
	SlotMachineState mState = SlotMachineState::START;
	GraphicsObjectManager* mpGrapicObjManagers = nullptr;

	int mNumReels;
	int mLenght;
	std::vector<Rectangle> mSlotSpriteRects; // defines the sprites 

	// int is row count, vector2's describes end point and start point
	std::unordered_map<int, std::pair<Vector2, Vector2>> mLines;
	
	float mSpinSpeed = 20.0f;
	float mTotalSpinLenght = 5.0f;

	bool mShowLines = false;
	void insertLineFromRow(int row);
	Rectangle getRectFromRow(int row);
	void handleEvent(const Event& theEvent);

	void handleClick();
};