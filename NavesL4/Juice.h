#pragma once
#include "Pickup.h"
class Juice : public Pickup
{
public:
	Juice(Game* game);
	void giveBonus() override;
};

