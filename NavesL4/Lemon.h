#pragma once
#include "Pickup.h"
class Lemon : public Pickup
{
public:
	Lemon(Game* game);
	void giveBonus() override;
};

