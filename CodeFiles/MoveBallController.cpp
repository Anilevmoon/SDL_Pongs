#include "MoveBallController.h"

MoveBallController::MoveBallController(bool a) {
	//m_crossing = 0.0;
}

void MoveBallController::CheckBrickCollision(Ball const& ball, Brick const& brick) {
	//Initialization of ball's real size, not one his coordinate
	float ballLeft = ball.m_position.x;
	float ballRight = ball.m_position.x + Constants::BALL_WIDTH;
	float ballTop = ball.m_position.y;
	float ballBottom = ball.m_position.y + Constants::BALL_HEIGHT;

	//Initialization of brick's real size, not one his coordinate
	float brickLeft = brick.m_position.x;
	float brickRight = brick.m_position.x + Constants::BRICK_WIDTH;
	float brickTop = brick.m_position.y;
	float brickBottom = brick.m_position.y + Constants::BRICK_HEIGHT;

	if(ballLeft >= brickRight || ballRight <= brickLeft || ballTop >= brickBottom || ballBottom <= brickTop) {
		m_ContactType = m_NoContact;
		return;
	}

	//Description of different types ball contact with different parts of Brick
	float BrickTopPart = brickBottom - (2.0f * Constants::BRICK_HEIGHT / 3.0f);
	float BrickMiddlePart = brickBottom - (Constants::BRICK_HEIGHT / 3.0f);

	//solution with bug when the ball crossing into a brick/wall
	if(ball.m_velocity.x < 0) {		
		// Left Brick
		m_crossing = brickRight - ballLeft;

	} else if(ball.m_velocity.x > 0) {
		// Right Brick
		m_crossing = brickLeft - ballRight;
	}

	//Realising where the ball hits the brick
	if((ballBottom > brickTop) && (ballBottom < BrickTopPart)) {
		m_ContactType = m_contactTop;

	} else if((ballBottom > BrickTopPart) && (ballBottom < BrickMiddlePart)) {
		m_ContactType = m_contactMiddle;

	} else {
		m_ContactType = m_contactBottom;
	}

	return;
}

void MoveBallController::CollideWithBrick(Ball& ball) {
	//Changing x-ballspeed to opposite when it hits the brick
	ball.m_position.x += m_crossing;
	ball.m_velocity.x = -ball.m_velocity.x;

	//Changing y-ballspeed to create an angle  when it hits NOT in the middle part of brick
	if(m_ContactType == m_contactTop) {
		ball.m_velocity.y = -0.75f * Constants::BALL_SPEED;
	} else if(m_ContactType == m_contactBottom) {
		ball.m_velocity.y = 0.75f * Constants::BALL_SPEED;
	} else {
		ball.m_velocity.y = 0;
	}
}

void MoveBallController::CheckWallBounce(Ball const& ball) {
	//Initialization of ball's real size, not one his coordinate
	float ballLeft = ball.m_position.x;
	float ballRight = ball.m_position.x + Constants::BALL_WIDTH;
	float ballTop = ball.m_position.y;
	float ballBottom = ball.m_position.y + Constants::BALL_HEIGHT;
	
	//Realising what wall the ball collides and changing m_contactType according to this
	if(ballLeft < 0.0f) {
		m_ContactType = m_LeftWallContact;

	} else if(ballRight > Constants::WINDOW_WIDTH) {
		m_ContactType = m_RightWallContact;

	} else if(ballTop < 0.0f) {
		m_ContactType = m_contactTop;
		m_crossing = -ballTop;

	} else if(ballBottom > Constants::WINDOW_HEIGHT) {
		m_ContactType = m_contactBottom;
		m_crossing = Constants::WINDOW_HEIGHT - ballBottom;
	}
}

//Ball's reaction to the each type of contact
void MoveBallController::BounceWithWall(Ball& ball) {
	if((m_ContactType == m_contactTop) || (m_ContactType == m_contactBottom)) {
		ball.m_position.y += m_crossing;
		ball.m_velocity.y = -ball.m_velocity.y;

		//Also respawning ball after it hits right or lefi brick
	} else if(m_ContactType == m_LeftWallContact) { 
		ball.m_position.x = Constants::WINDOW_WIDTH / 2.0f;
		ball.m_position.y = Constants::WINDOW_HEIGHT / 2.0f;
		ball.m_velocity.x = Constants::BALL_SPEED;
		ball.m_velocity.y = 0.85f * Constants::BALL_SPEED;

	} else if(m_ContactType == m_RightWallContact) {
		ball.m_position.x = Constants::WINDOW_WIDTH / 2.0f;
		ball.m_position.y = Constants::WINDOW_HEIGHT / 2.0f;
		ball.m_velocity.x = -Constants::BALL_SPEED;
		ball.m_velocity.y = 0.80f * Constants::BALL_SPEED;
	}
}
