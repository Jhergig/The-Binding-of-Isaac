#include "ManchaDa�ina.h"

ManchaDa�ina::ManchaDa�ina(float x, float y, Game* game) : Trap(x, y, game)
{
	vidaTime = 200;

	aMoving = new Animation("res/mancha.png", 88, 78,
		176, 78, 4, 2, true, game);
	aDying = new Animation("res/mancha_agotada.png", 88, 78,
		88, 78, 90, 1, false, game);
	animation = aMoving;

}

void ManchaDa�ina::update()
{
	// Actualizar la animaci�n
	bool endAnimation = animation->update();

	vidaTime--;
	if (vidaTime < 0) {
		state = game->stateDying;
	}

	// Acabo la animaci�n, no sabemos cual
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
	
}

void ManchaDa�ina::draw(float scrollX, float scrollY)
{
	animation->draw(x - scrollX, y - scrollY);
}
