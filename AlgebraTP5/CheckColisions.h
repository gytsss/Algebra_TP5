#pragma once
#include "Balls.h"
#include "raylib.h"
#include <iostream>

using namespace std;

void CheckBallWallColition(BALL& ball);
void CheckBallBallColition(BALL& ball1, BALL& ball2);
void CheckBallCorner(BALL& ball);
bool CheckCollisionCircleCircle(Vector2 ball, float radius1, Vector2 ball2, float radius2);
void ElasticCollision(BALL& ball1, BALL& ball2);