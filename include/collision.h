#pragma once

// Cubes Struct//
struct Cube Moving[4];

bool checkCollision(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh)
{
	if (Ay + Ah < By) return false;
	else if (Ay > By + Bh) return false;
	else if (Ax + Aw < Bx) return false;
	else if (Ax > Bx + Bw) return false;

	return true;
}

/////////////////////////////////////////////////////// Collision Detection //////////////////////////////////////////////////////////////

void collision()
{
	// Player/Cube //

	for (int i = 0; i < 4; i++)
	{
		if (checkCollision(playerX, playerY, playerWidth, playerHeight, Moving[i].cubeX, Moving[i].cubeY, Moving[i].cubeSizeY, Moving[i].cubeSizeY) == true)
		{
			printf("Player HIT Cube\n");
			playerLives -= 1;
			playerX = -15;
			playerY = 0;
			Moving[i].cubeX = 24 + distr(gen) / 2;
			Moving[i].cubeY = distr(gen);

			printf("Lost Life 3\n");
		}
	}

	// Laser/Cube //

	for (int i = 0; i < 4; i++)
	{
		if (checkCollision(laserX, laserY, laserSizeX, laserSizeY, Moving[i].cubeX, Moving[i].cubeY, Moving[i].cubeSizeY, Moving[i].cubeSizeY) == true)//Check for collision
		{
			printf("Laser HIT Cube\n");
			Moving[i].cubeX = 24 + distr(gen) / 2;
			Moving[i].cubeY = distr(gen);
			playerScore += 5;
			
			
		}

		if (Moving[i].cubeX <= -20)
		{
			Moving[i].cubeX = 24 + distr(gen) / 2;
			Moving[i].cubeY = distr(gen);
			SPEED += 0.01;
		}
	}



	// Screen edge collision //
	if (playerX < -15) { playerX = -15; }
	if (playerX > 15) { playerX = 15; }
	if (playerY < -11) { playerY = -11; }
	if (playerY > 11) { playerY = 11; }


}