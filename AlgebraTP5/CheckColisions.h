#pragma once
#include "Balls.h"
#include "raylib.h"
#include <iostream>

using namespace std;

void CheckBallWallColition(BALL& ball);
void CheckBallBallColition(BALL& ball1, BALL& ball2);
void CheckBallCorner(BALL& ball);