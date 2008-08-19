#include "RotatingTriangle.h"
#include "Game.h"

#define SIZE 50

void RotatingTriangle::draw() const
{
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(x, y, 0.0);
	glRotatef((float)rotation, 0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES);
	{
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(SIZE, SIZE);
		glVertex2f(-SIZE, SIZE);
		glVertex2f(SIZE, -SIZE);
	}
	glEnd();
}

void RotatingTriangle::update()
{
	rotation = rotation + 5 % 360;
}

bool RotatingTriangle::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_MOUSEMOTION)
	{
		Point screenCoord(event.motion.x, event.motion.y);
		Point worldCoord = Game::screenToWorldCoord(screenCoord);
		x = worldCoord.x;
		y = worldCoord.y;
	}
	return false;
}

Rect RotatingTriangle::boundingRect() const
{
	Rect r;
	r.origin = Point(x - SIZE, y - SIZE);
	r.size = Vector(2 * SIZE, 2 * SIZE);
	return r;
}
