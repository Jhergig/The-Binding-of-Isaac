#include "ArticuloEnVenta.h"

#include "GameLayer.h"

ArticuloEnVenta::ArticuloEnVenta(Pickup* articulo, float x, float y, Game* game) :
	Pickup("res/moneda.png", x, y, articulo->width, articulo->height, game) {
	this->articulo = articulo;
	precio = rand() % 10 + 5;
	precio_hud = new Text(to_string(precio), x, y + 20, game);
}

void ArticuloEnVenta::giveBonus()
{
	if (((GameLayer*)game->gameLayer)->player->money >= precio) {
		((GameLayer*)game->gameLayer)->player->money -= precio;
		((GameLayer*)game->gameLayer)->money_text->content = to_string(((GameLayer*)game->gameLayer)->player->money);
		articulo->giveBonus();
		vendido = true;
	}
}

void ArticuloEnVenta::update() {
	articulo->update();
}

void ArticuloEnVenta::draw(float scrollX, float scrollY) {
	articulo->draw(scrollX, scrollY);
	precio_hud->draw(scrollX, scrollY);
}
