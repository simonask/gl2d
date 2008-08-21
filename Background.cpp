#include "Background.h"
#include "Game.h"
#include "Color.h"

Background::Background() : mTexture(NULL)
{
	
}

void Background::render(uint64_t frames)
{
	Point topleft = Game::screenToWorldCoord(Point(0.0, 0.0));
	glTranslatef(topleft.x, topleft.y, 0.0);
	glEnable(GL_TEXTURE_2D);
	glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, Color(1.0, 1.0, 1.0, mAlpha).transformed());
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, mTexture->name());
	
	glBegin(GL_QUADS);
	{
		Vector size = Game::screenSize();
		Point bottomright = Game::screenToWorldCoord(size);
		
		// bottom left
		glTexCoord2f(0.0, 1.0);
		glVertex2f(0.0, bottomright.height);
		
		// bottom right
		glTexCoord2f(1.0, 1.0);
		glVertex2f(bottomright.width, bottomright.height);
		
		// top right
		glTexCoord2f(1.0, 0.0);
		glVertex2f(bottomright.width, 0.0);
		
		// top left
		glTexCoord2f(0.0, 0.0);
		glVertex2f(0.0, 0.0);
	}
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
}

Rect Background::boundingRect() const
{
	return Rect(Point(0.0, 0.0), Game::worldSize());
}
