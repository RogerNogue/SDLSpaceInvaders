#include "ModuleCollisions.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleEntity.h"

//sdl includes
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <SDL.h>
#include <SDL_image.h>
#elif defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif

ModuleCollisions::ModuleCollisions() :Module()
{

}

ModuleCollisions::~ModuleCollisions()
{

}

bool ModuleCollisions::Init()
{
	return true;
}

update_status ModuleCollisions::Update()
{
	//update all projectiles moving them upwards
	for (auto proj : listProjectiles)
	{
		proj->projectileRect->y -= PROJECTILE_SPEED;
	}
	//player firing projectile
	if (App->input->keyboardState.Fire == KEY_DOWN &&
		timeLastProjectile >= PLAYER_FIRE_TIME)
	{
		//we fire, projectiles are cleaned at cleanup function
		//or when they hit/leave screen
		int playerX = App->entity->gameEntities[0]->entityRect->x +
			(PLAYER_DIMENSIONS/2 - PROJECTILE_DIMENSIONS/2);
		int playerY = App->entity->gameEntities[0]->entityRect->y;
		listProjectiles.push_back(new Projectile(playerX, playerY,
			PROJECTILE_DIMENSIONS, PROJECTILE_DIMENSIONS, true));

		timeLastProjectile = 0;
	}
	++timeLastProjectile;

	return UPDATE_CONTINUE;
}

bool ModuleCollisions::CleanUp() 
{
	//clean projectile list
	for (auto proj : listProjectiles)
	{
		delete proj;
	}
	listProjectiles.clear();
	return true;
}