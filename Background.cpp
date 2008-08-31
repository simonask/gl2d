#include "Background.h"
#include "Game.h"
#include "Color.h"
#include "Streamy.h"

Background::Background() : mTexture(NULL)
{
	
}

void Background::render(uint64_t frames)
{
	Point topleft = Game::screenToWorldCoord(Point(0.0, 0.0));
	Point bottomright = Game::screenSize();
	
	glTranslatef(topleft.x, topleft.y, 0.0);
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, Color(1.0, 1.0, 1.0, mAlpha).transformed());
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, mTexture->name());
	
	Point t1 = Point(
		(topleft.x / Game::worldSize().width) * ((mTexture->size().width - mClipSize.width) / mTexture->size().width),
		(topleft.y / Game::worldSize().height) * ((mTexture->size().height - mClipSize.height) / mTexture->size().height)
	);
	Point t2 = t1 + Point(mClipSize.width / mTexture->size().width, mClipSize.height / mTexture->size().height);
	
	glBegin(GL_QUADS);
	{
		// bottom left
		glTexCoord2f(t1.x, t2.y);
		glVertex2f(0.0, bottomright.y);
		
		// bottom right
		glTexCoord2f(t2.x, t2.y);
		glVertex2f(bottomright.x, bottomright.y);
		
		// top right
		glTexCoord2f(t2.x, t1.y);
		glVertex2f(bottomright.x, 0.0);
		
		// top left
		glTexCoord2f(t1.x, t1.y);
		glVertex2f(0.0, 0.0);
	}
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
}

Rect Background::boundingRect() const
{
	return Rect(Point(0.0, 0.0), Game::worldSize());
}
