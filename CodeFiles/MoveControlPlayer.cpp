#include "MoveControlPlayer.h"

MoveControlPlayer::MoveControlPlayer(bool change) {
	//All brick moves as false
	brickOneUp = change;
	brickOneDown = change;
	brickTwoUp = change;
	brickTwoDown = change;
}

//Rundom nuber function used for controlling bot moves to make it more interesting
double MoveControlPlayer::randomNumber() {
	int min = 1;
	int max = 99;

	std::random_device rd;
	std::mt19937 mersenne(rd());

	int preResult = static_cast<int>(mersenne()%(max - min + 1) + min);
	double result = preResult/100.0;
	return result;
}

//  Players/player control using events
void MoveControlPlayer::PlayerControl(bool& running, Brick& brickOne, Brick& brickTwo, bool& runBot) {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		//enable window cross to close an app
		if(event.type == SDL_QUIT) {
			running = false;
			//making players move if the keys are down
		} else if(event.type == SDL_KEYDOWN) {
			// Enable ESC to close an app
			if(event.key.keysym.sym == SDLK_ESCAPE) {
				running = false;
			} else if(event.key.keysym.sym == SDLK_w && !runBot) {
				brickOneUp = true;
			} else if(event.key.keysym.sym == SDLK_s && !runBot) {
				brickOneDown = true;
			} else if(event.key.keysym.sym == SDLK_UP) {
				brickTwoUp = true;
			} else if(event.key.keysym.sym == SDLK_DOWN) {
				brickTwoDown = true;
			}

			//making players stop if the keys are UP
		} else if(event.type == SDL_KEYUP) {
			if(event.key.keysym.sym == SDLK_w && !runBot) {
				brickOneUp = false;
			} else if(event.key.keysym.sym == SDLK_s && !runBot) {
				brickOneDown = false;
			} else if(event.key.keysym.sym == SDLK_UP) {
				brickTwoUp = false;
			} else if(event.key.keysym.sym == SDLK_DOWN) {
				brickTwoDown = false;
			}
		}
	}

	//If no BOT Enable Player 2 moving or moving depandin on the keys are pressed
	if(!runBot) {
		if(brickOneUp) {
			brickOne.m_movingWay.y = -Constants::BRICK_SPEED;
		} else if(brickOneDown) {
			brickOne.m_movingWay.y = Constants::BRICK_SPEED;
		} else {
			brickOne.m_movingWay.y = 0.0f;
		}
	}

	//player 1 moving depandin on the keys are pressed
	if(brickTwoUp) {
		brickTwo.m_movingWay.y = -Constants::BRICK_SPEED;
	} else if(brickTwoDown) {
		brickTwo.m_movingWay.y = Constants::BRICK_SPEED;
	} else {
		brickTwo.m_movingWay.y = 0.0f;
	}

}

//Bot controling 
void MoveControlPlayer::BotControl(bool& running, Brick& brickBOT, Ball const& ball) {
	//Realising on wich side ball is
	isBallOnBotside = ball.m_position.x<(Constants::WINDOW_WIDTH/2);

	//Update BOT random in the right moment
	if(rand == 0.0f && ball.m_position.x < 1*(Constants::WINDOW_WIDTH/6)) {
		rand = randomNumber();
	}
	if(ball.m_position.x > 2*(Constants::WINDOW_WIDTH/6) && ball.m_position.x < 3*(Constants::WINDOW_WIDTH/6)) {
		rand = 0.0f;
		BotDisplacement = 0.0f;
	}

	//changing the way ball will be beaten by BOT depend on random number, according to the "center" of the ball
	if(isBallOnBotside && ball.m_velocity.x<0) {
		if(rand <= 0.33f) {
			BotDisplacement = (Constants::BRICK_HEIGHT/6.0) - (Constants::BALL_HEIGHT/2); //2.5
		} else if(rand>0.33f && rand<0.66f) {
			BotDisplacement = 3*(Constants::BRICK_HEIGHT/6.0) - (Constants::BALL_HEIGHT/2); //22.5
		} else {
			BotDisplacement = 5*(Constants::BRICK_HEIGHT/6.0) - (Constants::BALL_HEIGHT/2); // 42.5f
		}

		//Moving bot according to data with 4px fallibility for stability 
		if(ball.m_position.y + 2 < brickBOT.m_position.y + BotDisplacement) {
			brickBOT.m_movingWay.y = -Constants::BRICK_BOT_SPEED;
		} else if(ball.m_position.y - 2 > brickBOT.m_position.y + BotDisplacement) {
			brickBOT.m_movingWay.y = Constants::BRICK_BOT_SPEED;
		} else {
			brickBOT.m_movingWay.y = 0.0f;
		}
	} else {
		brickBOT.m_movingWay.y = 0.0f;
	}

}


