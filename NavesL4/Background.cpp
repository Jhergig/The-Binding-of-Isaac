#include "Background.h"

Background::Background(string filename, float x, float y, Game* game, bool main)
	: Actor(filename, x, y, WIDTH, HEIGHT, game) {
	if (main) {
		backgroundAux = new Background(filename, x, y, game, false);
	}
}

void Background::update() {
	/*
	if (vx != 0) {
		x = x + vx;

		// se salio por la izquierda
		if (x + width / 2 < 0) {
			// vuelve a aparecer por la derecha
			x = WIDTH + width / 2;
		}
		// se salio por la derecha
		if (x - width / 2 > WIDTH) {
			// vuelve por la izquierda
			x = 0 - width / 2;
		}

	}
	*/
}

void Background::draw(float scrollX, float scrollY) {
	int bScrollX = int(scrollX) % WIDTH;
	int bScrollY = int(scrollY) % HEIGHT;
	Actor::draw(bScrollX, bScrollY); // llamar al metodo del hijo

	if (backgroundAux != NULL) {
		// zona sin cubrir por la izquierda
		if (x - width / 2 - bScrollX > 0) {
			// pintar aux por la izquierda
			backgroundAux->x = x + width;
			backgroundAux->y = y;
		}
		// zona sin cubrir por la derecha
		if (x + width / 2 - bScrollX < WIDTH) {
			// pintar aux por la derecha
			backgroundAux->x = x + width;
			backgroundAux->y = y;
		}

		if (y - height / 2 - bScrollY > 0) {
			backgroundAux->x = x;
			backgroundAux->y = y + height;
		}
		if (y + height / 2 - bScrollY < HEIGHT) {
			backgroundAux->x = x;
			backgroundAux->y = y + height;
		}
		backgroundAux->draw(scrollX, scrollY);
	}

}

