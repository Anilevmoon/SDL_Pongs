#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <random>
#include <chrono>
#include "CONSTANTS.h"
#include "Brick.h"
#include "Ball.h"
class MoveControlPlayer {
	public:
	MoveControlPlayer(bool change);
	virtual ~MoveControlPlayer() = default;

	double randomNumber();
	void PlayerControl(bool &running, Brick &brickOne, Brick &brickTwo, bool &runBot);
	void BotControl(bool &running, Brick &brickBOT, Ball const &ball);

	private:
	bool isBallOnBotside = 0;
	double BotDisplacement = 0.0f;
	double rand = 0.0f;

	bool brickOneUp;
	bool brickOneDown;
	bool brickTwoUp;
	bool brickTwoDown;
};

