#include "GeneratorEnemy.h"
#include "GameLayer.h"

GeneratorEnemy::GeneratorEnemy(float x, float y, Game* game) : Enemy(x, y, game)
{
	hp = 6;
	maxSpeed = 3;
	generationTime = 20;
	generationCadence = 120;

	aMoving = new Animation("res/enemy_fat_bat.png", 72, 48,
		384, 32, 6, 8, true, game);
}

void GeneratorEnemy::actions()
{
	//movement
	if (((GameLayer*)game->gameLayer)->player->x > this->x) {
		if (vx > -maxSpeed)
			vx--;
	}
	else {
		if (vx < maxSpeed)
			vx++;
	}

	if (((GameLayer*)game->gameLayer)->player->y > this->y) {
		if (vy > -maxSpeed)
			vy--;
	}
	else {
		if (vy < maxSpeed)
			vy++;
	}

	//generation
	generationTime--;
	if (generationTime < 0) {
		spawnEnemy();
		generationTime = generationCadence;
	}
}

void GeneratorEnemy::spawnEnemy()
{
	Enemy* enemy = new Enemy(x, y, game);
	((GameLayer*)game->gameLayer)->currentRoom->enemies.push_back(enemy);
	((GameLayer*)game->gameLayer)->space->addDynamicActor(enemy);
}
