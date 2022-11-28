#include "Game.h"


void game()
{
	const int maxBalls = 2;
	BALL arrayBalls[maxBalls];

	//                                           X     Y    radius  mass id
	createBall(arrayBalls[0], GetScreenWidth() / 2, 650.0f, 10.0f, 5.0f, 0, WHITE);
	//linea de 5
	createBall(arrayBalls[1], GetScreenWidth() / 2 + 30, 200.0f, 10.0f, 5.0f, 1, RED);
	//createBall(arrayBalls[2], GetScreenWidth() / 2 + 60, 200.0f, 10.0f, 5.0f, 2, RED);
	//createBall(arrayBalls[3], GetScreenWidth() / 2 - 30, 200.0f, 10.0f, 5.0f, 3, GREEN);
	//createBall(arrayBalls[4], GetScreenWidth() / 2 - 60, 200.0f, 10.0f, 5.0f, 4, GREEN);
	//createBall(arrayBalls[5], GetScreenWidth() / 2, 200.0f, 10.0f, 5.0f, 5, BLUE);
	////linea de 4
	//createBall(arrayBalls[6], GetScreenWidth() / 2 - 45, 230.0f, 10.0f, 5.0f, 6, BLUE);
	//createBall(arrayBalls[7], GetScreenWidth() / 2 + 45, 230.0f, 10.0f, 5.0f, 7, DARKBLUE);
	//createBall(arrayBalls[8], GetScreenWidth() / 2 - 15, 230.0f, 10.0f, 5.0f, 8, DARKBLUE);
	//createBall(arrayBalls[9], GetScreenWidth() / 2 + 15, 230.0f, 10.0f, 5.0f, 9, VIOLET);
	////linea de 3
	//createBall(arrayBalls[10], GetScreenWidth() / 2 + 30, 260.0f, 10.0f, 5.0f, 10, VIOLET);
	//createBall(arrayBalls[11], GetScreenWidth() / 2 - 30, 260.0f, 10.0f, 5.0f, 11, ORANGE);
	//createBall(arrayBalls[12], GetScreenWidth() / 2, 260.0f, 10.0f, 5.0f, 12, ORANGE);
	////linea de 2
	//createBall(arrayBalls[13], GetScreenWidth() / 2 - 15, 290.0f, 10.0f, 5.0f, 13, YELLOW);
	//createBall(arrayBalls[14], GetScreenWidth() / 2 + 15, 290.0f, 10.0f, 5.0f, 14, YELLOW);
	////linea de 1
	//createBall(arrayBalls[15], GetScreenWidth() / 2, 320.0f, 10.0f, 5.0f, 15, BLACK);

	PLAYER P1 = CreatePlayer();

	while (!WindowShouldClose())
	{
		//ball
		if (IsKeyPressed(KEY_SPACE) && !arrayBalls[0].inMovement)
		{
			arrayBalls[0].inMovement = true;
			setSpeedBall(arrayBalls[0], GetMousePosition(), 20);
		}

		for (int i = 0; i < maxBalls; i++)
		{
			updateBall(arrayBalls[i]);
		}

		//cout << arrayBalls[0].speed.x << ", "<<arrayBalls[0].speed.y<< endl;
		//cout << arrayBalls[1].position.x << " " << arrayBalls[1].position.y << endl;

		//player
		PlayerMove(P1, arrayBalls[0]);

		//colisions
		for (int i = 0; i < maxBalls; i++)
		{
			//CheckBallWallColition(arrayBalls[i]);
			CheckBallCorner(arrayBalls[i]);
		}



		for (int i = 0; i < maxBalls; i++)
		{
			for (int j = 0; j < maxBalls; j++)
			{
				if (arrayBalls[i].id != arrayBalls[j].id)
				{
					if (overlap(arrayBalls[i].position.x, arrayBalls[i].position.y, arrayBalls[i].radius,
						arrayBalls[j].position.x, arrayBalls[j].position.y, arrayBalls[j].radius))
					{

						//distancia entre los centros de las bolas
						float fDistance = sqrtf((arrayBalls[i].position.x - arrayBalls[j].position.x) * (arrayBalls[i].position.x - arrayBalls[j].position.x) + (arrayBalls[i].position.y - arrayBalls[j].position.y) * (arrayBalls[i].position.y - arrayBalls[j].position.y));

						float fOverlap = 0.5f * (fDistance - arrayBalls[i].radius - arrayBalls[j].radius);

						//le doy a la posicion la mitad del overlapeo en la direccion normalizada
						arrayBalls[i].position.x -= fOverlap * (arrayBalls[i].position.x - arrayBalls[j].position.x) / fDistance;
						arrayBalls[i].position.y -= fOverlap * (arrayBalls[i].position.y - arrayBalls[j].position.y) / fDistance;

						arrayBalls[j].position.x += fOverlap * (arrayBalls[i].position.x - arrayBalls[j].position.x) / fDistance;
						arrayBalls[j].position.y += fOverlap * (arrayBalls[i].position.y - arrayBalls[j].position.y) / fDistance;


						//normal
						float nx = (arrayBalls[j].position.x - arrayBalls[i].position.x) / fDistance;
						float ny = (arrayBalls[j].position.y - arrayBalls[i].position.y) / fDistance;

						//tangente
						float tx = -ny;
						float ty = nx;

						//tangente del producto punto 
						float dpTan1 = arrayBalls[i].position.x * tx + arrayBalls[i].position.y * ty;
						float dpTan2 = arrayBalls[j].position.x * tx + arrayBalls[j].position.y * ty;

						//normal del producto punto 
						float dpNorm1 = arrayBalls[i].position.x * nx + arrayBalls[i].position.y * ny;
						float dpNorm2 = arrayBalls[j].position.x * nx + arrayBalls[j].position.y * ny;

						//conservacion de velocidad en 1d
						float m1 = (dpNorm1 * (arrayBalls[i].mass - arrayBalls[j].mass) + 2.0f * arrayBalls[j].mass * dpNorm2) / (arrayBalls[i].mass + arrayBalls[j].mass);
						float m2 = (dpNorm2 * (arrayBalls[j].mass - arrayBalls[i].mass) + 2.0f * arrayBalls[i].mass * dpNorm1) / (arrayBalls[i].mass + arrayBalls[j].mass);

						arrayBalls[i].speed.x = tx * dpTan1 + nx * m1;
						arrayBalls[i].speed.y = ty * dpTan1 + ny * m1;
						arrayBalls[j].speed.x = tx * dpTan2 + nx * m2;
						arrayBalls[j].speed.y = ty * dpTan2 + ny * m2;


					}

				}

			}
		}

		for (int i = 0; i < maxBalls; i++)
		{
			if (arrayBalls[i].inMovement)
			{
				for (int j = 0; j < maxBalls; j++)
				{
					CheckBallBallColition(arrayBalls[i], arrayBalls[j]);

				}
			}
		}


		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			arrayBalls[0].position = GetMousePosition();

		//draw
		BeginDrawing();
		ClearBackground(BLACK);
		drawTable();
		for (int i = 0; i < maxBalls; i++)
		{
			drawBalls(arrayBalls[i], maxBalls);
		}
		DrawRectanglePro(P1.rec, P1.origin, P1.rotation, BROWN);
		DrawCircleLines(static_cast<int>(arrayBalls[0].position.x), static_cast<int>(arrayBalls[0].position.y), arrayBalls[0].radius * 2, RED);


		EndDrawing();

	}

}
bool overlap(float x1, float y1, float r1, float x2, float y2, float r2)
{

	//chequeo si se overlapean las bolas usando pitagoras pero de una forma optimizada evitando el sqrt
	return fabs((x1 - x2) * (x1 - x2) + (y1, y2) * (y1 - y2)) <= (r1 + r2) * (r1 + r2);
}