#include "Balls.h"
#include <iostream>

void createBall(BALL& newBall, float x, float y, float radius, float mass, int id, Color color)
{
	newBall.position.x = x;
	newBall.position.y = y;

	newBall.inMovement = false;
	newBall.radius = radius;
	newBall.mass = mass;

	newBall.angle = 0.0f;
	newBall.speed = {}; // Velocidad establecida por defecto en 0. 
	newBall.id = id;
	newBall.color = color;

	newBall.receivedInitialForce = 0.0f;


}

void updateBall(BALL& ball)
{
	//Friccion calculada en base a la gravedad, la masa de la pelota y la fuerza de rozamiento con la mesa
	ball.friction = 0.2f * (ball.mass * 9.8f);

	// Si la fuerza se le fue aplicada... 
	if (ball.inMovement)
	{

		if (ball.speed.x > 0)
		{
			ball.speed.x -= ball.friction * GetFrameTime();
		}
		else
		{
			ball.speed.x -= -ball.friction * GetFrameTime();
		}

		if (ball.speed.y > 0)
		{
			ball.speed.y -= ball.friction * GetFrameTime();
		}
		else
		{
			ball.speed.y -= -ball.friction * GetFrameTime();
		}


		//si esta casi detenida, frenarla a 0
		if (fabs(ball.speed.x * ball.speed.x + ball.speed.y * ball.speed.y) <= 0.9)
		{
			ball.speed.x = 0;
			ball.speed.y = 0;
		}


		// Si la velocidad en ambos ejes est� en 0... 
		if (ball.speed.x == 0 && ball.speed.y == 0)
		{
			ball.inMovement = false;
		}


		ball.position.x += ball.speed.x * GetFrameTime();
		ball.position.y += ball.speed.y * GetFrameTime();


	}
}

void setSpeedBall(BALL& ball, Vector2 forceOriginPosition, float force)
{
	ball.inMovement = true;
	Vector2 vectorDirection = { forceOriginPosition.x - ball.position.x, forceOriginPosition.y - ball.position.y };

	vectorDirection = Vector2Normalize(vectorDirection);

	ball.speed.x = vectorDirection.x * force;
	ball.speed.y = vectorDirection.y * force;
}

void setSpeedBall(BALL& ball, Vector2 speed)
{
	ball.speed.x += speed.x * 0.009;
	ball.speed.y += speed.y * 0.009;
}

static void normalizeVector(Vector2& v)
{
	float x = v.x;
	float y = v.y;
	float bigger = 0.0f;


	// Si es negativo, se vuelve positivo. 
	if (x < 0.0f)
	{
		x = -x;
	}

	// Si es negativo, se vuelve positivo. 
	if (y < 0.0f)
	{
		y = -y;
	}

	// Se verifica cu�l es el m�s grande. 
	if (x >= y)
	{
		bigger = x;
	}
	else
	{
		bigger = y;
	}

	// Se normaliza. 
	v.x /= bigger;
	v.y /= bigger;
}