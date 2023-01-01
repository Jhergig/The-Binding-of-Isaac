#include "Effect.h"

void Effect::applyEffect(Enemy* enemy)
{
	enemy->maxSpeed -= 2;
	if (enemy->maxSpeed < 1)
		enemy->maxSpeed = 1;
}
