#include "Brick.h"

Brick::Brick(VectorPhysics position, VectorPhysics movingWay) : m_position(position), m_movingWay(movingWay) {
	//making brick's rectangle to make it size we need
	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);
	rect.w = Constants::BRICK_WIDTH;
	rect.h = Constants::BRICK_HEIGHT;
}

void Brick::UpdateBrickPosition(float timeGone) {
	//This is made for the speed of ball not to depend from FPS, the speed is multipling by time of frame to form right ball moving
	m_position += m_movingWay * timeGone;

	if(m_position.y < 0) {
		// Position Control in top
		m_position.y = 0;
	} else if(m_position.y >(Constants::WINDOW_HEIGHT - Constants::BRICK_HEIGHT)) {
		//  Position Control in bottom
		m_position.y = Constants::WINDOW_HEIGHT - Constants::BRICK_HEIGHT;
	}
}
