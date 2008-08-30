#ifndef _PRINTERS_H_
#define _PRINTERS_H_

#include <iostream>
#include "Point.h"

template <typename T>
std::ostream& operator<<(std::ostream& os, const PointT<T>& p)
{
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const Angle& angle);

#endif /* _PRINTERS_H_ */
