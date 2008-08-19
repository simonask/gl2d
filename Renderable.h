#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

#include <OpenGL/gl.h>

#include "Rect.h"

#define DRAW_BOUNDING_BOXES 1

class Renderable
{
public:
	/*
		Renders the object to screen. This is declared const, because it
		may be called any number of times in a rendering pass, so it should
		not modify the state of the object.
		
		This function is only called if the object is determined to be on
		screen. This is determined by the result of boundingRect().
	*/
	virtual void draw() const = 0;
	
	/*
		Return a rectangle that is guaranteed to contain this object. This
		is used to determine whether or not the object should be allowed to
		perform rendering, so it is important that draw() does not perform
		rendering outside this rectangle.
	*/
	virtual Rect boundingRect() const = 0;
	
	/*
		Optional. This is called exactly once for all objects on screen. Use this
		to implement animation and whatever you may like.
		
		boundingRect() is used to determine whether this object is on screen, and
		thus, whether it should be updated.
	*/
	virtual void update() {}
};

#endif /* _RENDERABLE_H_ */
