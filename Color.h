#ifndef _COLOR_H_
#define _COLOR_H_

#include <OpenGL/gl.h>

struct Color
{
	union
	{
		GLfloat colors[4];
		struct { GLfloat r, g, b, a; };
	};
	
	Color(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _a = 1.0)
	{
		r = _r; g = _g; b = _b; a = _a;
	}
	
	void set() const
	{
		glColor4f(r, g, b, a);
	}
	
	inline operator const GLfloat*() const
	{
		return colors;
	}
};

#endif /* _COLOR_H_ */
