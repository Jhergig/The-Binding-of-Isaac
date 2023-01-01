#include "ProjectileFactory.h"

ProjectileFactory::ProjectileFactory()
{
	pf = NULL;
}

void ProjectileFactory::add(ProjectileFactory* pf2)
{
	if (pf == NULL)
		pf = pf2;
	else
		pf->add(pf2);
}

list<Projectile*> ProjectileFactory::shoot(int direction, float x, float y, Game* game)
{
	list<Projectile*> projectiles;
	if (pf == NULL) {
		Projectile* p = new Projectile(x, y, game);
		if (direction == game->orientationRight)
			p->vx = 6;
		if (direction == game->orientationLeft)
			p->vx = -6;
		if (direction == game->orientationUp)
			p->vy = -6;
		if (direction == game->orientationDown)
			p->vy = 6;

		p->setExpectedValues();
		projectiles.push_back(p);
	}
	else {
		projectiles = pf->shoot(direction, x, y , game);
	}
	list<Projectile*> newProjectiles;
	for (Projectile* p : projectiles) 
		for (Projectile* newp : addEffect(p, direction))
			newProjectiles.push_back(newp);
	return newProjectiles;
}

list<Projectile*> ProjectileFactory::addEffect(Projectile* p, int direction)
{
	list<Projectile*> projectile;
	projectile.push_back(p);
	return projectile;
}
