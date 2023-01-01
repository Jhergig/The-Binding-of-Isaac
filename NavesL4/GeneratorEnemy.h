#pragma once
#include "Enemy.h"
class GeneratorEnemy :
    public Enemy
{
public:
	GeneratorEnemy(float x, float y, Game* game);
	void actions() override;
	void spawnEnemy();
	int generationCadence;
	int generationTime;
};

