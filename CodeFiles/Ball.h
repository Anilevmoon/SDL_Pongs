#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "VectorPhysics.h"
#include "CONSTANTS.h"
class Ball {
	public:
	
	Ball(VectorPhysics position, VectorPhysics velocity, SDL_Renderer* renderer);

	void load(SDL_Renderer* renderer);
	void UpdateBallPosition(float timeBetFrms);

	VectorPhysics m_position;
	VectorPhysics m_velocity;
	SDL_Rect rect;
	SDL_Texture *m_ball = NULL;



};

