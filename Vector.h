#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "Point.h"

template <typename T>
struct VectorT : public PointT<T>
{
	VectorT<T>() : PointT<T>() {}
	VectorT<T>(T x, T y) : PointT<T>(x, y) {}
	VectorT<T>(const PointT<T>& vec) : PointT<T>(vec) {}
	
	double length() const { return sqrt(this->x*this->x + this->y*this->y); }
	
	VectorT<T> normalize() const
	{
		double l = length();
		return VectorT<T>(this->x / l, this->y / l);
	}
};

typedef VectorT<Real> Vector;

#endif /* _VECTOR_H_ */
