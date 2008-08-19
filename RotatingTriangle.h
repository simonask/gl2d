#ifndef _ROTATINGTRIANGLE_H_
#define _ROTATINGTRIANGLE_H_

#include "Renderable.h"
#include "EventListener.h"

class RotatingTriangle : public Renderable, public EventListener
{
private:
	float x, y;
	int rotation;
public:
	explicit RotatingTriangle() : x(0), y(0), rotation(0), EventListener(SDL_MOUSEMOTIONMASK) {}
	virtual void draw() const;
	void update();
	bool handleEvent(const SDL_Event&);
	Rect boundingRect() const;
};

#endif /* _ROTATINGTRIANGLE_H_ */
