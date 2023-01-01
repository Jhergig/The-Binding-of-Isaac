#include "GunmanEnemy.h"
#include "GameLayer.h"

GunmanEnemy::GunmanEnemy(float x, float y, Game* game) : Enemy(x, y, game)
{
	hp = 5;
	shootTime = 20;
	shootCadence = 60;

	aMoving = new Animation("res/enemy_pooter.png", 50, 50,
		512, 32, 2, 16, true, game);
	
}

void GunmanEnemy::actions() {
	//movement

	//shoot
	shootTime--;
	if (shootTime < 0) {
		shoot();
		shootTime = shootCadence;
	}
}

void GunmanEnemy::shoot()
{
	GameLayer* gl = ((GameLayer*)game->gameLayer);
	int dx = gl->player->x - x;
	int dy = gl->player->y - y;
	float diagonalDistance = sqrt(dx * dx + dy * dy);
	float factor = 10 / diagonalDistance;
	float vxProjectile = dx * factor;
	float vyProjectile = dy * factor;
	Projectile* newProjectile = new Projectile(x, y, vxProjectile, vyProjectile, game);
	gl->space->addDynamicActor(newProjectile);
	gl->enemyProjectiles.push_back(newProjectile);
}

