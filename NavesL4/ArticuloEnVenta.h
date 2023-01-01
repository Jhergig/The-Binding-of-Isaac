#pragma once
#include "Pickup.h"
#include "Text.h"

class ArticuloEnVenta : public Pickup
{
public:
	ArticuloEnVenta(Pickup* articulo, float x, float y, Game* game);
	void giveBonus() override;
	void update() override;
	void draw(float scrollX, float scrollY) override;
	Pickup* articulo;
	int precio;
	bool vendido = false;
	Text* precio_hud;
};

