#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "EventListener.h"
#include "Point.h"

#include <SDL/SDL.h>
#include <vector>

class Game
{
private:
	Game();
	Game(const Game&);
	
	static bool done;
	static float fps;
	static std::vector<EventListener*> mListeners;
	static Point mCameraPosition;
	
	static void handleEvents();
	static void update();
	static void renderPass(uint64_t frame);
	static void render();
	static void calculateFps();
public:
	// TODO: Put these in EventListener as statics
	static void registerEventListener(EventListener* object);
	static void unregisterEventListener(EventListener* object);
	
	static uint64_t currentFrame();
	static uint64_t framerate();

	inline static Point cameraPosition() { return mCameraPosition; }
	static void setCameraPosition(const Point& point, bool smooth = true);
	
	inline static Point screenToWorldCoord(const Point& p) { return p + mCameraPosition; }
	inline static Point worldToScreenCoord(const Point& p) { return p - mCameraPosition; }
	
	static int run(int argc, char* argv[]);
};

#endif /* _APPLICATION_H_ */