#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"

#include "Enemy.h"
#include "Trap.h"
#include "Projectile.h"
#include "Text.h"
#include "Tile.h"
#include "Pad.h"
#include "Door.h"
#include "Cerradura.h"
#include "Pickup.h"
#include "ArticuloEnVenta.h"

#include "Audio.h"
#include "Space.h" // importar

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>
#include <map>
#include "Room.h"

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	void gamePadToControls(SDL_Event event); // USO DE GAMEPAD
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	Pickup* getItem();
	string getRoomFromUbication(float x, float y);
	void calculateScroll(bool paneo = true);
	Actor* message;
	bool pause;
	// Elementos de interfaz
	SDL_GameController* gamePad;
	Actor* contenedores_vida[12];
	Actor* vidas[12];
	Actor* mediaVida;
	Actor* money_hud;
	Actor* keys_hud;
	Text* money_text;
	Text* keys_text;

	Tile* cup; // Elemento de final de nivel
	Space* space;
	float scrollX;
	float scrollY;
	int mapWidth;
	list<Tile*> tiles;

	Audio* audioBackground;
	int newEnemyTime = 0;
	Player* player;
	Background* background;
	int paneoTotalFrames = 30;
	int paneoFrame = 30;
	Actor* backgroundPoints;
	list<Projectile*> projectiles;
	list<Projectile*> enemyProjectiles;
	list<Trap*> traps;
	list<Door*> doors;
	list<Cerradura*> cerraduras;
	list<Pickup*> pickups;
	list<Pickup*> items;
	list<ArticuloEnVenta*> tienda;
	map<string, Room*> rooms;
	Room* currentRoom;
	int roomChanched = -1;

	bool controlContinue = false;
	int controlShoot = 0;
	int controlMoveY = 0;
	int controlMoveX = 0;


};

