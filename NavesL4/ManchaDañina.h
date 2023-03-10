#pragma once
#include "Trap.h"
#include "Animation.h"

class ManchaDaņina : public Trap
{
public:
    ManchaDaņina(float x, float y, Game* game);
    void update() override;
    void draw(float scrollX = 0, float scrollY = 0) override;
    int vidaTime;
    Animation* aDying;
    Animation* aMoving;
    Animation* animation;
};

