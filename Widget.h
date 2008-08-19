#ifndef _WIDGET_H_
#define _WIDGET_H_

#include "Game.h"
#include "Renderable.h"
#include "EventListener.h"
#include "Rect.h"

class Widget : public Renderable, public EventListener
{
private:
	Rect mRect;
protected:
	bool mMouseOver;
	bool mMouseDown;
public:
	explicit Widget(const Rect&);
	const Rect& rect() const { return mRect; }
	Rect& rect() { return mRect; }
	
	inline Real x() const { return mRect.origin.x; }
	inline Real y() const { return mRect.origin.y; }
	inline Real width() const { return mRect.size.x; }
	inline Real height() const { return mRect.size.y; }
	
	void draw() const;
	bool handleEvent(const SDL_Event& event);
	Rect boundingRect() const { return mRect; }
	
	virtual void drawWidget() const;
	virtual void mouseOver(const SDL_MouseMotionEvent&) {}
	virtual void mouseOut(const SDL_MouseMotionEvent&) {}
	virtual void mouseDown(const SDL_MouseButtonEvent&) {}
	virtual void mouseUp(const SDL_MouseButtonEvent&) {}
};

#endif /* _WIDGET_H_ */
