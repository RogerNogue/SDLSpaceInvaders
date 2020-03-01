#ifndef _MODULEPLAYER_
#define _MODULEPLAYER_


#include "Module.h"
#include <vector>

//fwd declarations

class SDL_Rect;

enum enemiesState
{
	MOVING_RIGHT,
	MOVING_DOWN,
	MOVING_LEFT
};

//decided to have both enemies and player in the same class since adding an extra
//hierarchy adds more complexity than necessary
class Entity final
{
public:
	Entity(bool isPlayer);
	Entity(int x, int y, int w, int h, bool isPlayer);

	~Entity();

	inline void SetRect(int x, int y, int w, int h);

	inline bool IsPlayer() const { return isPlayer; }

public:
	SDL_Rect* entityRect = nullptr;
	int health = ENEMY_HEALTHPOINTS;

private:
	bool isPlayer;
};

//decided to have both enemies and player in the same class since adding an extra
//hierarchy adds more complexity than necessary
class Projectile final
{
public:
	Projectile(bool fromPlayer);
	Projectile(int x, int y, int w, int h, bool fromPlayer);

	~Projectile();

	inline void SetRect(int x, int y, int w, int h);

	inline bool IsFromPlayer() const { return fromPlayer; }

public:
	SDL_Rect* projectileRect = nullptr;

private:
	bool fromPlayer;
};

class ModuleEntity final:
	public Module
{
public:
	ModuleEntity();

	~ModuleEntity();

	bool Init() override;

	bool CleanUp() override;

	void MoveEnemies(int x, int y);

	update_status Update() override;

	//method that re calculates enemy boundaries when one died
	void EnemyKilled(Entity* deadEnemy);

public:
	//first position is for the player
	std::vector<Entity*> gameEntities =
		std::vector<Entity*>(NUM_ENEMIES + 1);

	//variables that keeps track of the most right and left side enemies
	Entity* mostRightEnemy = nullptr;
	Entity* mostLeftEnemy = nullptr;

	//var that tells us which direction enemies are going
	int direction = 1;

	//variable that keeps track of the distance enemies travel when going down
	//before switching directions
	int stepsDown = 0;

	enemiesState enemState = MOVING_RIGHT;
	
};

#endif // !_MODULEPLAYER_