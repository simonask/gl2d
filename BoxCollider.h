#ifndef _BOXCOLLIDER_H_
#define _BOXCOLLIDER_H_

#include "Collidable.h"
#include "Rect.h"

class BoxCollider : public Collidable
{
protected:
	Rect mRect;
	Degrees mRotation;
public:
	explicit BoxCollider(const Rect& r, Degrees rotation) : mRect(r), mRotation(rotation) {}
	
	virtual void render(uint64_t frame);
	virtual bool contains(const Point& p) const;
	virtual Vector surfaceNormal(const Point& p) const;
	
	const Rect& rect() const { return mRect; }
	void setRect(const Rect& r) { mRect = r; }
	Degrees rotation() const { return mRotation; }
	void setRotation(const Degrees& rot) { mRotation = rot; }
};

#endif /* _BOXCOLLIDER_H_ */
