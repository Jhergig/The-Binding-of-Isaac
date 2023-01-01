#pragma once
#include "Enemy.h"
class GunmanEnemy :
    public Enemy
{
public:
    GunmanEnemy(float x, float y, Game* game);
    void actions() override;
    void shoot();
    int shootCadence;
    int shootTime;
};

