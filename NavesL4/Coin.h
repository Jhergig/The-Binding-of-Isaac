#pragma once
#include "Pickup.h"
#include "Animation.h"

class Coin : public Pickup
{
public:
	Coin(float x, float y, Game* game);
	void giveBonus() override;
	void update() override;
	void draw(float scrollX, float scrollY) override;
	Animation* animation;
};

