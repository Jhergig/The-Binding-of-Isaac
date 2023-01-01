#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 30, 30, game) {

	this->fileWidth = 56;
	this->fileHeight = 66;

	orientation = game->orientationDown;
	shootDirection = orientation;
	pf = new ProjectileFactory();

	state = game->stateMoving;

	audioShoot1 = new Audio("res/disparo_1.wav", false);
	audioShoot2 = new Audio("res/disparo_2.wav", false);

	aHeadRight = new Animation("res/headRight.png",
		56, 50, 56, 50, 1, 1, true, game);
	aHeadLeft = new Animation("res/headLeft.png",
		56, 50, 56, 50, 1, 1, true, game);
	aHeadUp = new Animation("res/headUp.png",
		56, 50, 56, 50, 1, 1, true, game);
	aHeadDown = new Animation("res/headDown.png",
		56, 50, 56, 50, 1, 1, true, game);
	aShootRight = new Animation("res/shootRight.png",
		56, 52, 112, 52, 6, 2, false, game);
	aShootLeft = new Animation("res/shootLeft.png",
		56, 52, 112, 52, 6, 2, false, game);
	aShootUp = new Animation("res/shootUp.png",
		56, 52, 112, 52, 6, 2, false, game);
	aShootDown = new Animation("res/shootDown.png",
		56, 52, 112, 52, 6, 2, false, game);
	aBodyDown = new Animation("res/bodyDown.png",
		36, 26, 36, 26, 1, 1, true, game);
	aMoveRight = new Animation("res/moveRight.png",
		36, 30, 360, 28, 4, 10, true, game);
	aMoveLeft = new Animation("res/moveLeft.png",
		36, 30, 360, 28, 4, 10, true, game);
	aMoveUp = new Animation("res/moveUp.png",
		36, 30, 360, 30, 4, 10, true, game);
	aMoveDown = new Animation("res/moveDown.png",
		36, 30, 360, 30, 4, 10, true, game);

	headAnimation = aHeadDown;
	bodyAnimation = aBodyDown;
}


void Player::update() {

	if (invulnerableTime > 0) {
		invulnerableTime--;
	}

	bool endAnimation = headAnimation->update();
	bodyAnimation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba disparando
		if (state == game->stateShooting) {
			state = game->stateMoving;
		}
	}

	// Establecer orientación y animación del cuerpo
	if (vx < 0) {
		bodyAnimation = aMoveLeft;
		orientation = game->orientationLeft;
	}
	if (vx > 0) {
		bodyAnimation = aMoveRight;
		orientation = game->orientationRight;
	}
	if (vy < 0) {
		bodyAnimation = aMoveUp;
		orientation = game->orientationUp;
	}
	if (vy > 0) {
		bodyAnimation = aMoveDown;
		orientation = game->orientationDown;
	}
	if (vx == 0 && vy == 0) {
		bodyAnimation = aBodyDown;
		orientation = game->orientationDown;
	}

	// Selección de animación basada en estados
	if (state == game->stateShooting) {
		if (shootDirection == game->orientationRight) {
			headAnimation = aShootRight;;
		}
		if (shootDirection == game->orientationLeft) {
			headAnimation = aShootLeft;
		}
		if (shootDirection == game->orientationUp) {
			headAnimation = aShootUp;
		}
		if (shootDirection == game->orientationDown) {
			headAnimation = aShootDown;
		}
	} else
	if (shootDirection > 0 && state == game->stateMoving) {
		if (shootDirection == game->orientationRight) {
			headAnimation = aHeadRight;;
		}
		if (shootDirection == game->orientationLeft) {
			headAnimation = aHeadLeft;
		}
		if (shootDirection == game->orientationUp) {
			headAnimation = aHeadUp;
		}
		if (shootDirection == game->orientationDown) {
			headAnimation = aHeadDown;
		}
	}

	else {
		if (orientation == game->orientationRight) {
			headAnimation = aHeadRight;
		}
		if (orientation == game->orientationLeft) {
			headAnimation = aHeadLeft;
		}
		if (orientation == game->orientationUp) {
			headAnimation = aHeadUp;
		}
		if (orientation == game->orientationDown) {
 			headAnimation = aHeadDown;
		}
	}

	if (shootTime > 0) {
		shootTime--;
	}

}

void Player::moveX(float axis) {
	vx += axis;
	if (axis == 0 && vx > 0)
		vx--;
	if (axis == 0 && vx < 0)
		vx++;
	if (abs(vx) > speed) {
		vx = axis * speed;
		if (vy != 0)
			vx *= 0.7; // Menos velocidad x al moverse en diagonal
	}
}

void Player::moveY(float axis) {
	vy += axis;
	if (axis == 0 && vy > 0)
		vy--;
	if (axis == 0 && vy < 0)
		vy++;
	if (abs(vy) > speed) {
		vy = axis * speed;
		if (vx != 0)
			vy *= 0.7; // Menos velocidad y al moverse en diagonal
	}
}

list<Projectile*> Player::shoot(int shootDirection) {

	list<Projectile*> projectiles;

	if (shootTime == 0) {
		state = game->stateShooting;
		if (rand() % 2 == 0) {
			audioShoot1->play();
		}
		else {
			audioShoot2->play();
		}
		shootTime = shootCadence;
		this->shootDirection = shootDirection;
		projectiles = pf->shoot(shootDirection, x, y, game);
		if (shootDirection == game->orientationRight) {
			aShootRight->currentFrame = 0; //"Rebobinar" aniamción
		}
		if (shootDirection == game->orientationLeft) {
			aShootLeft->currentFrame = 0; //"Rebobinar" aniamción
		}
		if (shootDirection == game->orientationUp) {
			aShootUp->currentFrame = 0; //"Rebobinar" aniamción
		}
		if (shootDirection == game->orientationDown) {
			aShootDown->currentFrame = 0; //"Rebobinar" aniamción
		}
		return projectiles;
	}
	else {
		return projectiles;
	}
}

void Player::draw(float scrollX, float scrollY) {

	
	if (invulnerableTime == 0) {
		bodyAnimation->draw(x - scrollX, y - scrollY);
		headAnimation->draw(x - scrollX, y - 28 - scrollY);
	}
	else {
		if (invulnerableTime % 10 >= 0 && invulnerableTime % 10 <= 5) {
			bodyAnimation->draw(x - scrollX, y - scrollY);
			headAnimation->draw(x - scrollX, y - 28 - scrollY);
		}
	}
}

void Player::loseLife() {
	if (invulnerableTime <= 0) {
		if (lifes > 0) {
			lifes--;
			invulnerableTime = 100;
			// 100 actualizaciones 
		}
	}
}
