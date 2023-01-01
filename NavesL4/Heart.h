#pragma once
#include "Pickup.h"
#include "Animation.h"

class Heart : public Pickup
{
public:
	Heart(float x, float y, Game* game);
	void update() override;
	void draw(float scrollX, float scrollY) override;
	void giveBonus() override;
	Animation* animation;
};

