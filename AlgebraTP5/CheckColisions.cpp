#include "CheckColisions.h"
#include "Game.h"

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

				if (overlap(ball1.position.x, ball1.position.y, ball1.radius,
					ball2.position.x, ball2.position.y, ball2.radius))
				{

					//distancia entre los centros de las bolas
					float fDistance = sqrtf((ball1.position.x - ball2.position.x) * (ball1.position.x - ball2.position.x) + (ball1.position.y - ball2.position.y) * (ball1.position.y - ball2.position.y));

					float fOverlap = 0.5f * (fDistance - ball1.radius - ball2.radius);

					//le doy a la posicion la mitad del overlapeo en la direccion normalizada
					ball1.position.x -= fOverlap * (ball1.position.x - ball2.position.x) / fDistance;
					ball1.position.y -= fOverlap * (ball1.position.y - ball2.position.y) / fDistance;

					ball2.position.x += fOverlap * (ball1.position.x - ball2.position.x) / fDistance;
					ball2.position.y += fOverlap * (ball1.position.y - ball2.position.y) / fDistance;


					//normal
					float nx = (ball2.position.x - ball1.position.x) / fDistance;
					float ny = (ball2.position.y - ball1.position.y) / fDistance;

					//tangente
					float tx = -ny;
					float ty = nx;

					//tangente del producto punto 
					float dpTan1 = ball1.position.x * tx + ball1.position.y * ty;
					float dpTan2 = ball2.position.x * tx + ball2.position.y * ty;

					//normal del producto punto 
					float dpNorm1 = ball1.position.x * nx + ball1.position.y * ny;
					float dpNorm2 = ball2.position.x * nx + ball2.position.y * ny;

					//conservacion de velocidad en 1d
					float m1 = (dpNorm1 * (ball1.mass - ball2.mass) + 2.0f * ball2.mass * dpNorm2) / (ball1.mass + ball2.mass);
					float m2 = (dpNorm2 * (ball2.mass - ball1.mass) + 2.0f * ball1.mass * dpNorm1) / (ball1.mass + ball2.mass);

					ball1.speed.x = tx * dpTan1 + nx * m1;
					ball1.speed.y = ty * dpTan1 + ny * m1;
					ball2.speed.x = tx * dpTan2 + nx * m2;
					ball2.speed.y = ty * dpTan2 + ny * m2;


				}

				ball1.speed.x *= -1;
				ball1.speed.y *= -1;

				setSpeedBall(ball2, ball1.position, 20);


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
			ball.position = { static_cast<float>(ball.id * 50) , 20 };
		}

		ball.inMovement = false;
	}


}

bool CheckCollisionCircleCircle(Vector2 ball, float radius1, Vector2 ball2, float radius2) {

	// get distance between the circle's centers
	// use the Pythagorean Theorem to compute the distance
	float distX = ball.x - ball2.x;
	float distY = ball.y - ball2.y;
	float distance = sqrt((distX * distX) + (distY * distY));

	// if the distance is less than the sum of the circle's
	// radii, the circles are touching

	return distance <= radius1 + radius2;


}