#include "BoxCollider.h"
#include "Renderable.h"
#include "Color.h"

void BoxCollider::render(uint64_t frame)
{
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(mRect.origin.x, mRect.origin.y, 0.0);
	glRotatef(mRotation, 0.0, 0.0, 1.0);
	
	Color(0.0, 0.0, 0.5, 0.8).set();
	glBegin(GL_QUADS);
	{
		glVertex2f(0.0, 0.0);
		glVertex2f(mRect.size.width, 0.0);
		glVertex2f(mRect.size.width, mRect.size.height);
		glVertex2f(0.0, mRect.size.height);
	}
	glEnd();
	
	Color(0.0, 0.1, 0.8, 0.8).set();
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(0.0, 0.0);
		glVertex2f(mRect.size.width, 0.0);
		glVertex2f(mRect.size.width, mRect.size.height);
		glVertex2f(0.0, mRect.size.height);
	}
	glEnd();
}


bool BoxCollider::contains(const Point& p) const
{
	if (mRotation == 0.0)
		return mRect.contains(p);
	
	Point transformed = p.rotateAround(mRect.origin, -mRotation);
	return mRect.contains(transformed);
}

Vector BoxCollider::surfaceNormal(const Point& p) const
{
	Point transformed = p.rotateAround(mRect.origin, -mRotation);
	
}
