#pragma once
#include "Actor.h"

class Trap : public Actor
{
public:
	Trap(float x, float y, Game* game);
	virtual void update();

	int state;
};

