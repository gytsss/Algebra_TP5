#pragma once
#include "raylib.h"
#include "raymath.h"

#include "Balls.h"

struct PLAYER
{
	Rectangle rec;
	Vector2 origin;
	float rotation;
	Color color;
};

PLAYER CreatePlayer();

void PlayerMove(PLAYER& P1, BALL& ball1);