#pragma once

#include "Actor.h"

class Door : public Actor
{
public:
	Door(int orientacion, float x, float y, Game* game, int type = 0);
	int orientacion;
	int type;
	 void movePlayer();
	 void draw(float scrollX = 0, float scrollY=0) override;
};

