#include "Texture.h"
#include <iostream>

using namespace std;

#include <OpenGL/glu.h>
#include <SDL_image/SDL_image.h>

Texture::Texture() : mInternalFormat(GL_RGBA8), mFormat(GL_RGBA)
{
}

Texture::~Texture()
{
	SDL_FreeSurface(mImage);
	// Does OpenGL need us to unregister the texture name, so it can reclaim VRAM??
}

void Texture::generate()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);	// For RGBA-alignment
	glGenTextures(1, &mName);
	glBindTexture(GL_TEXTURE_2D, mName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	switch (mImage->format->BytesPerPixel)
	{
		default:
			cerr << "WARNING: Unknown pixel format (" << mImage->format->BytesPerPixel << " bytes per pixel) -- using RGB." << endl;
		case 3:
			mFormat = GL_RGB;
			break;
		case 4:
			mFormat = GL_RGBA;
			break;
	}
	
	GLenum error;
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, mImage->w, mImage->h, mFormat, GL_UNSIGNED_BYTE, mImage->pixels);
	if (error = glGetError())
		cerr << "Could not generate texture! OpenGL error " << error << endl;
}

Texture* Texture::fromFile(const string& filename)
{
	Texture* tex = new Texture();
	SDL_RWops* textureFile = SDL_RWFromFile(filename.c_str(), "rb");
	tex->mImage = IMG_Load_RW(textureFile, 1);
	tex->mSize = Vector(tex->mImage->w, tex->mImage->h);
	
	tex->generate();
	
	cout << "Loaded texture: " << filename << " with name " << tex->mName << " and dimensions " << tex->mSize.width << "x" << tex->mSize.height << endl;
	
	return tex;
}
