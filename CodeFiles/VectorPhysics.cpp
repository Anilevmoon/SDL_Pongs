#include "VectorPhysics.h"

//Operators overload for doings operations with them (velocity and Position)
VectorPhysics VectorPhysics::operator+(VectorPhysics const& move) {
	return VectorPhysics(x + move.x, y + move.y);
}

VectorPhysics& VectorPhysics::operator+=(VectorPhysics const& move) {
	x += move.x;
	y += move.y;

	return *this;
}

VectorPhysics VectorPhysics::operator*(float move) {
	return VectorPhysics(x * move, y * move);
}
