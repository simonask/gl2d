#include "RotatingTriangle.h"
#include "Game.h"
#include "Color.h"
#include <iostream>
using namespace std;

#define SIZE 50

RotatingTriangle::RotatingTriangle() : EventListener(SDL_MOUSEMOTIONMASK), accumulator(70)
{
	state.x = state.y = 0.0;
}

void RotatingTriangle::render(uint64_t frame)
{
//	accumulator.restore(state, frame);
	
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(state.x, state.y, 0.0);
	
	Real stepsize = 360.0 / 5.0;
	Degrees rotation = (frame % (uint64_t)stepsize) / stepsize * 360.0;
	glRotatef((float)rotation, 0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES);
	{
		Color(1.0, 1.0, 1.0).set();
		glVertex2f(SIZE, SIZE);
		glVertex2f(-SIZE, SIZE);
		glVertex2f(SIZE, -SIZE);
	}
	glEnd();
}

bool RotatingTriangle::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_MOUSEMOTION)
	{
		Point screenCoord(event.motion.x, event.motion.y);
		Point worldCoord = Game::screenToWorldCoord(screenCoord);
		state.x = worldCoord.x;
		state.y = worldCoord.y;
	}
	return false;
}

Rect RotatingTriangle::boundingRect() const
{
	Rect r;
	r.origin = Point(state.x - SIZE, state.y - SIZE);
	r.size = Vector(2 * SIZE, 2 * SIZE);
	return r;
}
