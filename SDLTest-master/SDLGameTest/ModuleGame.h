#ifndef _MODULEPLAYER_
#define _MODULEPLAYER_

#include "Module.h"
#include <vector>
#include <list>
#include "Globals.h"

//fwd declarations

class SDL_Rect;
class MenuText;

enum enemiesState
{
	MOVING_RIGHT,
	MOVING_DOWN,
	MOVING_LEFT
};

//decided to have enemies, player and obstacles in the same class since adding an extra
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
	Entity* enemyOnTop = nullptr;
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

class ModuleGame final:
	public Module
{
public:
	ModuleGame();

	~ModuleGame();

	bool NewGameInit();
	bool Init() override;

	bool CleanUp() override;

	void MoveEnemies(int x, int y);

	update_status Update() override;

	//method that re calculates enemy boundaries when one died
	void EnemyKilled(Entity* deadEnemy);

	void EnterMenu();

	void LeaveMenu();

	inline void IncreaseEnemiesSpeed() { enemySpeed += SPEED_INCREASE_PER_EVENT; }

public:
	//first position is for the player
	std::vector<Entity*> gameEntities =
		std::vector<Entity*>(NUM_ENEMIES + 1);

	//vector of the obstacles in the game
	std::vector<Entity*> obstacles =
		std::vector<Entity*>(NUM_OBSTACLES);

	//list of lowest placed enemies that will shoot
	std::list<Entity*> lowestEnemies;

	//variables that keeps track of the most right and left side enemies
	Entity* mostRightEnemy = nullptr;
	Entity* mostLeftEnemy = nullptr;

	//var that tells us which direction enemies are going
	int direction = 1;

	//variable that keeps track of the distance enemies travel when going down
	//before switching directions
	int stepsDown = 0;

	enemiesState enemState = MOVING_RIGHT;

	MenuText* currentScoreText;
	MenuText* currentScoreValue;

private://variables
	//we need it float because it escalates so much otherwise
	float enemySpeed = 0;
	
};

#endif // !_MODULEPLAYER_