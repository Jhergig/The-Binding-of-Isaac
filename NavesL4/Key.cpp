#include "Key.h"
#include "GameLayer.h"

Key::Key(float x, float y, Game* game) :
	Pickup("res/llave.png", x, y, 28, 40, game) {
}

void Key::giveBonus()
{
	((GameLayer*)game->gameLayer)->player->keys++;
	((GameLayer*)game->gameLayer)->keys_text->content = to_string(((GameLayer*)game->gameLayer)->player->keys);
}
