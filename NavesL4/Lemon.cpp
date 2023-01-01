#include "Lemon.h"
#include "GameLayer.h"

Lemon::Lemon (Game* game): Pickup("res/item_lemon.png", x, y, 50, 50, game) {
}

void Lemon::giveBonus()
{
	((GameLayer*)game->gameLayer)->player->speed++;
	if (((GameLayer*)game->gameLayer)->player->speed > 7) {
		((GameLayer*)game->gameLayer)->player->speed = 7;
	}
	((GameLayer*)game->gameLayer)->message = new Actor("res/mensaje_lemon.png", WIDTH / 2, HEIGHT / 2, 250, 150, game);
	((GameLayer*)game->gameLayer)->pause = true;
}
