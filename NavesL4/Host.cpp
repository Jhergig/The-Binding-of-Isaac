#include "Host.h"
#include "GameLayer.h"

Host::Host(float x, float y, Game* game) : Enemy(x, y, game)
{
	hp = 7;
	maxSpeed = 1;
	generationTime = 20;
	generationCadence = 20;

	aMoving = new Animation("res/enemy_host.png", 42, 66,
		56, 44, 20, 2, true, game);
}

void Host::actions()
{
	//movement
	if (((GameLayer*)game->gameLayer)->player->x > this->x) {
		if (vx < maxSpeed)
			vx++;
	}
	else {
		if (vx > -maxSpeed)
			vx--;
	}

	if (((GameLayer*)game->gameLayer)->player->y > this->y) {
		if (vy < maxSpeed)
			vy++;
	}
	else {
		if (vy > -maxSpeed)
			vy--;
	}

	//generation
	generationTime--;
	if (generationTime < 0) {
		spawnMancha();
		generationTime = generationCadence;
	}
}

void Host::spawnMancha()
{
	ManchaDañina* mancha = new ManchaDañina(x, y, game);
	((GameLayer*)game->gameLayer)->traps.push_back(mancha);
}