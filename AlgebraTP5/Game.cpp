#include "Game.h"

void game()
{
	const int maxBalls = 2;
	BALL arrayBalls[maxBalls];

	//                           X       Y    radius  mass
	createBall(arrayBalls[0], GetScreenWidth() / 2, 650.0f, 10.0f, 5.0f, 0, WHITE);
	//linea de 5
	createBall(arrayBalls[1], GetScreenWidth() / 2 + 30, 200.0f, 10.0f, 5.0f, 1, RED);
	//createBall(arrayBalls[2], GetScreenWidth() / 2 + 60, 200.0f, 10.0f, 5.0f, 2,RED);
	//createBall(arrayBalls[3], GetScreenWidth() / 2 - 30, 200.0f, 10.0f, 5.0f, 3,GREEN);
	//createBall(arrayBalls[4], GetScreenWidth() / 2 - 60, 200.0f, 10.0f, 5.0f, 4,GREEN);
	//createBall(arrayBalls[5], GetScreenWidth() / 2, 200.0f, 10.0f, 5.0f, 5,BLUE);
	////linea de 4
	//createBall(arrayBalls[6], GetScreenWidth() / 2 - 45, 230.0f, 10.0f, 5.0f, 6,BLUE);
	//createBall(arrayBalls[7], GetScreenWidth() / 2 + 45, 230.0f, 10.0f, 5.0f, 7,DARKBLUE);
	//createBall(arrayBalls[8], GetScreenWidth() / 2 - 15, 230.0f, 10.0f, 5.0f, 8,DARKBLUE);
	//createBall(arrayBalls[9], GetScreenWidth() / 2 + 15, 230.0f, 10.0f, 5.0f, 9,VIOLET);
	////linea de 3
	//createBall(arrayBalls[10], GetScreenWidth() / 2 + 30, 260.0f, 10.0f, 5.0f, 10,VIOLET);
	//createBall(arrayBalls[11], GetScreenWidth() / 2 - 30, 260.0f, 10.0f, 5.0f, 11,ORANGE);
	//createBall(arrayBalls[12], GetScreenWidth() / 2, 260.0f, 10.0f, 5.0f, 12,ORANGE);
	////linea de 2
	//createBall(arrayBalls[13], GetScreenWidth() / 2 - 15, 290.0f, 10.0f, 5.0f, 13,YELLOW);
	//createBall(arrayBalls[14], GetScreenWidth() / 2 + 15, 290.0f, 10.0f, 5.0f, 14,YELLOW);
	////linea de 1
	//createBall(arrayBalls[15], GetScreenWidth() / 2, 320.0f, 10.0f, 5.0f, 15,BLACK);

	PLAYER P1 = CreatePlayer();

	while (!WindowShouldClose())
	{
		//ball
		if (IsKeyPressed(KEY_SPACE) && !arrayBalls[0].inMovement)
		{
			arrayBalls[0].inMovement = true;
			setSpeedBall(arrayBalls[0], GetMousePosition(), 15);
		}

		for (int i = 0; i < maxBalls; i++)
		{
			updateBall(arrayBalls[i]);
		}

		cout << arrayBalls[0].speed.x << ", "<<arrayBalls[0].speed.y<< endl;
		//cout << arrayBalls[1].position.x << " " << arrayBalls[1].position.y << endl;

		//player
		PlayerMove(P1, arrayBalls[0]);

		//colisions
		for (int i = 0; i < maxBalls; i++)
		{
			CheckBallWallColition(arrayBalls[i]);
			CheckBallCorner(arrayBalls[i]);
		}

		for (int i = 0; i < maxBalls; i++)
		{
			if (arrayBalls[i].inMovement)
			{
				for (int y = 0; y < maxBalls; y++)
				{
					CheckBallBallColition(arrayBalls[i], arrayBalls[y]);
				}
			}
		}

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