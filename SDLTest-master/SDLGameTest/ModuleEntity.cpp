#include "ModuleEntity.h"
#include "Application.h"

#include "ModuleInput.h"

//sdl includes
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <SDL.h>
#include <SDL_image.h>
#elif defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif


/////////////////////Class entity/////////////////////
Entity::Entity(bool isPlayer) :
	isPlayer(isPlayer)
{
	if (isPlayer)
	{
		health = PLAYER_HEALTHPOINTS;
	}
	else
	{
		health = ENEMY_HEALTHPOINTS;
	}
	entityRect = new SDL_Rect();
	SetRect(0, 0, 0, 0);
}

Entity::Entity(int x, int y, int w, int h, bool isPlayer) :
	isPlayer(isPlayer)
{
	if (isPlayer)
	{
		health = PLAYER_HEALTHPOINTS;
	}
	else
	{
		health = ENEMY_HEALTHPOINTS;
	}
	entityRect = new SDL_Rect();
	SetRect(x, y, w, h);
}

Entity::~Entity()
{
	delete entityRect;
}

inline void Entity::SetRect(int x, int y, int w, int h)
{
	entityRect->x = x;
	entityRect->y = y;
	entityRect->w = w;
	entityRect->h = h;
}

/////////////////////Class projectile/////////////////////
Projectile::Projectile(bool fromPlayer) :
	fromPlayer(fromPlayer)
{
	projectileRect = new SDL_Rect();
	SetRect(0, 0, 0, 0);
}

Projectile::Projectile(int x, int y, int w, int h, bool fromPlayer) :
	fromPlayer(fromPlayer)
{
	projectileRect = new SDL_Rect();
	SetRect(x, y, w, h);
}

Projectile::~Projectile()
{
	delete projectileRect;
}

inline void Projectile::SetRect(int x, int y, int w, int h)
{
	projectileRect->x = x;
	projectileRect->y = y;
	projectileRect->w = w;
	projectileRect->h = h;
}

/////////////////////Module entity/////////////////////


ModuleEntity::ModuleEntity()
{

}

ModuleEntity::~ModuleEntity()
{

}

bool ModuleEntity::Init()
{
	//creates and initializes all the entities
	//we create the player first
	int playerX = SCREEN_WIDTH/2;
	int playerY = SCREEN_HEIGHT - PLAYER_DIMENSIONS;
	gameEntities[0] = new Entity(
		playerX, playerY, PLAYER_DIMENSIONS, PLAYER_DIMENSIONS, true);

	//then all the enemies
	int enemyY = STARTING_ENEMIES_Y;
	int enemiesAtCurrentRow = 0;
	for (int i = 1; i < NUM_ENEMIES+1; ++i)
	{
		int enemyX = STARTING_ENEMIES_X + ((i - 1) % ENEMIES_PER_ROW) * X_SEPARATION_BETWEEN_ENEMIES;
		
		if (enemiesAtCurrentRow >= ENEMIES_PER_ROW)
		{
			enemyY += Y_SEPARATION_BETWEEN_ENEMIES;
			enemiesAtCurrentRow = 0;
		}
		
		gameEntities[i] = new Entity(
			enemyX, enemyY, ENEMY_DIMENSIONS, ENEMY_DIMENSIONS, false);
		++enemiesAtCurrentRow;
	}
	mostLeftEnemy = gameEntities[1];
	mostRightEnemy = gameEntities[ENEMIES_PER_ROW];
	return true;
}

bool ModuleEntity::CleanUp()
{
	//frees entities
	for (auto entity : gameEntities)
	{
		if (entity != nullptr)
		{
			delete entity;
		}
	}
	return true;
}

void ModuleEntity::MoveEnemies(int x, int y)
{
	for (int i = 1; i < gameEntities.size(); ++i)
	{
		gameEntities[i]->entityRect->x += x;
		gameEntities[i]->entityRect->y += y;
	}
}

//treats input and updates player and enemies
update_status ModuleEntity::Update()
{
	//player movement update
	if (App->input->keyboardState.Left == KEY_DOWN && 
		gameEntities[0]->entityRect->x > LEFT_BORDER_POSITION)
	{
		gameEntities[0]->entityRect->x -= PLAYER_SPEED;
	}
	if (App->input->keyboardState.Right == KEY_DOWN &&
		(gameEntities[0]->entityRect->x + PLAYER_DIMENSIONS) < RIGHT_BORDER_POSITION)
	{
		gameEntities[0]->entityRect->x += PLAYER_SPEED;
	}

	//enemies movement update
	//TODO(Roger): end the game if an enemy gets to the end of the screen
	switch (enemState)
	{
	case MOVING_RIGHT:
		//check if we got to right corner
		if ((mostRightEnemy->entityRect->x + ENEMY_DIMENSIONS) > RIGHT_BORDER_POSITION)
		{
			enemState = MOVING_DOWN;
			MoveEnemies(0, ENEMY_SPEED);
			++stepsDown;
		}
		else
		{
			MoveEnemies(direction*ENEMY_SPEED, 0);
		}
		break;
	case MOVING_LEFT:
		//check if we got to left corner
		if ((mostLeftEnemy->entityRect->x) < LEFT_BORDER_POSITION)
		{
			enemState = MOVING_DOWN;
			MoveEnemies(0, ENEMY_SPEED);
			++stepsDown;
		}
		else
		{
			MoveEnemies(direction * ENEMY_SPEED, 0);
		}
		break;
	case MOVING_DOWN:
		//check if we got down the specified distance
		if (stepsDown == ENEMY_DOWN_STEPS)
		{
			if (direction == 1)
			{
				enemState = MOVING_LEFT;
			}
			else
			{
				enemState = MOVING_RIGHT;
			}
			stepsDown = 0;
			direction *= -1;
			MoveEnemies(direction * ENEMY_SPEED, 0);
		}
		else
		{
			MoveEnemies(0, ENEMY_SPEED);
			++stepsDown;
		}
		break;
	}
	return UPDATE_CONTINUE;
}

void ModuleEntity::EnemyKilled(Entity* deadEnemy)
{
	//check if we have to re calculate a boundary index
	if (deadEnemy == mostLeftEnemy)
	{
		//check that the first one is not the one we killed
		if (gameEntities[1] == deadEnemy)
		{
			mostLeftEnemy = gameEntities[2];
		}
		else
		{
			mostLeftEnemy = gameEntities[1];
		}
		
		//old school stuff
		for(int i = 1; i < gameEntities.size(); ++i)
		{
			//skip iteration if its the dead enemy
			if (gameEntities[i] == deadEnemy)
			{
				continue;
			}
			if (gameEntities[i]->entityRect->x < mostLeftEnemy->entityRect->x)
			{
				mostLeftEnemy = gameEntities[i];
			}
		}
	}
	else if (deadEnemy == mostRightEnemy)
	{
		//check that the first one is not the one we killed
		if (gameEntities[1] == deadEnemy)
		{
			mostRightEnemy = gameEntities[2];
		}
		else
		{
			mostRightEnemy = gameEntities[1];
		}
		//old school stuff
		for (int i = 1; i < gameEntities.size(); ++i)
		{
			//skip iteration if its the dead enemy
			if (gameEntities[i] == deadEnemy)
			{
				continue;
			}
			if (gameEntities[i]->entityRect->x > mostRightEnemy->entityRect->x)
			{
				mostRightEnemy = gameEntities[i];
			}
		}
	}

}