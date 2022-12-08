#include "CheckColisions.h"
#include "Game.h"

void CheckBallWallColition(BALL& ball)
{
	if (ball.position.x <= leftWall)
	{
		ball.speed.x *= -1;
	}

	if (ball.position.x >= rightWall)
	{
		ball.speed.x *= -1;
	}

	if (ball.position.y <= upperWall)
	{
		ball.speed.y *= -1;
	}

	if (ball.position.y >= bottomWall)
	{
		ball.speed.y *= -1;
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

				//distancia entre los centros de las bolas
				float distance = sqrtf(powf(ball2.position.x - ball1.position.x, 2) + powf(ball2.position.y - ball1.position.y, 2));

				float overlap = 0.5f * (distance - ball1.radius - ball2.radius);

				//le doy a la posicion la mitad del overlapeo en la direccion normalizada
				ball1.position = { ball1.position.x - overlap * (ball1.position.x - ball2.position.x) / distance, ball1.position.y - overlap * (ball1.position.y - ball2.position.y) / distance };

				ball2.position = { ball2.position.x + overlap * (ball1.position.x - ball2.position.x) / distance, ball2.position.y + overlap * (ball1.position.y - ball2.position.y) / distance };


				ElasticCollision(ball1, ball2);
				
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


	float distX = ball.x - ball2.x;
	float distY = ball.y - ball2.y;
	float distance = sqrt((distX * distX) + (distY * distY));

	return distance <= radius1 + radius2;


}

void ElasticCollision(BALL& ball1, BALL& ball2)
{
	float distance = sqrtf(powf(ball2.position.x - ball1.position.x, 2) + powf(ball2.position.y - ball1.position.y, 2));

	//normal
	float normalX = (ball2.position.x - ball1.position.x) / distance;
	float normalY = (ball2.position.y - ball1.position.y) / distance;

	//tangente
	float tangentX = -normalY;
	float tangentY = normalX;

	//tangente del producto punto 
	float dpTan1 = ball1.speed.x * tangentX + ball1.speed.y * tangentY;
	float dpTan2 = ball2.speed.x * tangentX + ball2.speed.y * tangentY;

	//normal del producto punto 
	float dpNorm1 = ball1.speed.x * normalX + ball1.speed.y * normalY;
	float dpNorm2 = ball2.speed.x * normalX + ball2.speed.y * normalY;

	//conservacion de velocidad en 1d 
	float m1 = (dpNorm1 / (ball1.mass * 2)) + dpNorm2;
	float m2 = (dpNorm2 / (ball2.mass * 2)) + dpNorm1;


	ball1.speed = { tangentX * dpTan1 + normalX * m1, tangentY * dpTan1 + normalY * m1 };
	ball2.speed = { tangentX * dpTan2 + normalX * m2 , tangentY * dpTan2 + normalY * m2 };

}
