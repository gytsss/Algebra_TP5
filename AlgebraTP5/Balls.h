#ifndef BALL_H 
#define BALL_H 

#include "raylib.h" 
#include "raymath.h"

const int leftWall = 160;
const int rightWall = 750;
const int upperWall = 50;
const int bottomWall = 850;

struct BALL
{
	Vector2 position;

	bool inMovement;
	float radius;
	float mass;

	float angle;
	Vector2 speed;
	Color color;
	int id;

	float receivedInitialForce;
	float friction;
	

	

};


void createBall(BALL& newBall, float x, float y, float radius, float mass, int id, Color color); // Crea la bola con los valores pasados por par�metro. 

void updateBall(BALL& ball); // Actualiza el estado de la bola. Esta funci�n debe llamarse siempre. 
void setSpeedBall(BALL& ball, Vector2 originForcePosition, float force); // Establece una nueva velocidad a la bola. Pisa la velocidad anterior. 
void setSpeedBall(BALL& ball, Vector2 speed); // Modifica la velocidad actual de la bola. Se le suma a la velocidad actual. 

#endif // !BALL_H 