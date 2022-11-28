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
	newBall.vectorDirection = {};
	newBall.speed = {}; // Velocidad establecida por defecto en 0. 
	newBall.id = id;
	newBall.color = color;

	newBall.receivedInitialForce = 0.0f;

	newBall.frictionToRestX= newBall.mass / newBall.receivedInitialForce;
	newBall.frictionToRestY= newBall.mass / newBall.receivedInitialForce;
}

void updateBall(BALL& ball)
{
	// Si la fuerza se le fue aplicada... 
	if (ball.inMovement)
	{
		 ball.frictionToRestX = ball.mass / ball.receivedInitialForce;
		 ball.frictionToRestY = ball.mass / ball.receivedInitialForce;
		 //:)
		 //chequeo contra paredes
		 if (ball.position.x <= 160)
		 {
			 if (ball.speed.x < 0)
			 {
				 ball.speed.x *= -1;
				 ball.frictionToRestX *= -1;
				 ball.vectorDirection.x *= -1;
			 }
		 }

		 if (ball.position.x >= 750)
		 {
			 if (ball.speed.x > 0)
			 {
				 ball.speed.x *= -1;
				 ball.frictionToRestX *= -1;
				 ball.vectorDirection.x *= -1;
			 }
		 }

		 if (ball.position.y <= 50)
		 {
			 if (ball.speed.y < 0)
			 {
				 ball.speed.y *= -1;
				 ball.frictionToRestY *= -1;
				 ball.vectorDirection.y *= -1;
			 }
		 }

		 if (ball.position.y >= 850)
		 {
			 if (ball.speed.y > 0)
			 {
				 ball.speed.y *= -1;
				 ball.frictionToRestY *= -1;
				 ball.vectorDirection.y *= -1;
			 }
		 }


		ball.speed.x -= ball.frictionToRestX * ball.vectorDirection.x ;
		ball.speed.y -= ball.frictionToRestY * ball.vectorDirection.y ;
		

		//si esta casi detenida, frenarla a 0
		if (fabs(ball.speed.x * ball.speed.x + ball.speed.y * ball.speed.y) < 0.09)
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
	float torque = force * ball.radius; // F�rmula de la fuerza angular: Fuerza inicial * radio. 

	ball.inMovement = true;
	ball.vectorDirection = { forceOriginPosition.x - ball.position.x, forceOriginPosition.y - ball.position.y };

	ball.vectorDirection = Vector2Normalize(ball.vectorDirection);

	ball.speed.x = ball.vectorDirection.x * torque;
	ball.speed.y = ball.vectorDirection.y * torque;
	ball.receivedInitialForce = torque;
}

void addSpeedBall(BALL& ball, Vector2 speed, float force = 0.0f)
{
	float torque = force * ball.radius; // F�rmula de la fuerza angular: Fuerza inicial * radio. 

	ball.speed.y += torque;
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