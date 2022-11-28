#include "Ball.h"

Ball::Ball(VectorPhysics position, VectorPhysics velocity, SDL_Renderer* renderer) : m_position(position), m_velocity(velocity) {
	//init of IMG for SDL_image to load png
	int flags = IMG_INIT_PNG;
	if(!(IMG_Init(flags) & flags)) {
		std::cout << "Can't init image: " << IMG_GetError() << std::endl;
	}

	load(renderer);

	//making ball's rectangle to make ball size we need
	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);
	rect.w = Constants::BALL_WIDTH;
	rect.h = Constants::BALL_HEIGHT;
}

void Ball::load(SDL_Renderer* rend) {
	//Loading Ball picture + remake into texture
	SDL_Surface* temp_surf = new SDL_Surface {NULL};
	temp_surf = IMG_Load("ball.png");
	m_ball = SDL_CreateTextureFromSurface(rend, temp_surf);
	temp_surf = NULL;
	delete temp_surf;
}

void Ball::UpdateBallPosition(float timeBetFrms) {
	//This is made for the speed of ball not to depend from FPS, the speed is multipling by time of frame to form right ball moving
	m_position += m_velocity * timeBetFrms;
}
