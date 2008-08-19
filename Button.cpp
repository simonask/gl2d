#include "Button.h"
#include <iostream>
using namespace std;

#include "Game.h"

Button::Button() :
	Widget(Rect(50, 50, 70, 80)),
	color(1.0, 0.0, 0.0)
{
}

void Button::drawWidget() const
{
	glBegin(GL_QUADS);
	{
		color.set();
		glVertex2f(0.0, 0.0);
		glVertex2f(width(), 0.0);
		glVertex2f(width(), height());
		glVertex2f(0.0, height());
	}
	glEnd();
}

void Button::mouseOver(const SDL_MouseMotionEvent& event)
{
	color = Color(0.0, 1.0, 0.0);
	cout << "Mouse over button!" << endl;
}

void Button::mouseOut(const SDL_MouseMotionEvent& event)
{
	color = Color(1.0, 0.0, 0.0);
	cout << "Mouse left button!" << endl;
}

void Button::mouseDown(const SDL_MouseButtonEvent& event)
{
	Game::setCameraPosition(Game::cameraPosition () + Point(2, 2));
	cout << "BUTTON CLICKED!" << endl;
}

void Button::mouseUp(const SDL_MouseButtonEvent& event)
{
	cout << "Button UP!" << endl;
}
