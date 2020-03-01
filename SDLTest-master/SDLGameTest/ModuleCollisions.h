#ifndef _MODULECOLLISIONS_
#define	_MODULECOLLISIONS_

#include "Module.h"
#include "Globals.h"
#include <list>

//fwd declarations
class Projectile;

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

public:
	//since elements will be deleted frequently, list is better than vector
	std::list<Projectile*> listProjectiles;

	unsigned timeLastProjectile = PLAYER_FIRE_TIME;
};

#endif // !_MODULECOLLISIONS_