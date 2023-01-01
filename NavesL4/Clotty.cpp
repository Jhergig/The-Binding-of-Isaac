#include "Clotty.h"
#include "GameLayer.h"

Clotty::Clotty(float x, float y, Game* game) : Enemy(x, y, game)
{
	hp = 9;
	maxSpeed = 2;
	shootTime = 20;
	shootCadence = 60;
	movementRate = 50;
	movementTime = 0;
	aMoving = new Animation("res/enemy_clotty.png", 96, 96,
		704, 64, 2, 11, true, game);

}

void Clotty::actions() {
	//movement
	movementTime--;
	if (movementTime < 0) {
		movementTime = movementRate;
		if (rand() % 3 > 0)
			changeDirection();
	}

	if (vx == 0 || vy == 0) {
		changeDirection();
	}

	//shoot
	shootTime--;
	if (shootTime < 0) {
		shoot();
		shootTime = shootCadence;
	}
}

void Clotty::changeDirection() {
	vx = rand() % 2 == 0 ? -maxSpeed : maxSpeed;
	vy = rand() % 2 == 0 ? -maxSpeed : maxSpeed;
}

void Clotty::shoot()
{
	GameLayer* gl = ((GameLayer*)game->gameLayer);

	Projectile* newProjectile1 = new Projectile(x, y, 6, 0, game);
	Projectile* newProjectile2 = new Projectile(x, y, -6, 0, game);
	Projectile* newProjectile3 = new Projectile(x, y, 0, 6, game);
	Projectile* newProjectile4 = new Projectile(x, y, 0, -6, game);
	gl->space->addDynamicActor(newProjectile1);
	gl->space->addDynamicActor(newProjectile2);
	gl->space->addDynamicActor(newProjectile3);
	gl->space->addDynamicActor(newProjectile4);
	gl->enemyProjectiles.push_back(newProjectile1);
	gl->enemyProjectiles.push_back(newProjectile2);
	gl->enemyProjectiles.push_back(newProjectile3);
	gl->enemyProjectiles.push_back(newProjectile4);
}

