#pragma once
#include "Pickup.h"
#include "ProjectileFactory.h"

class Chocolate : public Pickup
{
public:
	Chocolate(Game* game);
	void giveBonus() override;
};

class ChocolateShoot : public ProjectileFactory {
public:
	list<Projectile*> addEffect(Projectile* projectile, int direction) override;
};

