#pragma once

#include "Actor.h"

class Background : public Actor
{
public:
	Background(string filename, float x, float y, Game* game, bool main = true);
	void draw(float scrollX, float scrollY) override; // Va a sobrescribir
	void update();
	Background* backgroundAux = nullptr;

};
