#pragma once
#include "Camera.h"

void drawBalls(BALL ball, int maxBalls)
{
	DrawCircle((int)ball.position.x, (int)ball.position.y, ball.radius, ball.color); // La bola blanca.	
}

void drawTable()
{
	DrawRectangle(150, 50, 600, 800, DARKGREEN);
	DrawRectangleLinesEx(Rectangle{ 135, 35, 630, 830 }, 15, DARKBROWN);

	DrawCircle(150, 50, 15, BLACK);
	DrawCircle(750, 50, 15, BLACK);

	DrawCircle(150, 450, 15, BLACK);
	DrawCircle(750, 450, 15, BLACK);

	DrawCircle(150, 850, 15, BLACK);
	DrawCircle(750, 850, 15, BLACK);
}