#pragma once

#include "Actor.h"
#include "Projectile.h" 
#include "Audio.h"
#include "Animation.h" // incluir animacion 
#include "ProjectileFactory.h"

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	list<Projectile*> shoot(int shootDirection);
	void update();
	void moveX(float axis);
	void moveY(float axis);
	void draw(float scrollX = 0, float scrollY=0) override; // Va a sobrescribir
	void loseLife();
	int lifes = 6;
	int maxLifes = 8;
	int strength = 3;
	int shootCadence = 24;
	int speed = 4;
	int money = 0;
	int keys = 0;

	int invulnerableTime = 0;
	int orientation;
	int shootDirection;
	int state;
	int shootTime = 0;
	Animation* aHeadRight;
	Animation* aHeadLeft;
	Animation* aHeadUp;
	Animation* aHeadDown;
	Animation* aShootRight;
	Animation* aShootLeft;
	Animation* aShootUp;
	Animation* aShootDown;
	Animation* aBodyDown;
	Animation* aMoveRight;
	Animation* aMoveLeft;
	Animation* aMoveUp;
	Animation* aMoveDown;
	Animation* headAnimation; // Referencia a la animación mostrada
	Animation* bodyAnimation; // Referencia a la animación mostrada
	Audio* audioShoot1;
	Audio* audioShoot2;
	ProjectileFactory* pf;
};

