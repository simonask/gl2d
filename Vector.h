#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "Point.h"

template <typename T>
struct VectorT : public PointT<T>
{
	VectorT<T>() : PointT<T>() {}
	VectorT<T>(T x, T y) : PointT<T>(x, y) {}
	VectorT<T>(const PointT<T>& vec) : PointT<T>(vec) {}
	
	T length() const { return (T)sqrt(this->x*this->x + this->y*this->y); }
	
	VectorT<T> normalize() const
	{
		T l = length();
		return VectorT<T>(this->x / l, this->y / l);
	}
	
	inline VectorT<T> operator/(T other) const { return VectorT<T>(this->x / other, this->y / other); }
};

typedef VectorT<Real> Vector;

#endif /* _VECTOR_H_ */
