#pragma once
#include "Pickup.h"
class Meat : public Pickup
{
public:
	Meat(Game* game);
	void giveBonus() override;
};

