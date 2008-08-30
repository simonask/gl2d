#ifndef _NAVIGATOR_H_
#define _NAVIGATOR_H_

#include "Widget.h"

class Navigator : public Widget
{
private:
	Real mHeight;
	
	void moveCamera(const Point& p);
public:
	Navigator();
	virtual ~Navigator() {}
	
	inline Real height() const { return mHeight; }
	inline void setHeight(Real h) { mHeight = h; }
	void update();
	void drawWidget(uint64_t frame);
	void mouseDown(const SDL_MouseButtonEvent&);
	void mouseMove(const SDL_MouseMotionEvent&);
	Rect boundingRect() const { return Rect(Point(0, 0), Game::worldSize()); }
};

#endif /* _NAVIGATOR_H_ */
