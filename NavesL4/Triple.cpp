#include "Triple.h"
#include "GameLayer.h"

Triple::Triple(Game* game) : Pickup("res/item_triple.png", 0, 0, 50, 50, game) {
}

void Triple::giveBonus()
{
	((GameLayer*)game->gameLayer)->player->pf->add(new TripleShoot());
	((GameLayer*)game->gameLayer)->message = new Actor("res/mensaje_triple.png", WIDTH / 2, HEIGHT / 2, 250, 150, game);
	((GameLayer*)game->gameLayer)->pause = true;
}

list<Projectile*> TripleShoot::addEffect(Projectile* projectile, int direction)
{
	Projectile* p2 = new Projectile(projectile->x, projectile->y, projectile->game);
	Projectile* p3 = new Projectile(projectile->x, projectile->y, projectile->game);
	if (direction == projectile->game->orientationRight || direction == projectile->game->orientationLeft) {
		p2->vx = projectile->vx;
		p3->vx = projectile->vx;
		p2->vy = projectile->vy + 1;
		p3->vy = projectile->vy - 1;
	}
	if (direction == projectile->game->orientationUp || direction == projectile->game->orientationDown) {
		p2->vx = projectile->vx + 1;
		p3->vx = projectile->vx - 1;
		p2->vy = projectile->vy;
		p3->vy = projectile->vy;
	}
	p2->setExpectedValues();
	p3->setExpectedValues();
	list<Projectile*> projectiles;
	projectiles.push_back(projectile);
	projectiles.push_back(p2);
	projectiles.push_back(p3);
	return projectiles;
}
