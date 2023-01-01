#include "Chocolate.h"
#include "GameLayer.h"

Chocolate::Chocolate(Game* game) : Pickup("res/item_chocolate.png", 0, 0, 50, 50, game) {
}

void Chocolate::giveBonus()
{
	((GameLayer*)game->gameLayer)->player->pf->add(new ChocolateShoot());
	((GameLayer*)game->gameLayer)->player->strength--;
	((GameLayer*)game->gameLayer)->message = new Actor("res/mensaje_chocolate.png", WIDTH / 2, HEIGHT / 2, 250, 150, game);
	((GameLayer*)game->gameLayer)->pause = true;
}

list<Projectile*> ChocolateShoot::addEffect(Projectile* projectile, int direction)
{
	Projectile* p2 = new Projectile(projectile->x, projectile->y, projectile->game);
	Projectile* p3 = new Projectile(projectile->x, projectile->y, projectile->game);
	if (direction == projectile->game->orientationRight || direction == projectile->game->orientationLeft) {
		p2->x = projectile->x + 10;
		p3->x = projectile->x - 10;
		p2->vx = projectile->vx;
		p3->vx = projectile->vx;
	}
	if (direction == projectile->game->orientationUp || direction == projectile->game->orientationDown) {
		p2->y = projectile->y + 10;
		p3->y = projectile->y - 10;
		p2->vy = projectile->vy;
		p3->vy = projectile->vy;
	}
	p2->setExpectedValues();
	p3->setExpectedValues();
	list<Projectile*> projectiles;
	projectiles.push_back(p2);
	projectiles.push_back(projectile);
	projectiles.push_back(p3);
	return projectiles;
}