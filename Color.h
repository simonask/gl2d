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
	
	static const Color id;
	static Color matrix;
	
	inline void set() const
	{
		glColor4f(r * matrix.r, g * matrix.g, b * matrix.b, a * matrix.a);
	}
	
	inline operator const GLfloat*() const
	{
		return colors;
	}
	
	inline Color transformed() const
	{
		return Color(r * matrix.r, g * matrix.g, b * matrix.b, a * matrix.a);
	}
	
	inline static void load(const Color& color)
	{
		matrix = color;
	}
		
	inline static void translate(const Color& color)
	{
		matrix.r *= color.r;
		matrix.g *= color.g;
		matrix.b *= color.b;
		matrix.a *= color.a;
	}
	
	inline static void loadIdentity()
	{
		matrix = id;
	}
	
	static void push();
	static void pop();
};

#endif /* _COLOR_H_ */
