#pragma once
#include "Camera.h"

void drawBalls(BALL ball, int maxBalls)
{
	DrawCircle((int)ball.position.x, (int)ball.position.y, ball.radius, ball.color); // La bola blanca.	
}

void drawTable()
{
	DrawRectangle(150, 50, 600, 800, DARKGREEN);
	DrawRectangleLinesEx(Rectangle{ 150, 50, 600, 800 }, 15, DARKBROWN);
}