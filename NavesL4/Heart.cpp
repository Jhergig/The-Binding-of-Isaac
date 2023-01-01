#include "Heart.h"
#include "GameLayer.h"

Heart::Heart(float x, float y, Game* game) :
	Pickup("res/corazon.png", x, y, 38, 31, game) {
	animation = new Animation("res/corazon.png", width, height,
		342, 31, 2, 9, true, game);
}

void Heart::update() {
	animation->update();
}

void Heart::draw(float scrollX, float scrollY)
{
	animation->draw(x - scrollX, y - scrollY);
}


void Heart::giveBonus()
{
	((GameLayer*)game->gameLayer)->player->lifes+=2;
	if (((GameLayer*)game->gameLayer)->player->maxLifes < ((GameLayer*)game->gameLayer)->player->lifes) {
		((GameLayer*)game->gameLayer)->player->lifes = ((GameLayer*)game->gameLayer)->player->maxLifes;
	}
}
