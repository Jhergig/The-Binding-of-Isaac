#include "GameLayer.h"
#include "GeneratorEnemy.h"
#include "GunmanEnemy.h"
#include "Clotty.h"
#include "Host.h"
#include "ManchaDañina.h"
#include "Heart.h"
#include "Coin.h"
#include "Key.h"
#include <chrono>
#include "Lemon.h"
#include "Hourglass.h"
#include "Meat.h"
#include "Onion.h"
#include "Chocolate.h"
#include "Triple.h"
#include "Juice.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	message = new Actor("res/mensaje_como_jugar.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);

	gamePad = SDL_GameControllerOpen(0);
	init();
}


void GameLayer::init() {
	space = new Space(0);
	scrollX = 0;
	scrollY = 0;
	tiles.clear();

	audioBackground = new Audio("res/ost.mp3", true);
	audioBackground->play();
	srand(std::chrono::system_clock::now().time_since_epoch().count());
	
	background = new Background("res/fondo_2.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	for (int i= 0; i < 6; i++) {
		contenedores_vida[i] = new Actor("res/hud_contenedor_vida.png",
			WIDTH * 0.05 + i * 24, HEIGHT * 0.05, 26, 24, game);
	}
	for (int i = 0; i < 6; i++) {
		contenedores_vida[i+6] = new Actor("res/hud_contenedor_vida.png",
			WIDTH * 0.05 + i * 24, HEIGHT * 0.05 + 20, 26, 24, game);
	}
	for (int i = 0; i < 6; i++) {
		vidas[i] = new Actor("res/hud_vida.png",
			WIDTH * 0.05 + i * 24, HEIGHT * 0.05, 26, 24, game);
	}
	for (int i = 0; i < 6; i++) {
		vidas[i + 6] = new Actor("res/hud_vida.png",
			WIDTH * 0.05 + i * 24, HEIGHT * 0.05 + 20, 26, 24, game);
	}
	mediaVida = new Actor("res/hud_vida.png",
		WIDTH * 0.05, HEIGHT * 0.05, 26, 24, game);

	rooms.clear(); // Vaciar por si reiniciamos el juego
	projectiles.clear(); // Vaciar por si reiniciamos el juego
	enemyProjectiles.clear(); // Vaciar por si reiniciamos el juego
	doors.clear(); // Vaciar por si reiniciamos el juego
	cerraduras.clear(); // Vaciar por si reiniciamos el juego
	pickups.clear(); // Vaciar por si reiniciamos el juego
	items.clear(); // Vaciar por si reiniciamos el juego
	tienda.clear(); // Vaciar por si reiniciamos el juego
	traps.clear(); // Vaciar por si reiniciamos el juego

	loadMap("res/" + to_string(game->currentLevel) + ".txt");

	money_text = new Text(to_string(player->money), WIDTH * 0.08, HEIGHT * 0.2, game);
	keys_text = new Text(to_string(player->keys), WIDTH * 0.08, HEIGHT * 0.2 + 20, game);
	money_hud = new Actor("res/hud_monedas.png", WIDTH * 0.05, HEIGHT * 0.2, 18, 22, game);
	keys_hud = new Actor("res/hud_llaves.png", WIDTH * 0.05, HEIGHT * 0.2 + 20, 18, 24, game);

	calculateScroll(false);
}

