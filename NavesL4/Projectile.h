#pragma once

#include "Actor.h"
#include "Effect.h"
#include <list>

class Projectile : public Actor
{
public:
	Projectile(float x, float y, Game* game);
	Projectile(float x, float y, float vx, float vy, Game* game);
	void addEffect(Effect* effect);
	void update();
	void setExpectedValues();
	list<Effect*> effects;
	float expectedVX;
	float expectedVY;
};

