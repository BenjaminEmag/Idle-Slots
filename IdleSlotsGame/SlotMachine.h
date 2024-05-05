#include <vector>
#include "Reel.h"
#include <raylib.h>
#include <string>
#include "GraphicsObjectManager.h"

class GraphicsObjectManager;
class GraphicsObject;

class SlotMachine
{
public:
    enum State
    {
        START,
        SPIN,
        STOP
    };

    SlotMachine(Vector2 position, int numReels, int lenght, GraphicsObjectManager* graphicsObjManager, const std::string key, Vector2 machinDim, Vector2 spriteDim, int spriteCount);
    void start();
    void spin();
    void stop();
    void draw();
    void update();
    void setState(State state) { mState = state; };
private:
    Rectangle mRectangle; // Defines size of slot machine 
    Vector2 mPos;
    std::vector<Reel> mReels;
    State mState = START;
    GraphicsObjectManager* mGrapicObjManagers;
    int mNumReels;
};