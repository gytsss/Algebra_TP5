#include "Player.h"

PLAYER CreatePlayer()
{
	PLAYER P1 = {};
	P1.rec.x = 0;
	P1.rec.y = 0;
	P1.rec.width= 40;
	P1.rec.height = 5;

	P1.origin = {0, P1.rec.height/2};

	P1.rotation = 0;

	P1.color = BROWN;

	return P1;
}


void PlayerMove(PLAYER& P1, BALL& ball1)
{
	Vector2 vectorDirection;
	float arctan;

	vectorDirection.x = GetMouseX() - ball1.position.x;
	vectorDirection.y = GetMouseY() - ball1.position.y;

	arctan = static_cast<float>(atan(vectorDirection.y / vectorDirection.x));
	P1.rotation = arctan * 180 / PI;
	P1.rotation += 180;

	if (vectorDirection.x < 0)
	{
		P1.rotation += 180;
	}

	P1.rec.x = ball1.position.x;
	P1.rec.y = ball1.position.y;
}