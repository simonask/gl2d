#include "YinYang.h"
#include "Color.h"

void drawCircle(GLenum polygonType, Point center, Real radius, int segments = 0, Radians arcOffset = 0.0, Radians arc = 2.0*Math::PI)
{
	if (segments == 0)
		segments = (int)(Math::PI * radius);	// pretty darn smooth!
	glPushMatrix();
	glTranslatef(center.x, center.y, 0.0);
	glBegin(polygonType);
	{
		for (int i = 0; i < segments; ++i)
		{
			Real x = cos((Real)arcOffset + (Real)arc / segments * i) * radius;
			Real y = sin((Real)arcOffset + (Real)arc / segments * i) * radius;
			glVertex3f(x, y, 0);
		}
	}
	glEnd();
	glPopMatrix();
}

void YinYang::render(uint64_t frame)
{
	Degrees rotationPerFrame = 2.0;
	Degrees stepSize = 360.0 / rotationPerFrame;
	Degrees rotation = (frame % (uint64_t)stepSize) / stepSize * 360.0;

	glTranslatef(mCenter.x, mCenter.y, -mRadius * 2);
	glRotatef(rotation, 0.1, 0.1, 1);
	
	
	// Half cirlces
	int segments = (int)(Math::PI * mRadius) / 2;
	Color(1.0, 1.0, 1.0).set();
	drawCircle(GL_POLYGON, Point(0, 0), mRadius, 0, 0.0, Math::PI);
	Color(0.0, 0.0, 0.0).set();
	drawCircle(GL_POLYGON, Point(0, 0), mRadius, 0, Math::PI, Math::PI);
	
	// Indents
	Color(1.0, 1.0, 1.0).set();
	drawCircle(GL_POLYGON, Point(-mRadius/2, 0.0), mRadius/2);
	Color(0.0, 0.0, 0.0).set();
	drawCircle(GL_POLYGON, Point(mRadius/2, 0.0), mRadius/2);
	
	// Drops of complement
	Color(1.0, 1.0, 1.0).set();
	drawCircle(GL_POLYGON, Point(mRadius/2, 0.0), mRadius/8);
	Color(0.0, 0.0, 0.0).set();
	drawCircle(GL_POLYGON, Point(-mRadius/2, 0.0), mRadius/8);
	
	// Outline
	Color(1.0, 1.0, 1.0).set();
	drawCircle(GL_LINE_LOOP, Point(0, 0), mRadius);
}