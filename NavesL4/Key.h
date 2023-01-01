#pragma once
#include "Pickup.h"

class Key : public Pickup
{
public:
	Key(float x, float y, Game* game);
	void giveBonus() override;
};

