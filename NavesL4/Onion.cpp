#include "Onion.h"
#include "GameLayer.h"

Onion::Onion(Game* game) : Pickup("res/item_onion.png", 0, 0, 50, 50, game) {
}

void Onion::giveBonus()
{
	((GameLayer*)game->gameLayer)->player->shootCadence -= 5;
	if (((GameLayer*)game->gameLayer)->player->shootCadence < 10) {
		((GameLayer*)game->gameLayer)->player->shootCadence = 10;
	}
	((GameLayer*)game->gameLayer)->message = new Actor("res/mensaje_onion.png", WIDTH / 2, HEIGHT / 2, 250, 150, game);
	((GameLayer*)game->gameLayer)->pause = true;
}
