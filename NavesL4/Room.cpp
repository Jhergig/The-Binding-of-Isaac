#include "Room.h"

Room::Room(Game* game)
{
	this->game = game;
	this->enemies.clear();
	this->puertasCerradas.clear();
}

void Room::update()
{
	for (auto const& enemy : enemies) {
		enemy->update();
	}
}

void Room::draw(float scrollX, float scrollY)
{
	for (auto const& enemy : enemies) {
		enemy->draw(scrollX, scrollY);
	}

	for (auto const& puerta : puertasCerradas) {
		puerta->draw(scrollX, scrollY);
	}
}

void Room::addEnemy(Enemy* enemy)
{
	enemies.push_back(enemy);
}

void Room::removeEnemy(Enemy* enemy)
{
	enemies.remove(enemy);
}

void Room::addPuertaCerrada(Tile* puerta) {
	puertasCerradas.push_back(puerta);
}

