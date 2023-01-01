#pragma once

#include "Enemy.h"
#include "Tile.h"
#include <list>

class Room
{
public:
	Room(Game* game);
	Game* game;
	list<Enemy*> enemies;
	list<Tile*> puertasCerradas;

	void update();
	void draw(float scrollX, float scrollY);
	void addEnemy(Enemy* enemy);
	void removeEnemy(Enemy* enemy);
	void addPuertaCerrada(Tile* puerta);
};

