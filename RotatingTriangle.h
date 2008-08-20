#ifndef _ROTATINGTRIANGLE_H_
#define _ROTATINGTRIANGLE_H_

#include "Renderable.h"
#include "EventListener.h"
#include "Accumulator.h"

class RotatingTriangle : public Renderable, public EventListener
{
private:
	struct State {
		float x, y;
	};
	State state;
	Accumulator<RotatingTriangle::State> accumulator;
public:
	explicit RotatingTriangle();
	virtual void render(uint64_t frame);
	bool handleEvent(const SDL_Event&);
	Rect boundingRect() const;
};

#endif /* _ROTATINGTRIANGLE_H_ */
