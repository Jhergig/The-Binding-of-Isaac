#pragma once
#include "Pickup.h"
#include "ProjectileFactory.h"

class Triple : public Pickup
{
public:
	Triple(Game* game);
	void giveBonus() override;
};

class TripleShoot : public ProjectileFactory {
public:
	list<Projectile*> addEffect(Projectile* projectile, int direction) override;
};
