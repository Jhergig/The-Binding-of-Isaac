#pragma once
#include "Pickup.h"
#include "ProjectileFactory.h"

class Hourglass : public Pickup
{
public:
	Hourglass(Game* game);
	void giveBonus() override;
};

class HourglassShoot : public ProjectileFactory {
public:
	list<Projectile*> addEffect(Projectile* projectile, int direction) override;
};

