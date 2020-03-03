#ifndef _MODULECOLLISIONS_
#define	_MODULECOLLISIONS_

#include "Module.h"
#include "Globals.h"
#include <list>

//fwd declarations
class Projectile;
class SDL_Rect;

//class that will handle the projectiles and their collisions/screen presence
class ModuleCollisions final:
	public Module
{
public:
	ModuleCollisions();

	~ModuleCollisions();

	bool Init() override;

	update_status Update() override;

	bool CleanUp() override;

	//method that tells us where is the enemy that fired
	void EnemyFire(const SDL_Rect* enemyRect);


public:
	//since elements will be deleted frequently, list is better than vector
	std::list<Projectile*> listProjectiles;

	unsigned timeLastProjectile = PLAYER_FIRE_TIME;
};

#endif // !_MODULECOLLISIONS_