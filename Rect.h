#ifndef _RECT_H_
#define _RECT_H_

#include "Point.h"
#include "Vector.h"

template <typename T>
struct RectT
{
	PointT<T> origin;
	VectorT<T> size;
	
	RectT() {}
	RectT(const PointT<T>& _origin, const VectorT<T>& _size) : origin(_origin), size(_size) {}
	RectT(T _x, T _y, T _w, T _h) : origin(_x, _y), size(_w, _h) {}
	
	inline bool contains(T px, T py) const
	{
		return (px >= origin.x && px < origin.x + size.x && py >= origin.y && py < origin.y + size.y);
	}
	
	inline bool contains(const PointT<T>& p) const
	{
		return contains(p.x, p.y);
	}
	
	inline T area() const { return size.x * size.y; }
	
	inline bool overlaps(const RectT<T>& other) const
	{
		return overlapsX(other) && overlapsY(other);
	}
	
	inline bool overlapsX(const RectT<T>& other) const
	{
		return (origin.x <= other.origin.x ? (origin.x + size.width > other.origin.x) : (other.origin.x + other.size.width > origin.x));
	}
	
	inline bool overlapsY(const RectT<T>& other) const
	{
		return (origin.y <= other.origin.y ? (origin.y + size.height > other.origin.y) : (other.origin.y + other.size.height > origin.y));
	}
};

typedef RectT<Real> Rect;

#endif /* _RECT_H_ */
