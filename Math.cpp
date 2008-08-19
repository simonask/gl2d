#include "Math.h"

Radians::Radians(const Degrees& deg) : Angle(deg.toRadians()) {}
Degrees Radians::toDegrees() const { return Degrees((value / (2*M_PI)) * 360); }

Degrees::Degrees(const Radians& rad) : Angle(rad.toDegrees()) {}
Radians Degrees::toRadians() const { return Radians((value / 360) * (2*M_PI)); }