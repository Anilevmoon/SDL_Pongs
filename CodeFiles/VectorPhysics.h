#pragma once
class VectorPhysics {
	public:
	VectorPhysics(): x(0.0f), y(0.0f) {}

	VectorPhysics(float x, float y): x(x), y(y) {}

	VectorPhysics operator + (VectorPhysics const& move);
	VectorPhysics& operator += (VectorPhysics const& move);
	VectorPhysics operator * (float move);

	float x, y;

};

