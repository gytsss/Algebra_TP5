#include "CheckColisions.h"

void CheckBallWallColition(BALL& ball)
{
	if (ball.position.x <= 160)
	{
		if (ball.speed.x < 0)
		{
			ball.speed.x *= -1;
		}
	}

	if (ball.position.x >= 750)
	{
		if (ball.speed.x > 0)
		{
			ball.speed.x *= -1;
		}
	}

	if (ball.position.y <= 50)
	{
		if (ball.speed.y < 0)
		{
			ball.speed.y *= -1;
		}
	}

	if (ball.position.y >= 850)
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
			if (CheckCollisionCircleCircle(ball1.position, ball1.radius, ball2.position, ball2.radius))
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

void CheckBallCorner(BALL& ball)
{
	if (CheckCollisionCircleCircle(ball.position, ball.radius, { 150, 50 }, 15) ||
		CheckCollisionCircleCircle(ball.position, ball.radius, { 750, 50 }, 15) ||
		CheckCollisionCircleCircle(ball.position, ball.radius, { 150, 450 }, 15) ||
		CheckCollisionCircleCircle(ball.position, ball.radius, { 750, 450 }, 15) ||
		CheckCollisionCircleCircle(ball.position, ball.radius, { 150, 850 }, 15) ||
		CheckCollisionCircleCircle(ball.position, ball.radius, { 750, 850 }, 15))
	{
		if (ball.id == 0)
		{
			ball.position = { static_cast<float>(GetScreenWidth() / 2), 650.0f };
			ball.speed = { 0,0 };
		}
		else
		{
			ball.position = { static_cast<float>(ball.id * 50) , 20};
		}

		ball.inMovement = false;
	}


}

bool CheckCollisionCircleCircle(Vector2 ball, float radius1, Vector2 ball2, float radius2) {

  // get distance between the circle's centers
  // use the Pythagorean Theorem to compute the distance
  float distX = ball.x - ball2.x;
  float distY = ball.y - ball2.y;
  float distance = sqrt( (distX*distX) + (distY*distY) );

  // if the distance is less than the sum of the circle's
  // radii, the circles are touching!
  if (distance <= radius1 + radius2) {
    return true;
  }
  return false;
}