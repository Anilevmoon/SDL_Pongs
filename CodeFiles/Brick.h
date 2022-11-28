#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "VectorPhysics.h"
#include "CONSTANTS.h"
class Brick {
	public:

	Brick(VectorPhysics position,  VectorPhysics movingWay);
	void UpdateBrickPosition(float timeGone);

	VectorPhysics m_position;
	VectorPhysics m_movingWay;
	SDL_Rect rect;
};

