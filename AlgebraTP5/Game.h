#pragma once
#include <iostream>

#include "raylib.h"

#include "Balls.h"
#include "Camera.h"
#include "CheckColisions.h"
#include "Game.h"
#include "Player.h"

using namespace std;

void game();
bool overlap(float x1, float y1, float r1, float x2, float y2, float r2);