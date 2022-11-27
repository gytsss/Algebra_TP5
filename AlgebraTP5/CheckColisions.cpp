#include "CheckColisions.h"

void CheckBallWallColition(BALL& ball)
{
	if (ball.position.x < 160)
	{
		if (ball.speed.x < 0)
		{
			ball.speed.x *= -1;
		}
	}

	if (ball.position.x > 750)
	{
		if (ball.speed.x > 0)
		{
			ball.speed.x *= -1;
		}
	}

	if (ball.position.y < 50)
	{
		if (ball.speed.y < 0)
		{
			ball.speed.y *= -1;
		}
	}

	if (ball.position.y > 850)
	{
		if (ball.speed.y > 0)
		{
			ball.speed.y *= -1;
		}
	}

}

void CheckBallBallColition(BALL& ball1, BALL& ball2)
{
	if (ball1.id != ball2.id)
	{
		if (ball1.inMovement)
		{
			if (CheckCollisionCircles(ball1.position, ball1.radius, ball2.position, ball2.radius))
			{
				cout << "colition" << endl;
				ball2.inMovement = true;

				setSpeedBall(ball2, ball1.position, 15);

				ball1.speed.x *= -1;
				ball1.speed.y *= -1;
			}
		}
	}
}