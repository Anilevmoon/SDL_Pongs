#pragma once
#include "Ball.h"
#include "Brick.h"
class MoveBallController {
	public:

	static const int m_NoContact = 0;
	static const int m_contactTop = 1;
	static const int m_contactMiddle = 2;
	static const int m_contactBottom = 3;
	static const int m_LeftWallContact = 4;
	static const int m_RightWallContact = 5;

	int m_ContactType = 0;

	MoveBallController(bool a);

	void CheckBrickCollision(Ball const& ball, Brick const& brick);
	void CollideWithBrick(Ball &ball);
	void CheckWallBounce(Ball const& ball);
	void BounceWithWall(Ball &ball);

	private:
	float m_crossing;

};

