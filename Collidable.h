#ifndef _COLLIDABLE_H_
#define _COLLIDABLE_H_

#include "Point.h"
#include "Rect.h"
#include "GeometryMath.h"
#include <vector>

class Collidable;

typedef vector<Collidable*> Collidables;

class Collidable
{
public:
	static const Collidables& all();
	static Collidables within(const Rect& rect);
	
	Collidable();
	virtual ~Collidable();
	
	virtual bool contains(const Point& p) const = 0;
	
	/*
		Only called in debug mode.
	*/
	virtual void render(uint64_t frame) = 0;
	
	virtual Vector surfaceNormal(const Point& p) const = 0;
};

#endif /* _COLLIDABLE_H_ */
