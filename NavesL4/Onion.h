#pragma once
#include "Pickup.h"
class Onion : public Pickup
{
public:
	Onion(Game* game);
	void giveBonus() override;
};

