#include "Trap.h"

Trap::Trap(float x, float y, Game* game)
	: Actor("res/pinchos.png", x, y, 46, 52, game) {
	state = game->stateMoving;
}

void Trap::update() {
}