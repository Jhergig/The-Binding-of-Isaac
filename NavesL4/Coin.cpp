#include "Coin.h"
#include "GameLayer.h"

Coin::Coin(float x, float y, Game* game) :
	Pickup("res/moneda.png", x, y, 36, 26, game) {
	animation = new Animation("res/moneda.png", width, height,
		360, 26, 2, 10, true, game);
}

void Coin::giveBonus()
{
	((GameLayer*)game->gameLayer)->player->money++;
	((GameLayer*)game->gameLayer)->money_text->content = to_string(((GameLayer*)game->gameLayer)->player->money);
}

void Coin::update() {
	animation->update();
}

void Coin::draw(float scrollX, float scrollY)
{
	animation->draw(x - scrollX, y - scrollY);
}
