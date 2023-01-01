#pragma once
#include "Actor.h"
#include "Tile.h"

class Cerradura : public Actor
{
public:
	Cerradura(int orientation, float x, float y, Game* game, int type);
	Tile* puertaCerradura;
	bool cerrado;
};

