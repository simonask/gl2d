#ifndef _POINT_H_
#define _POINT_H_

#include "Basic.h"
#include "GeometryMath.h"
#include <iostream>
using namespace std;

template <typename T>
struct PointT
{
	union
	{
		struct { T x, y; };
		struct { T width, height; };	// Mostly because I'm lazy...
	};
	
	PointT() : x(), y() {}
	PointT(T _x, T _y) : x(_x), y(_y) {}
	PointT(const PointT<T>& other) : x(other.x), y(other.y) {}
	
	bool operator==(const PointT<T>& other) const
	{
		return x == other.x && y == other.y;
	}
	
	PointT<T>& operator+=(const PointT<T>& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	
	PointT<T>& operator-=(const PointT<T>& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	
	PointT<T> operator+(const PointT<T>& other) const
	{
		return PointT<T>(x + other.x, y + other.y);
	}
	
	PointT<T> operator-(const PointT<T>& other) const
	{
		return PointT<T>(x - other.x, y - other.y);
	}
	
	PointT<T> rotateAround(PointT<T> orego, Radians angle) const;
};

typedef PointT<Real> Point;

template <typename T>
PointT<T> PointT<T>::rotateAround(PointT<T> origo, Radians angle) const
{
	if (*this == origo)
		return origo;
	
	T dx = x - origo.x;
	T dy = y - origo.y;
	double distance = sqrt(dx * dx + dy * dy);

	T dxu = dx / distance; // division by zero is prevented by equality trap
	T dyu = dy / distance;
	
	Radians pxangle = fmod(acosr(dxu), 2 * Math::PI);
	
	if (dyu < 0.0)	// acos always has two possible results -- check if we needed the other one
		pxangle = Math::PI * 2.0 - pxangle;
	
	Radians tr = fmod(pxangle - angle, 2 * Math::PI);
	
	T tx = cos(tr) * distance;
	T ty = sin(tr) * distance;
	
	return origo + PointT<T>(tx, ty);
}

#endif /* _POINT_H_ */
