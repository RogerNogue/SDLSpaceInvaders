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

	//checking all projectiles
	//since we want to remove elems, lets use old school loop
	std::list<Projectile*>::iterator it = listProjectiles.begin();
	
	bool projectileDeleted = false;
	while (it != listProjectiles.end())
	{
		projectileDeleted = false;
		//delete if it got outside of the screen
		if ((*it)->projectileRect->y < 0)
		{
			it = listProjectiles.erase(it);
			projectileDeleted = true;
		}
		else
		{
			auto entityVector = &App->entity->gameEntities;
			//lets check collisions
			//first we check player and proj not being from the player
			SDL_Rect collisionRect;
			if (!(*it)->IsFromPlayer() &&
				SDL_IntersectRect(
				(*it)->projectileRect, (*entityVector)[0]->entityRect, &collisionRect)
				== SDL_TRUE)
			{
				//get rid of projectile
				it = listProjectiles.erase(it);
				projectileDeleted = true;
				//lower health
				--(*entityVector)[0]->health;
				if ((*entityVector)[0]->health <= 0)
				{
					//TODO(Roger):endGame
				}

			}
			//if not, check obstacles and enemies
			else 
			{
				//obstacles
				auto obstacleVector = &App->entity->obstacles;
				for (int i = 0; i < (*obstacleVector).size() && !projectileDeleted; ++i)
				{
					if (SDL_IntersectRect(
						(*it)->projectileRect, (*obstacleVector)[i]->entityRect, &collisionRect)
						== SDL_TRUE)
					{
						//get rid of projectile
						it = listProjectiles.erase(it);
						projectileDeleted = true;
						//lower health
						--(*obstacleVector)[i]->health;
						if ((*obstacleVector)[i]->health <= 0)
						{
							(*obstacleVector).erase((*obstacleVector).begin() + i);

						}
					}
				}
				//enemies
				for (int i = 1; i < (*entityVector).size() && !projectileDeleted; ++i)
				{
					//if collided, we delete it and lower health of impacted
					if (SDL_IntersectRect(
						(*it)->projectileRect, (*entityVector)[i]->entityRect, &collisionRect)
						== SDL_TRUE)
					{
						//get rid of projectile
						it = listProjectiles.erase(it);
						projectileDeleted = true;
						//lower health
						--(*entityVector)[i]->health;
						if ((*entityVector)[i]->health <= 0)
						{
							App->entity->EnemyKilled((*entityVector)[i]);
							//erase the i-th element. Destructor is called
							(*entityVector).erase((*entityVector).begin() + (i));
						}

					}
					
				}
			}
		}
		//if nothing erased, advance iterator
		if(!projectileDeleted)
		{
			++it;
		}
	}
	return UPDATE_CONTINUE;
}

bool ModuleCollisions::CleanUp() 
{
	//clean projectile list
	for (auto proj : listProjectiles)
	{
		SAFE_RELEASE(proj);
	}
	listProjectiles.clear();
	return true;
}