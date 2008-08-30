#include "Streamy.h"

std::ostream& operator<<(std::ostream& os, const Angle& angle)
{
	os << angle.toRadians().value << " rad / " << angle.toDegrees().value << " deg";
	return os;
}
