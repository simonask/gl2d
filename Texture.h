#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <SDL/SDL.h>
#include <OpenGL/gl.h>

#include <string>

#include "Vector.h"

class Texture
{
private:
	void generate();
protected:
	Vector mSize;
	
	GLint mInternalFormat;
	GLenum mFormat;
	GLuint mName;
	SDL_Surface* mImage;
	
	Texture();
public:
	virtual ~Texture();
	
	inline GLuint name() const { return mName; }
	inline Vector size() const { return mSize; }
	
	static Texture* fromFile(const std::string& filename);
};

#endif /* _TEXTURE_H_ */