void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidth = line.length() * 40; // Ancho del mapa en pixels
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 50 / 2 + j * 50; // x central
				float y = 50 + i * 50; // y suelo
				loadMapObject(character, x, y);
			}

			cout << character << endl;
		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case 'T': {
		cup = new Tile("res/trampilla.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		cup->y = cup->y - cup->height / 2;
		space->addDynamicActor(cup); // Realmente no hace falta
		break;
	}
	case 'P': {
		GunmanEnemy* enemy = new GunmanEnemy(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		string key = getRoomFromUbication(x, y);
		rooms[key]->addEnemy(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'F': {
		GeneratorEnemy* enemy = new GeneratorEnemy(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		string key = getRoomFromUbication(x, y);
		rooms[key]->addEnemy(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'B': {
		Enemy* enemy = new Enemy(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		string key = getRoomFromUbication(x, y);
		rooms[key]->addEnemy(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'C': {
		Clotty* enemy = new Clotty(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		string key = getRoomFromUbication(x, y);
		rooms[key]->addEnemy(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'H': {
		Host* enemy = new Host(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		string key = getRoomFromUbication(x, y);
		rooms[key]->addEnemy(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case '1': {
		if (player == NULL) {
			player = new Player(x, y, game);
		}
		// modificación para empezar a contar desde el suelo.
		player->x = x;
		player->y = y - player->height / 2;
		space->addDynamicActor(player);
		string key = getRoomFromUbication(x, y);
		currentRoom = rooms[key];
		break;
	}
	case '#': {
		Tile* tile = new Tile("res/invisible.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'D': {
		int orient = 0;
		if (int(x) % WIDTH == 75) 
			orient = game->orientationLeft;
		if (int(x) % WIDTH == 875)
			orient = game->orientationRight;
		if (int(y) % HEIGHT == 0)
			orient = game->orientationDown;
		if (int(y) % HEIGHT == 50)
			orient = game->orientationUp;
		Door* door = new Door(orient, x, y, game);
		// modificación para empezar a contar desde el suelo.
		door->y = door->y - door->height / 2;
		doors.push_back(door);
		space->addDynamicActor(door);
		break;
	}
	case 'O': {
		int orient = 0;
		if (int(x) % WIDTH == 75)
			orient = game->orientationLeft;
		if (int(x) % WIDTH == 875)
			orient = game->orientationRight;
		if (int(y) % HEIGHT == 0)
			orient = game->orientationDown;
		if (int(y) % HEIGHT == 50)
			orient = game->orientationUp;
		Door* door = new Door(orient, x, y, game,1);
		// modificación para empezar a contar desde el suelo.
		door->y = door->y - door->height / 2;
		doors.push_back(door);
		space->addDynamicActor(door);
		break;
	}
	case 'S': {
		int orient = 0;
		if (int(x) % WIDTH == 75)
			orient = game->orientationLeft;
		if (int(x) % WIDTH == 875)
			orient = game->orientationRight;
		if (int(y) % HEIGHT == 0)
			orient = game->orientationDown;
		if (int(y) % HEIGHT == 50)
			orient = game->orientationUp;
		Door* door = new Door(orient, x, y, game, 2);
		// modificación para empezar a contar desde el suelo.
		door->y = door->y - door->height / 2;
		doors.push_back(door);
		space->addDynamicActor(door);
		break;
	}
	case '@': {
		Tile* tile = new Tile("res/roca"+ to_string(rand()%3)+".png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case '^': {
		Trap* enemy = new Trap(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		traps.push_back(enemy);
		break;
	}
	case 'R': {
		Room* room = new Room(game);
		string key = to_string(int(x)) + to_string(int(y));
		rooms.emplace(key, room);
		// modificación para empezar a contar desde el suelo.
		break;
	}
	case 'o': {
		int orient = 0;
		if (int(x) % WIDTH == 125)
			orient = game->orientationLeft;
		if (int(x) % WIDTH == 825)
			orient = game->orientationRight;
		if (int(y) % HEIGHT == 500)
			orient = game->orientationDown;
		if (int(y) % HEIGHT == 100)
			orient = game->orientationUp;
		Cerradura* tile = new Cerradura(orient, x, y, game, 1);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile->puertaCerradura);
		space->addStaticActor(tile->puertaCerradura);
		cerraduras.push_back(tile);
		break;
	}
	case 's': {
		int orient = 0;
		if (int(x) % WIDTH == 125)
			orient = game->orientationLeft;
		if (int(x) % WIDTH == 825)
			orient = game->orientationRight;
		if (int(y) % HEIGHT == 500)
			orient = game->orientationDown;
		if (int(y) % HEIGHT == 100)
			orient = game->orientationUp;
		Cerradura* tile = new Cerradura(orient, x, y, game, 2);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile->puertaCerradura);
		space->addStaticActor(tile->puertaCerradura);
		cerraduras.push_back(tile);
		break;
	}
	case '%': {
		string img;
		if (int(x) % WIDTH == 125)
			img = "res/puerta_izquierda_cerrada.png";
		if (int(x) % WIDTH == 825)
			img = "res/puerta_derecha_cerrada.png";
		if (int(y) % HEIGHT == 500)
			img = "res/puerta_abajo_cerrada.png";
		if (int(y) % HEIGHT == 100)
			img = "res/puerta_arriba_cerrada.png";
		Tile* tile = new Tile(img, x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		string key = getRoomFromUbication(x, y);
		rooms[key]->addPuertaCerrada(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'I': {
		Pickup* item = getItem();
		item->x = x;
		item->y = y - item->height / 2;
		pickups.push_back(item);
		break;
	}
	case 'A': {
		Pickup* item = getItem();
		item->x = x;
		item->y = y - item->height / 2;
		ArticuloEnVenta* heart = new ArticuloEnVenta(item, x, y, game);
		tienda.push_back(heart);
		break;
	}
	}
}

Pickup* GameLayer::getItem()
{
	if (items.size() == 0) {
		Lemon* lemon = new Lemon(game);
		Hourglass* hourglass = new Hourglass(game);
		Meat* meat = new Meat(game);
		Onion* onion = new Onion(game);
		Chocolate* chocolate = new Chocolate(game);
		Triple* triple = new Triple(game);
		Juice* juice = new Juice(game);

		if (rand()%2 == 0)
			items.push_back(lemon);
		else
			items.push_front(lemon);
		if (rand() % 2 == 0)
			items.push_back(hourglass);
		else
			items.push_front(hourglass);
		if (rand() % 2 == 0)
			items.push_back(meat);
		else
			items.push_front(meat);
		if (rand() % 2 == 0)
			items.push_back(onion);
		else
			items.push_front(onion);
		if (rand() % 2 == 0)
			items.push_back(chocolate);
		else
			items.push_front(chocolate);
		if (rand() % 2 == 0)
			items.push_back(triple);
		else
			items.push_front(triple);
		if (rand() % 2 == 0)
			items.push_back(juice);
		else
			items.push_front(juice);
	}

	Pickup* item = items.front();
	items.pop_front();
	return item;
}

string GameLayer::getRoomFromUbication(float x, float y)
{
	int salax = x / WIDTH;
	int salay = y / HEIGHT;
	string key = to_string((salax * WIDTH) + 125) + to_string((salay * HEIGHT) + 100);
	return key;
}


void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_CONTROLLERDEVICEADDED) {
			gamePad = SDL_GameControllerOpen(0);
			if (gamePad == NULL) {
				cout << "error en GamePad" << endl;
			}
			else {
				cout << "GamePad conectado" << endl;
			}
		}

		// Cambio automático de input
		// PONER el GamePad
		if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERAXISMOTION) {
			game->input = game->inputGamePad;
		}
		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}
		// Procesar teclas
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		}
		// Procesar Mando
		if (game->input == game->inputGamePad) {  // gamePAD
			gamePadToControls(event);
		}


	}
	//procesar controles
	//procesar controles
	// Disparar
	if (controlContinue) {
		pause = false;
		controlContinue = false;
	}
	if (controlShoot > 0) {
		list<Projectile*> newProjectiles = player->shoot(controlShoot);
		for (auto const& p : newProjectiles) {
			space->addDynamicActor(p);
			projectiles.push_back(p);
		}

	}
	else {
		player->shootDirection = 0;
	}

	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0) {
		player->moveY(1);
	}
	else if (controlMoveY < 0) {
		player->moveY(-1);
	}
	else {
		player->moveY(0);
	}



}

void GameLayer::update() {
	if (pause) {
		return;
	}

	if (roomChanched > 0 && paneoFrame == paneoTotalFrames) {
		paneoFrame = 0;
	}

	if (paneoFrame != paneoTotalFrames) {
		return;
	}

	// Nivel superado
	if (cup->isOverlap(player)) {
		game->currentLevel++;
		if (game->currentLevel > game->finalLevel) {
			game->currentLevel = 0;
		}
		init();
		return;
	}

	space->update();
	background->update();
	player->update();

	for (auto const& door : doors) {
		if (player->isOverlap(door)) {
			door->movePlayer();
			roomChanched = door->orientacion;
			currentRoom = rooms[getRoomFromUbication(player->x, player->y)];
		}
	}

	for (auto const& door : cerraduras) {
		if (player->isOverlap(door) && currentRoom->enemies.size() == 0 && door->cerrado) {
			if (player->keys > 0 ) {
				player->keys--;
				door->cerrado = false;
				keys_text->content = to_string(player->keys);
				space->removeStaticActor(door->puertaCerradura);
				tiles.remove(door->puertaCerradura);
			}
		}
	}
	currentRoom->update();
	for (auto const& projectile : projectiles) {
		projectile->update();
	}
	for (auto const& trap : traps) {
		trap->update();
	}
	for (auto const& projectile : enemyProjectiles) {
		projectile->update();
	}


	// Colisiones
	for (auto const& enemy : currentRoom->enemies) {
		if (player->isOverlap(enemy) && enemy->state != game->stateDying) {
			player->loseLife();
			if (player->lifes <= 0) {
				player = new Player(player->x, player->y, game);
				game->currentLevel = 0;
				init();
				return;
			}
		}
	}

	for (auto const& trap : traps) {
		if (player->isOverlap(trap) && trap->state != game->stateDying) {
			player->loseLife();
			if (player->lifes <= 0) {
				player = new Player(player->x, player->y, game);
				game->currentLevel = 0;
				init();
				return;
			}
		}
	}

	for (auto const& pickup : pickups) {
		pickup->update();
	}

	for (auto const& pickup : tienda) {
		pickup->update();
	}
	// Colisiones , Enemy - Projectile

	list<Enemy*> deleteEnemies;
	list<Projectile*> deleteProjectiles;
	list<Pickup*> deletePickups;
	list<ArticuloEnVenta*> deleteArticulo;
	list<Trap*> deleteTraps;

	for (auto const& projectile : enemyProjectiles) {
		if (player->isOverlap(projectile)) {
			player->loseLife();
			if (player->lifes <= 0) {
				player = new Player(player->x, player->y, game);
				game->currentLevel = 0;
				init();
				return;
			}

			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}
	}

	for (auto const& projectile : enemyProjectiles) {
		if (projectile->isInRender(scrollX, scrollY) == false ||
			abs(projectile->expectedVX - projectile->vx) > 1 ||
			abs(projectile->expectedVY - projectile->vy) > 1) {

			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}

		}
	}

	for (auto const& b : pickups) {
		if (player->isOverlap(b)) {
			b->giveBonus();
			bool bInList = std::find(deletePickups.begin(),
				deletePickups.end(),
				b) != deletePickups.end();

			if (!bInList) {
				deletePickups.push_back(b);
			}
		}
	}

	for (auto const& b : tienda) {
		if (player->isOverlap(b)) {
			b->giveBonus();
			if (b->vendido) {
				bool bInList = std::find(deleteArticulo.begin(),
					deleteArticulo.end(),
					b) != deleteArticulo.end();

				if (!bInList) {
					deleteArticulo.push_back(b);
				}
			}
		}
	}

	for (auto const& projectile : projectiles) {
		if (projectile->isInRender(scrollX, scrollY) == false || abs(projectile->expectedVX - projectile->vx) > 1 ||
			abs(projectile->expectedVY - projectile->vy) > 1) {

			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}
	}

	for (auto const& enemy : currentRoom->enemies) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}
				enemy->impacted(player->strength);
				for (auto const& effect : projectile->effects) {
					effect->applyEffect(enemy);
				}
			}
		}
	}

	for (auto const& enemy : currentRoom->enemies) {
		if (enemy->state == game->stateDead) {
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();

			if (!eInList) {
				deleteEnemies.push_back(enemy);
			}
		}
	}

	for (auto const& trap : traps) {
		if (trap->state == game->stateDead) {
			bool eInList = std::find(deleteTraps.begin(),
				deleteTraps.end(),
				trap) != deleteTraps.end();

			if (!eInList) {
				deleteTraps.push_back(trap);
			}
		}
	}

	for (auto const& delEnemy : deleteEnemies) {
		currentRoom->removeEnemy(delEnemy);
		if (currentRoom->enemies.size() == 0) {
			for (auto const& tile : currentRoom->puertasCerradas) {
				space->removeStaticActor(tile);
			}
			currentRoom->puertasCerradas.clear();
			int itemroulette = rand() % 10;
			if (itemroulette < 6) {
				if (itemroulette == 0) {
					pickups.push_back(new Key(WIDTH / 2 + scrollX, HEIGHT / 2 + scrollY, game));
				} else if (itemroulette == 1) {
					pickups.push_back(new Heart(WIDTH / 2 + scrollX, HEIGHT / 2 + scrollY, game));
				}
				else {
					pickups.push_back(new Coin(WIDTH / 2 + scrollX, HEIGHT / 2 + scrollY, game));
				}
					
			}
		}
		space->removeDynamicActor(delEnemy);
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		enemyProjectiles.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
		delete delProjectile;
	}
	deleteProjectiles.clear();

	for (auto const& delTrap : deleteTraps) {
		traps.remove(delTrap);
	}

	deleteTraps.clear();

	for (auto const& delPickup : deletePickups) {
		pickups.remove(delPickup);
	}

	deletePickups.clear();

	for (auto const& delPickup : deleteArticulo) {
		tienda.remove(delPickup);
	}

	deleteArticulo.clear();

	cout << "update GameLayer" << endl;
}

void GameLayer::calculateScroll(bool paneo) {
	int roomX = player->x / WIDTH;
	int roomY = player->y / HEIGHT;

	scrollX = roomX * WIDTH;
	scrollY = roomY * HEIGHT;

	if (!paneo)
		return;

	int paneoX = 0;
	int paneoY = 0;
	paneoFrame++;
	if (roomChanched == game->orientationRight) {
		paneoX = WIDTH * paneoFrame / paneoTotalFrames;
		scrollX -= WIDTH - paneoX;
	}
	if (roomChanched == game->orientationLeft) {
		paneoX = WIDTH * paneoFrame / paneoTotalFrames;
		scrollX += WIDTH - paneoX;
	}
	if (roomChanched == game->orientationUp) {
		paneoY = HEIGHT * paneoFrame / paneoTotalFrames;
		scrollY += HEIGHT - paneoY;
	}
	if (roomChanched == game->orientationDown) {
		paneoY = HEIGHT * paneoFrame / paneoTotalFrames;
		scrollY -= HEIGHT - paneoY;
	}

	if (paneoFrame == paneoTotalFrames) {
		roomChanched = -1;
	}
}


void GameLayer::draw() {
 	if (paneoFrame != paneoTotalFrames) {
		calculateScroll();
	}

	background->draw(scrollX, scrollY);
	for (auto const& trap : traps) {
		trap->draw(scrollX, scrollY);
	}
	for (auto const& tile : doors) {
		tile->draw(scrollX, scrollY);
	}
	for (auto const& tile : tiles) {
		tile->draw(scrollX, scrollY);
	}
	for (auto const& pickup : pickups) {
		pickup->draw(scrollX, scrollY);
	}
	for (auto const& pickup : tienda) {
		pickup->draw(scrollX, scrollY);
	}
	for (auto const& projectile : projectiles) {
		projectile->draw(scrollX, scrollY);
	}
	for (auto const& projectile : enemyProjectiles) {
		projectile->draw(scrollX, scrollY);
	}
	cup->draw(scrollX, scrollY);
	currentRoom->draw(scrollX, scrollY);
	player->draw(scrollX, scrollY);

	// HUD
	for (int i = 0; i < player->maxLifes/2; i++) {
		contenedores_vida[i]->draw();
	}
	for (int i = 0; i < player->lifes/2; i++) {
		vidas[i]->draw();
	}
	if (player->lifes % 2 != 0) {
		mediaVida->x = WIDTH * 0.05;
		mediaVida->y = HEIGHT * 0.05;
		mediaVida = new Actor("res/hud_media_vida.png",
			WIDTH * 0.05, HEIGHT * 0.05, 26, 24, game);
		mediaVida->x += 24 * (player->lifes / 2);
		if (player->lifes > 12) {
			mediaVida->x -= 144;
			mediaVida->y += 20;
		}
		mediaVida->draw();
	}

	money_text->draw();
	keys_text->draw();
	money_hud->draw();
	keys_hud->draw();
	if (pause) {
		message->draw();
	}

	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::gamePadToControls(SDL_Event event) {

	// Leer los botones
	bool buttonA = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A);
	bool buttonB = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_B);
	bool buttonX = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_X);
	bool buttonY = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_Y);
	// SDL_CONTROLLER_BUTTON_A, SDL_CONTROLLER_BUTTON_B
	// SDL_CONTROLLER_BUTTON_X, SDL_CONTROLLER_BUTTON_Y
	cout << "botones:" << buttonA << "," << buttonB << endl;
	int stickX = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTX);
	cout << "stickX" << stickX << endl;
	int stickY = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTY);
	// Retorna aproximadamente entre [-32800, 32800], el centro debería estar en 0
	// Si el mando tiene "holgura" el centro varia [-4000 , 4000]
	if (stickX > 4000) {
		controlMoveX = 1;
	}
	else if (stickX < -4000) {
		controlMoveX = -1;
	}
	else {
		controlMoveX = 0;
	}

	if (stickY > 4000) {
		controlMoveY = 1;
	}
	else if (stickY < -4000) {
		controlMoveY = -1;
	}
	else {
		controlMoveY = 0;
	}

	if (buttonA) {
		controlShoot = game->orientationRight;
		controlContinue = true;
	}
	else {
		if (buttonB) {
			controlShoot = game->orientationDown;
		}
		else {
			if (buttonX) {
				controlShoot = game->orientationUp;
			}
			else {
				if (buttonY) {
					controlShoot = game->orientationLeft;
				}
				else {
					controlShoot = 0;
				}
			}
		}
	}
	
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_UP: // dispara
			controlShoot = game->orientationUp;
			break;
		case SDLK_DOWN: // dispara
			controlShoot = game->orientationDown;
			break;
		case SDLK_RIGHT: // dispara
			controlShoot = game->orientationRight;
			break;
		case SDLK_LEFT: // dispara
			controlShoot = game->orientationLeft;
			break;
		case SDLK_SPACE:
			controlContinue = true;
			break;
		}


	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_UP: // dispara
			if (controlShoot == game->orientationUp) {
				controlShoot = 0;
			}
			break;
		case SDLK_DOWN: // dispara
			if (controlShoot == game->orientationDown) {
				controlShoot = 0;
			}
			break;
		case SDLK_RIGHT: // dispara
			if (controlShoot = game->orientationRight) {
				controlShoot = 0;
			}
			break;
		case SDLK_LEFT: // dispara
			if (controlShoot = game->orientationLeft) {
				controlShoot = 0;
			}
			break;
		case SDLK_SPACE: 
			controlContinue = false;
			break;
		}

	}

}

