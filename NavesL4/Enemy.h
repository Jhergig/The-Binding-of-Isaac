#pragma once

#include "Actor.h"
#include "Animation.h" 

class Enemy : public Actor
{
public:
	Enemy(float x, float y, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void update();
	virtual void actions();
	void impacted(int dmg); // Recibe impacto y pone animación de morir
	int state;
	int hp = 4;
	int maxSpeed = 8;
	Animation* aDying;
	Animation* aMoving;
	Animation* animation; // Referencia a la animación mostrada
};
