#include "Navigator.h"
#include "Color.h"
#include "Streamy.h"

Navigator::Navigator() : Widget(Rect(0, 0, 0, 0))
{
	update();
}

void Navigator::update()
{
	Vector screen = Game::screenSize();
	Vector world = Game::worldSize();
	
	Point origin = Point(0, screen.height - mHeight);
	
	rect() = Rect(origin, Vector((mHeight / world.height) * world.width, mHeight));
}

void Navigator::moveCamera(const Point& p)
{
	Point r = p - rect().origin;
	Vector world = Game::worldSize();
	Point worldPoint = Point(r.x * (world.width / rect().size.width), r.y * (world.height / rect().size.height));
	Game::setCameraPosition(worldPoint);
}

void Navigator::mouseDown(const SDL_MouseButtonEvent& event)
{
	Vector world = Game::worldSize();
	
	Point rpoint = Point(event.x - rect().origin.x, event.y - rect().origin.y);
	Point worldPoint = Point(rpoint.x * (world.width / rect().size.width), rpoint.y * (world.height / rect().size.height));
	Game::setCameraPosition(worldPoint);
}

void Navigator::mouseMove(const SDL_MouseMotionEvent& event)
{
	if (mMouseDown)
	{
		moveCamera(Point(event.x, event.y));
	}
}

void Navigator::drawWidget(uint64_t frame)
{
	Color(0.0, 0.1, 0.2, 0.5).set();
	glBegin(GL_QUADS);
	{
		glVertex2f(0.0, 0.0);
		glVertex2f(rect().size.width, 0.0);
		glVertex2f(rect().size.width, rect().size.height);
		glVertex2f(0.0, rect().size.height);
	}
	glEnd();
	
	Vector screen = Game::screenSize();
	Vector world = Game::worldSize();
	Point camera = Game::cameraPosition();
	
	Real fx = rect().size.width / world.width;
	Real fy = rect().size.height / world.height;
	Real dx = (screen.width / 2.0) * fx;
	Real dy = (screen.height / 2.0) * fx;
	Real tx = camera.x * fx;
	Real ty = camera.y * fy;
	
	Color(0.0, 1.0, 0.0, 0.2).set();
	glBegin(GL_QUADS);
	{
		glVertex2f(tx - dx, ty - dy);
		glVertex2f(tx + dx, ty - dy);
		glVertex2f(tx + dx, ty + dy);
		glVertex2f(tx - dx, ty + dy);
	}
	glEnd();
	
	Color(0.0, 1.0, 0.0, 0.8).set();
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(tx - dx, ty - dy);
		glVertex2f(tx + dx, ty - dy);
		glVertex2f(tx + dx, ty + dy);
		glVertex2f(tx - dx, ty + dy);
	}
	glEnd();
}
