#pragma once
#include "Projectile.h"
#include "Game.h"
#include <list>


class ProjectileFactory
{
public:
	ProjectileFactory();
	void add(ProjectileFactory* pf);
	ProjectileFactory* pf;
	list<Projectile*> shoot(int direction, float x, float y, Game* game);
	virtual list<Projectile*> addEffect(Projectile* p, int direction);
};

