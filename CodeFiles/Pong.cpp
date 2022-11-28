#include <iostream>
#include <conio.h>
#include "MoveControlPlayer.h"
#include "MoveBallController.h"
#include "Screen.h"

SDL_Window* wind = NULL;
SDL_Renderer* rend = NULL;
SDL_Surface* scr = SDL_GetWindowSurface(wind);

bool RunBot = false;
bool gameStart = true;


// Initialize SDL components function
void init() {

	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "Can't init SDL: " << SDL_GetError() << std::endl;
	}

	wind = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	if(wind == NULL) {
		std::cout << "Can't create window: " << SDL_GetError() << std::endl;
	}

	rend = SDL_CreateRenderer(wind, -1, SDL_RENDERER_ACCELERATED);
	if(rend == NULL) {
		std::cout << "Can't create renderer: " << SDL_GetError() << std::endl;
	}

}

//Destructor
void quit() {
	SDL_DestroyRenderer(rend);
	rend = NULL;
	SDL_DestroyWindow(wind);
	wind = NULL;
	IMG_Quit();
	SDL_Quit();
}


int main(int arhc, char** argv) {

	// Initialize SDL components
	init();

	//Initializing all objects we need
	Screen scr(wind, rend);

	VectorPhysics pos((Constants::WINDOW_WIDTH / 2.0f) - (Constants::BALL_WIDTH / 2.0f),
		(Constants::WINDOW_HEIGHT / 2.0f) - (Constants::BALL_WIDTH / 2.0f));
	VectorPhysics velocit(Constants::BALL_SPEED, 0.0f);

	Ball ball(pos, velocit, rend);

	Brick brickPlayer(VectorPhysics(50.0f, (Constants::WINDOW_HEIGHT / 2.0f) - (Constants::BRICK_HEIGHT / 2.0f)), VectorPhysics(0.0f, 0.0f));
	Brick brickBot(VectorPhysics(Constants::WINDOW_WIDTH - 50.0f, (Constants::WINDOW_HEIGHT / 2.0f) - (Constants::BRICK_HEIGHT / 2.0f)), VectorPhysics(0.0f, 0.0f));

	MoveControlPlayer moveControl(false);
	MoveBallController controlBall(true);

	
	//loading components for Score rendering
	scr.ScoreLoad();

	//Starting menu. 
	scr.MenuLoad();

	while(gameStart){
		scr.menu(gameStart, RunBot);
		SDL_SetRenderDrawColor(rend, 0x0, 0x0, 0x0, 0xFF);
		SDL_RenderPresent(rend);
	}


	//
	bool running = true;
	float timeBetwenFrames = 0.0f;

	int playerOneScore = 0;
	int playerTwoScore = 0;
	// Continue looping and processing events until user exits
	while(running) {

		//Stop timer and save the time of frame(used for brick/ball speed, in case it isn't affected by FPS)
		auto startTimer = std::chrono::high_resolution_clock::now();
		
		//Main input controls processing
		moveControl.PlayerControl(running, brickPlayer, brickBot, RunBot);  
		if(RunBot) {
		moveControl.BotControl(running, brickPlayer, ball);
		}
		
		//Updating all moving part's positions 
		brickPlayer.UpdateBrickPosition(timeBetwenFrames);
		brickBot.UpdateBrickPosition(timeBetwenFrames);
		ball.UpdateBallPosition(timeBetwenFrames);

		//Checking collisions with BrickOne
		bool isContact(false);
		controlBall.CheckBrickCollision(ball, brickPlayer);
		
		if(controlBall.m_ContactType != controlBall.m_NoContact) {
			controlBall.CollideWithBrick(ball);
			isContact = true;
		}

		//Checking collisions with BrickTwo
		if(!isContact) {
			controlBall.CheckBrickCollision(ball, brickBot);

			if(controlBall.m_ContactType != controlBall.m_NoContact) {
				controlBall.CollideWithBrick(ball);
				isContact = true;
			}
		}

		
		
		if(!isContact) {
			//Checking Top/Bottom wall collisions 
			controlBall.CheckWallBounce(ball);

			//Checking 'goals' (ball contacts with right/left wall) and updating score
			if(controlBall.m_ContactType != controlBall.m_NoContact) { 
				controlBall.BounceWithWall(ball);
				if(controlBall.m_ContactType == controlBall.m_LeftWallContact) {
					playerTwoScore++;
					scr.m_pTwoScore = playerTwoScore;
				} else if(controlBall.m_ContactType == controlBall.m_RightWallContact) {
					playerOneScore++;
					scr.m_pOneScore = playerOneScore;
				}
			}
		}

		Sleep(1); //Simple frame-control for no 1000FPS
		
		// Clear the window to black to clear last frame
		SDL_SetRenderDrawColor(rend, 0x0, 0x0, 0x0, 0xFF);
		SDL_RenderClear(rend);

		// Rendering (not menu) happens here 
		scr.DrawStaticElements();
		scr.BallDraw(ball);
		scr.BrickDraw(brickPlayer);
		scr.BrickDraw(brickBot);
		scr.DrawScore(scr.m_rectFirst, scr.m_rectSecond);


		// Present the backbuffer
		SDL_RenderPresent(rend);

		//Stop timer and save the time of frame(used for brick/ball speed, in case it isn't affected by FPS)
		auto stopTimer = std::chrono::high_resolution_clock::now();
		timeBetwenFrames = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTimer - startTimer).count();
		
		// Player scores to 0, Delay for "Player win" Window
		if(playerOneScore == 10 || playerTwoScore == 10) {
			playerOneScore = 0;
			playerTwoScore = 0;
			SDL_Delay(3000);

			//The ball random start side, bricks in the start position
			double random = moveControl.randomNumber();

			if(random>=0.5) {
			ball.m_velocity.x = 1.0f;
			} else {
			ball.m_velocity.x = -1.0f;
			}

			ball.m_velocity.y = 0.0f;
			brickPlayer.m_position.y = Constants::WINDOW_HEIGHT/2 - Constants::BRICK_HEIGHT/2 + Constants::BALL_HEIGHT/2;
			brickBot.m_position.y = Constants::WINDOW_HEIGHT/2 - Constants::BRICK_HEIGHT/2 + Constants::BALL_HEIGHT/2;
			
		}
	}

	// Cleanup
	quit();

	return 0;
}

