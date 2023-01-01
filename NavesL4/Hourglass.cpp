#include "Hourglass.h"
#include "GameLayer.h"

Hourglass::Hourglass(Game* game) : Pickup("res/item_hourglass.png", 0, 0, 50, 50, game) {
}

void Hourglass::giveBonus()
{
	((GameLayer*)game->gameLayer)->player->pf->add(new HourglassShoot());
	((GameLayer*)game->gameLayer)->message = new Actor("res/mensaje_hourglass.png", WIDTH / 2, HEIGHT / 2, 250, 150, game);
	((GameLayer*)game->gameLayer)->pause = true;
}

list<Projectile*> HourglassShoot::addEffect(Projectile* projectile, int direction)
{
	list<Projectile*> projectiles;
	if (rand() % 2 == 0) {
		projectile->addEffect(new Effect());
		projectile->texture = projectile->game->getTexture("res/disparo_jugador_efecto.png");
	}
	projectiles.push_back(projectile);
	return projectiles;
}