#ifndef _MATH_H_
#define _MATH_H_

#include "Basic.h"
#include <math.h>

struct Degrees;
struct Radians;

struct Angle
{
	Real value;

	Angle(Real r) : value(r) {}
	virtual Radians toRadians() const = 0;
	virtual Degrees toDegrees() const = 0;
	
	operator Real() const { return value; }
};

struct Radians : Angle
{
	Radians(Real rad) : Angle(rad) {}
	Radians(const Degrees& deg);
	
	Radians toRadians() const { return *this; }
	Degrees toDegrees() const;
	
	Radians& operator=(const Angle& angle) { value = angle.toRadians(); return *this; }
	Radians& operator+=(const Angle& other) { value += other.toRadians(); return *this; }
	Radians& operator-=(const Angle& other) { value -= other.toRadians(); return *this; }
	Radians& operator*=(Real other) { value *= other; return *this; }
	Radians& operator/=(Real other) { value /= other; return *this; }
	Radians operator+(const Angle& other) const { return Radians(value + other.toRadians()); }
	Radians operator-(const Angle& other) const { return Radians(value - other.toRadians()); }
	Radians operator*(Real other) const { return Radians(value * other); }
	Radians operator/(Real other) const { return Radians(value / other); }
	Radians operator-() const { return Radians(-value); }
};

struct Degrees : Angle
{
	Degrees(Real deg) : Angle(deg) {}
	Degrees(const Radians& rad);
	
	Radians toRadians() const;
	Degrees toDegrees() const { return *this; }
	
	Degrees& operator=(const Angle& angle) { value = angle.toDegrees(); return *this; }
	Degrees& operator+=(const Angle& other) { value += other.toDegrees(); return *this; }
	Degrees& operator-=(const Angle& other) { value -= other.toDegrees(); return *this; }
	Degrees& operator*=(Real other) { value *= other; return *this; }
	Degrees& operator/=(Real other) { value /= other; return *this; }
	Degrees operator+(const Angle& other) const { return Degrees(value + other.toDegrees()); }
	Degrees operator-(const Angle& other) const { return Degrees(value - other.toDegrees()); }
	Degrees operator*(Real other) const { return Degrees(value * other); }
	Degrees operator/(Real other) const { return Degrees(value / other); }
	Degrees operator-() const { return Degrees(-value); }
};

/*
	Without the following, this case will yield unexpected results:
	
	sin(Degree(90)) => 0.89..., instead of the expected 1.0
	
	This is due to the conversion rules of C++ -- Degree can be implicitly
	converted to Real, but further action is needed to convert the value
	to Radians.
	
	For the same reason, care needs to be taken when using asin and friends.
	C++ cannot overload based on return types, so I provided asinr, acosr, etc,
	which should be a tiny bit safer (i.e., hello auto-conversion).
*/
inline Real sin(const Angle& deg) { return sin((Real)deg.toRadians()); }
inline Real sinh(const Angle& deg) { return sinh((Real)deg.toRadians()); }
inline Real cos(const Angle& deg) { return cos((Real)deg.toRadians()); }
inline Real cosh(const Angle& deg) { return cosh((Real)deg.toRadians()); }
inline Real tan(const Angle& deg) { return tan((Real)deg.toRadians()); }
inline Real tanh(const Angle& deg) { return tanh((Real)deg.toRadians()); }
inline Radians asinr(Real x) { return asin(x); }
inline Radians asinhr(Real x) { return asinh(x); }
inline Radians acosr(Real x) { return acos(x); }
inline Radians acoshr(Real x) { return acosh(x); }
inline Radians atanr(Real x) { return atan(x); }
inline Radians atanhr(Real x) { return atanh(x); }

namespace Math
{
	const Radians PI = Radians(M_PI);
	const Radians Circle = PI * 2.0;
}

#endif /* _MATH_H_ */
