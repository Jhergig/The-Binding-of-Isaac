#include "Juice.h"
#include "GameLayer.h"

Juice::Juice(Game* game) : Pickup("res/item_juice.png", 0, 0, 50, 50, game) {
}

void Juice::giveBonus()
{
	((GameLayer*)game->gameLayer)->player->maxLifes+=2;
	if (((GameLayer*)game->gameLayer)->player->maxLifes > 24) {
		((GameLayer*)game->gameLayer)->player->maxLifes = 24;
	}
	((GameLayer*)game->gameLayer)->player->lifes+=2;
	if (((GameLayer*)game->gameLayer)->player->maxLifes < ((GameLayer*)game->gameLayer)->player->lifes) {
		((GameLayer*)game->gameLayer)->player->lifes = ((GameLayer*)game->gameLayer)->player->maxLifes;
	}
	((GameLayer*)game->gameLayer)->message = new Actor("res/mensaje_juice.png", WIDTH / 2, HEIGHT / 2, 250, 150, game);
	((GameLayer*)game->gameLayer)->pause = true;
}
