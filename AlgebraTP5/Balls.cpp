#include "Balls.h"

void createBall(BALL& newBall ,float x, float y, float radius, float mass, int id, Color color)
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
}

void updateBall(BALL& ball)
{
	// Si la fuerza se le fue aplicada... 
	if (ball.inMovement)
	{
		float frictionToRestX = ball.mass / ball.receivedInitialForce;
		float frictionToRestY = ball.mass / ball.receivedInitialForce;

		// Se mueve la pelota con la velocidad actual. AGREGAR ROZAMIENTO CON LA SUPERFICIE, QUE ES INDEPENDIENTE DE LA MASA Y TODO ESO. 
		ball.position.x += ball.speed.x * GetFrameTime();
		ball.position.y += ball.speed.y * GetFrameTime();

		if (ball.speed.x > 0.0f)
		{
			ball.speed.x -= frictionToRestX * ball.vectorDirection.x;

			// Si la velocidad actual pas� a ir en sentido contrario... 
			if (ball.speed.x <= 0.0f)
			{
				// Se setea a 0. 
				ball.speed.x = 0.0f;
			}
		}
		else if (ball.speed.x < 0.0f)
		{
			ball.speed.x -= frictionToRestX * ball.vectorDirection.x;

			// Si la velocidad actual pas� a ir en sentido contrario... 
			if (ball.speed.x >= 0.0f)
			{
				// Se setea a 0. 
				ball.speed.x = 0.0f;
			}
		}

		if (ball.speed.y > 0.0f)
		{
			ball.speed.y -= frictionToRestY * ball.vectorDirection.y;

			// Si la velocidad actual pas� a ir en sentido contrario... 
			if (ball.speed.y <= 0.0f)
			{
				// Se setea a 0. 
				ball.speed.y = 0.0f;
			}
		}
		else if (ball.speed.y < 0.0f)
		{
			ball.speed.y -= frictionToRestY * ball.vectorDirection.y;

			// Si la velocidad actual pas� a ir en sentido contrario... 
			if (ball.speed.y >= 0.0f)
			{
				// Se setea a 0. 
				ball.speed.y = 0.0f;
			}
		}

		// A la velocidad se le resta la fricci�n (F�rmula: masa / fuerzaInicial). 
		//ball.speed.x -= ball.mass / ball.receivedInitialForce * ball.vectorDirection.x * GetFrameTime(); 
		//ball.speed.y -= ball.mass / ball.receivedInitialForce * ball.vectorDirection.y * GetFrameTime(); 

		// Si la velocidad en ambos ejes est� en 0... 
		if (ball.speed.x == 0.0f && ball.speed.y == 0.0f)
		{
			ball.inMovement = false;
		}
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