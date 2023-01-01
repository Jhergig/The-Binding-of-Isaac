#include "Cerradura.h"

Cerradura::Cerradura(int orientation, float x, float y, Game* game, int type) : Actor("res/invisible.png", x, y, 55, 55, game) {
	cerrado = true;

	string ending;
	if (type == 1)
		ending = "_dorada.png";
	if (type == 2)
		ending = "_tienda.png";
	if (orientation == game->orientationLeft) {
		puertaCerradura = new Tile("res/puerta_izquierda_cerradura" + ending, x, y - 25, game);
	}
	if (orientation == game->orientationRight) {
		puertaCerradura = new Tile("res/puerta_derecha_cerradura" + ending, x, y - 25, game);
	}
	if (orientation == game->orientationUp) {
		puertaCerradura = new Tile("res/puerta_arriba_cerradura" + ending, x, y - 25, game);
	}
	if (orientation == game->orientationDown) {
		puertaCerradura = new Tile("res/puerta_abajo_cerradura" + ending, x, y - 25, game);
	}
}

