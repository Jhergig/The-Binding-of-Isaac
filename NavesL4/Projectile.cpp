#include "Projectile.h"

Projectile::Projectile(float x, float y, Game* game) :
	Actor("res/disparo_jugador.png", x, y, 24, 24, game) {
	setExpectedValues();
}

Projectile::Projectile(float x, float y, float vx, float vy, Game* game) :
	Actor("res/disparo_enemigo.png", x, y, 24, 24, game) {
	this->vx = vx;
	this->vy = vy;
	setExpectedValues();
}

void Projectile::addEffect(Effect* effect)
{
	effects.push_back(effect);
}

void Projectile::update() {
	//vy = vy - 1; // La gravedad suma 1 en cada actualización restamos para anularla 
}

void Projectile::setExpectedValues()
{
	expectedVX = this->vx;
	expectedVY = this->vy;
}
