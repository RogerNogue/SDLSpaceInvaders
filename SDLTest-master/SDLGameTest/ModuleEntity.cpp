#include "ModuleEntity.h"
#include "Application.h"

//sdl includes
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <SDL.h>
#include <SDL_image.h>
#elif defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif


/////////////////////Class entity/////////////////////
Entity::Entity(bool isPlayer):
	isPlayer(isPlayer)
{
	entityRect = new SDL_Rect();
	SetRect(0, 0, 0, 0);
}

Entity::Entity(int x, int y, int w, int h, bool isPlayer) :
	isPlayer(isPlayer)
{
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
	int playerY = SCREEN_HEIGHT - PLAYER_DIMENSIONS/2;
	gameEntities[0] = new Entity(
		playerX, playerY, PLAYER_DIMENSIONS, PLAYER_DIMENSIONS, true);

	//then all the enemies
	for (int i = 1; i < NUM_ENEMIES+1; ++i)
	{
		//TODO(Roger): tune those values and remove magic number
		gameEntities[i] = new Entity(
			i, 50, ENEMY_DIMENSIONS, ENEMY_DIMENSIONS, false);
	}
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

//treats input and updates player and enemies
update_status ModuleEntity::Update()
{
	return UPDATE_CONTINUE;
}