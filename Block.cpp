#include "Block.h"
#include <math.h>
#include <iostream>
using namespace std;

Block::Block(const Rect& rect, Degrees rotation) :
	mColor(1.0, 1.0, 1.0, 1.0),
	mTexture(NULL),
	mRect(rect),
	mRotation(rotation)
{
	
}

void Block::draw() const
{
	glTranslatef(mRect.origin.x, mRect.origin.y, 0.0);
	glRotatef(mRotation, 0.0, 0.0, 1.0);

	if (mTexture)
	{
		glEnable(GL_TEXTURE_2D);
		glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, (GLfloat[]){1.0, 1.0, 1.0, 1.0});
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, mTexture->name());
		
		glMatrixMode(GL_TEXTURE);
#if 0
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(0.5, 0.5, 0.0);
		glRotatef(mRotation, 0.0, 0.0, 1.0);
		glTranslatef(-0.5, -0.5, 0.0);
#endif
		
		glBegin(GL_QUADS);
		{
			// bottom left
			glTexCoord2f(0.0, 1.0);
			glVertex2f(0.0, mRect.size.height);
			
			// bottom right
			glTexCoord2f(1.0, 1.0);
			glVertex2f(mRect.size.width, mRect.size.height);
			
			// top right
			glTexCoord2f(1.0, 0.0);
			glVertex2f(mRect.size.width, 0.0);
			
			// top left
			glTexCoord2f(0.0, 0.0);
			glVertex2f(0.0, 0.0);
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);

#if 0
		glPopMatrix();
#endif
	}
	else
	{
		mColor.set();
		glBegin(GL_QUADS);
		{
			glVertex2f(0.0, 0.0);
			glVertex2f(mRect.size.width, 0.0);
			glVertex2f(mRect.size.width, mRect.size.height);
			glVertex2f(0.0, mRect.size.height);
		}
		glEnd();
	}
}

Rect Block::boundingRect() const
{
	// Suboptimal, but it'll do.
	Rect r;
	Real max = fmax(mRect.size.width, mRect.size.height);
	r.origin = mRect.origin - Point(max, max);
	r.size = Vector(2*max, 2*max);
	return r;
}

static void print_matrix(double* m)
{
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			printf("%.2f  ", m[i * 4 + j]);
		}
		printf("\n");
	}
	printf("\n");
}

bool Block::contains(const Point& p) const
{
	if (mRotation == 0.0)
		return mRect.contains(p);
	
	Point transformed = p.rotateAround(mRect.origin, mRotation);
	return mRect.contains(transformed);
}
