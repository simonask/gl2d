#ifndef _YINYANG_H_
#define _YINYANG_H_

#include "Renderable.h"

class YinYang : public Renderable
{
private:
	Point mCenter;
	Real mRadius;
public:
	explicit YinYang(const Point& c, Real radius) : mCenter(c), mRadius(radius) {}
	
	void render(uint64_t frame);
	Rect boundingRect() const { return Rect(mCenter.x - mRadius, mCenter.y - mRadius, 2*mRadius, 2*mRadius); }
};

#endif /* _YINYANG_H_ */
