#pragma once
#include "GunmanEnemy.h"
class Clotty : public Enemy
{
public:
    Clotty(float x, float y, Game* game);
    void actions() override;
    void shoot();
    void changeDirection();

    int shootCadence;
    int shootTime;
    int movementRate;
    int movementTime;
};

