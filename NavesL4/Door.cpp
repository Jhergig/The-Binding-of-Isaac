#include "Door.h"
#include "GameLayer.h"

Door::Door(int orientacion, float x, float y, Game* game, int type)
	: Actor("res/puerta_izquierda.png", x, y, 50, 50, game) {
	this->orientacion = orientacion;
	string ending;
	if (type == 0)
		ending = ".png";
	if (type == 1)
		ending = "_dorada.png";
	if (type == 2)
		ending = "_tienda.png";
	if (orientacion == game->orientationLeft) {
		texture = game->getTexture("res/puerta_izquierda" + ending);
	}
	if (orientacion == game->orientationRight) {
		texture = game->getTexture("res/puerta_derecha" + ending);
	}
	if (orientacion == game->orientationUp) {
		texture = game->getTexture("res/puerta_arriba" + ending);
	}
	if (orientacion == game->orientationDown) {
		texture = game->getTexture("res/puerta_abajo" + ending);
	}
}

void Door::movePlayer()
{
	if (orientacion == game->orientationRight) {
		((GameLayer*)game->gameLayer)->player->x += 280;
	}
	if (orientacion == game->orientationLeft) {
		((GameLayer*)game->gameLayer)->player->x -= 280;
	}
	if (orientacion == game->orientationUp) {
		((GameLayer*)game->gameLayer)->player->y -= 200;
	}
	if (orientacion == game->orientationDown) {
		((GameLayer*)game->gameLayer)->player->y += 200;
	}
	
}

void Door::draw(float scrollX, float scrollY)
{
	if (orientacion == game->orientationRight) {

		// Recorte en el fichero de la imagen
		SDL_Rect source;
		source.x = 0;
		source.y = 0;
		source.w = 100; // texture.width;
		source.h = 150; // texture.height;

		// Donde se va a pegar en el renderizador
		SDL_Rect destination;
		destination.x = x - width / 2 - 50 - scrollX;
		destination.y = y - height / 2 - 50 - scrollY;
		destination.w = 100;
		destination.h = 150;
		// Modificar para que la referencia sea el punto central
		SDL_RenderCopyEx(game->renderer,
			texture, &source, &destination, 0, NULL, SDL_FLIP_NONE);
	}
	if (orientacion == game->orientationLeft) {
		// Recorte en el fichero de la imagen
		SDL_Rect source;
		source.x = 0;
		source.y = 0;
		source.w = 100; // texture.width;
		source.h = 150; // texture.height;

		// Donde se va a pegar en el renderizador
		SDL_Rect destination;
		destination.x = x - width / 2 - scrollX;
		destination.y = y - height / 2 - 50 - scrollY;
		destination.w = 100;
		destination.h = 150;
		// Modificar para que la referencia sea el punto central
		SDL_RenderCopyEx(game->renderer,
			texture, &source, &destination, 0, NULL, SDL_FLIP_NONE);
	}
	if (orientacion == game->orientationUp) {
		// Recorte en el fichero de la imagen
		SDL_Rect source;
		source.x = 0;
		source.y = 0;
		source.w = 150; // texture.width;
		source.h = 100; // texture.height;

		// Donde se va a pegar en el renderizador
		SDL_Rect destination;
		destination.x = x - width / 2 - 50 - scrollX;
		destination.y = y - height / 2 - scrollY;
		destination.w = 150;
		destination.h = 100;
		// Modificar para que la referencia sea el punto central
		SDL_RenderCopyEx(game->renderer,
			texture, &source, &destination, 0, NULL, SDL_FLIP_NONE);
	}

	if (orientacion == game->orientationDown) {
		// Recorte en el fichero de la imagen
		SDL_Rect source;
		source.x = 0;
		source.y = 0;
		source.w = 150; // texture.width;
		source.h = 100; // texture.height;

		// Donde se va a pegar en el renderizador
		SDL_Rect destination;
		destination.x = x - width / 2 - 50 - scrollX;
		destination.y = y - height / 2 - 50 - scrollY;
		destination.w = 150;
		destination.h = 100;
		// Modificar para que la referencia sea el punto central
		SDL_RenderCopyEx(game->renderer,
			texture, &source, &destination, 0, NULL, SDL_FLIP_NONE);
	}
}
