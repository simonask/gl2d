#include "Widget.h"
#include "Game.h"
#include <iostream>
using namespace std;

Widget::Widget(const Rect& rect) :
	EventListener(SDL_MOUSEEVENTMASK | SDL_KEYEVENTMASK),
	mRect(rect),
	mMouseOver(false), mMouseDown(false)
{
}

void Widget::render(uint64_t frame)
{
	Point worldPos = Game::screenToWorldCoord(mRect.origin);
	glTranslatef(worldPos.x, worldPos.y, 0);
	drawWidget(frame);
}

void Widget::drawWidget(uint64_t frame)
{
	// Dummy implementation
	glBegin(GL_QUADS);
	{
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(mRect.size.x, 0.0, 0.0);
		glVertex3f(mRect.size.x, mRect.size.y, 0.0);
		glVertex3f(0.0, mRect.size.y, 0.0);
	}
	glEnd();
}

bool Widget::handleEvent(const SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_MOUSEMOTION:
		{
			Point mouseCoord(event.motion.x, event.motion.y);
			bool contained = mRect.contains(mouseCoord);
			if (contained && !mMouseOver)
			{
				mMouseOver = true;
				mouseOver(event.motion);
			}
			else if (!contained && mMouseOver)
			{
				mMouseOver = false;
				mouseOut(event.motion);
			}
			return false;
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		if (mMouseOver)
		{
			mMouseDown = true;
			mouseDown(event.button);
			return true;
		}
		return false;
		case SDL_MOUSEBUTTONUP:
		if (mMouseDown)
		{
			mMouseDown = false;
			mouseUp(event.button);
			return true;
		}
		return false;
		/*
			TODO: Keys
		*/
	}
}
