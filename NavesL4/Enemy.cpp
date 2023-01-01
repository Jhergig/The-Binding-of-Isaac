#include "Enemy.h"
#include "GameLayer.h"

Enemy::Enemy(float x, float y, Game* game)
	: Actor("res/enemigo.png", x, y, 48, 33, game) {

	state = game->stateMoving;

	aDying = new Animation("res/enemy_dying.png", 50, 50,
		130, 42, 5, 2, false, game);

	aMoving = new Animation("res/enemy_bat.png", width, height,
		144, 33, 6, 3, true, game);
	animation = aMoving;

	vx = 0;
}

void Enemy::update() {
	// Actualizar la animación
	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
		}
	}

	if (state == game->stateMoving) {
		animation = aMoving;
	}
	if (state == game->stateDying) {
		animation = aDying;
	}

	// Establecer velocidad
	if (state != game->stateDying) {
		// no está muerto
		actions();
	}
	else {
		vx = 0;
	}
}

void Enemy::actions() {
	//movement
	if (((GameLayer*)game->gameLayer)->player->x > this->x) {
		if (vx < maxSpeed)
			vx++;
	}
	else {
		if (vx > -maxSpeed)
			vx--;
	}

	if (((GameLayer*)game->gameLayer)->player->y > this->y) {
		if (vy < maxSpeed)
			vy++;
	}
	else {
		if (vy > -maxSpeed)
			vy--;
	}
}

void Enemy::impacted(int dmg) {
	if (state != game->stateDying) {
		hp -= dmg;
		if (hp <= 0)
			state = game->stateDying;
	}
}


void Enemy::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}


