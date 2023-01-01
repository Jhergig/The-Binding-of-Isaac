#pragma once
#include "Enemy.h"
#include "ManchaDaņina.h"

class Host :
    public Enemy
{
public:
	Host(float x, float y, Game* game);
	void actions() override;
	void spawnMancha();
	int generationCadence;
	int generationTime;
};

