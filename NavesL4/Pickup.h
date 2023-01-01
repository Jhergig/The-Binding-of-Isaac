#pragma once
#include "Actor.h"

class Pickup : public Actor
{
public:
	Pickup(string filename, float x, float y, int width, int height, Game* game);
	virtual void update();
	virtual void giveBonus() = 0;
};
