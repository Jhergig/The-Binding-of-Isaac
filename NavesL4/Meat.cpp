#include "Meat.h"
#include "GameLayer.h"

Meat::Meat(Game* game) : Pickup("res/item_meat.png", 0, 0, 50, 50, game) {
}

void Meat::giveBonus()
{
	((GameLayer*)game->gameLayer)->player->strength++;
	((GameLayer*)game->gameLayer)->message = new Actor("res/mensaje_meat.png", WIDTH / 2, HEIGHT / 2, 250, 150, game);
	((GameLayer*)game->gameLayer)->pause = true;
}
