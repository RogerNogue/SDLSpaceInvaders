#include "ModuleGame.h"
#include "Application.h"

#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModuleGameLoop.h"

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
	SAFE_RELEASE(entityRect);
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
	SAFE_RELEASE(projectileRect);
}

inline void Projectile::SetRect(int x, int y, int w, int h)
{
	projectileRect->x = x;
	projectileRect->y = y;
	projectileRect->w = w;
	projectileRect->h = h;
}

/////////////////////Module game/////////////////////


ModuleGame::ModuleGame()
{

}

ModuleGame::~ModuleGame()
{

}

bool ModuleGame::NewGameInit()
{
	gameEntities = std::vector<Entity*>(NUM_ENEMIES + 1);
	obstacles = std::vector<Entity*>(NUM_OBSTACLES);
	return Init();
}

bool ModuleGame::Init()
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

		//if lowest, we add to losestEnemies
		if (i > NUM_ENEMIES - ENEMIES_PER_ROW)
		{
			lowestEnemies.push_back(gameEntities[i]);
		}
		//if enemy not highest, we fill their pointer to their enemy on top
		if (i > ENEMIES_PER_ROW+1)
		{
			gameEntities[i]->enemyOnTop = gameEntities[i - ENEMIES_PER_ROW];
		}

		++enemiesAtCurrentRow;
	}
	mostLeftEnemy = gameEntities[1];
	mostRightEnemy = gameEntities[ENEMIES_PER_ROW];

	//now all obstacles
	for (int i = 0; i < NUM_OBSTACLES; ++i)
	{
		int obstacleX = X_POSITION_LEFT_OBSTACLE + X_SEPARATION_BETWEEN_OBSTACLES*i;
		obstacles[i] = new Entity(obstacleX, OBSTACLES_Y_POSITION, OBSTACLES_X_DIMENSIONS,
			OBSTACLES_Y_DIMENSIONS, false);
		obstacles[i]->health = OBSTACLES_HEALTHPOINTS;
	}

	//init game text
	currentScoreText = new MenuText(117, 0, 50, 100, "Score: ");
	std::string scoreValue = std::to_string(App->gameLoop->score);
	currentScoreValue = new MenuText(217, 0, 50, 30, scoreValue.c_str());
	currentHealthText = new MenuText(317, 0, 50, 100, "Health: ");
	std::string healthValue = std::to_string(PLAYER_HEALTHPOINTS);
	currentHealthValue = new MenuText(417, 0, 50, 30, healthValue.c_str());


	App->renderer->AddTextToRender(currentHealthText);
	App->renderer->AddTextToRender(currentScoreValue);
	App->renderer->AddTextToRender(currentScoreText);
	App->renderer->AddTextToRender(currentHealthValue);
	//they start disabled
	currentHealthText->Disable();
	currentHealthValue->Disable();
	currentScoreText->Disable();
	currentScoreValue->Disable();

	enemySpeed = ENEMY_STARTING_SPEED;

	return true;
}

bool ModuleGame::CleanUp()
{
	//frees entities
	for (auto entity : gameEntities)
	{
		SAFE_RELEASE(entity);
	}
	gameEntities.clear();
	//obstacles
	for (auto obst : obstacles)
	{
		SAFE_RELEASE(obst);
	}
	obstacles.clear();
	//lowest enemies clearing
	lowestEnemies.clear();
	//free texts
	App->renderer->RemoveTextToRender(currentScoreText);
	currentScoreText->~MenuText();
	SAFE_RELEASE(currentScoreText);

	App->renderer->RemoveTextToRender(currentScoreValue);
	currentScoreValue->~MenuText();
	SAFE_RELEASE(currentScoreValue);

	App->renderer->RemoveTextToRender(currentHealthText);
	currentHealthText->~MenuText();
	SAFE_RELEASE(currentHealthText);

	App->renderer->RemoveTextToRender(currentHealthValue);
	currentHealthValue->~MenuText();
	SAFE_RELEASE(currentHealthValue);

	return true;
}

void ModuleGame::MoveEnemies(int x, int y)
{
	for (int i = 1; i < gameEntities.size(); ++i)
	{
		gameEntities[i]->entityRect->x += x;
		gameEntities[i]->entityRect->y += y;
		//check if enemy has crossed the bottom end of screen
		if (x == 0 &&
			gameEntities[i]->entityRect->y > SCREEN_HEIGHT)
		{
			App->gameLoop->currentState = END_MENU;
		}
	}
	
}

//treats input and updates player and enemies
update_status ModuleGame::Update()
{
	//TODO(Roger): increase speed of enemies scaling with:
	//1 enemies dead
	//2 how far down they have gone

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
			MoveEnemies(0, static_cast<int>(enemySpeed));
			++stepsDown;
			//we also increase the speed by the constant
			//IncreaseEnemiesSpeed();
		}
		else
		{
			MoveEnemies(direction* static_cast<int>(enemySpeed), 0);
		}
		break;
	case MOVING_LEFT:
		//check if we got to left corner
		if ((mostLeftEnemy->entityRect->x) < LEFT_BORDER_POSITION)
		{
			enemState = MOVING_DOWN;
			MoveEnemies(0, static_cast<int>(enemySpeed));
			++stepsDown;
			//we also increase the speed by the constant
			//IncreaseEnemiesSpeed();
		}
		else
		{
			MoveEnemies(direction * static_cast<int>(enemySpeed), 0);
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
			MoveEnemies(direction * static_cast<int>(enemySpeed), 0);
		}
		else
		{
			MoveEnemies(0, static_cast<int>(enemySpeed));
			++stepsDown;
		}
		break;
	}

	//Enemies firing from time to time
	for (auto enemy : lowestEnemies)
	{
		if (rand() % ENEMY_FIRE_MAX_VAL > ENEMY_FIRE_CHANCE)
		{
			if (enemy != nullptr)
			{
				App->gameLoop->collisions->EnemyFire(enemy->entityRect);
			}
		}

	}

	//update score text value
	currentScoreValue->SetText(std::to_string(App->gameLoop->score).c_str(),
		App->renderer->renderer);

	return UPDATE_CONTINUE;
}

void ModuleGame::EnemyKilled(Entity* deadEnemy)
{
	//if the last enemy died, we are done
	if (gameEntities.size() == 2)
	{
		App->gameLoop->currentState = END_MENU;
		return;
	}

	//we increase the speed by the constant
	IncreaseEnemiesSpeed();
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
	//check if was lowest in column
	auto itLowest = lowestEnemies.begin();
	for (; itLowest != lowestEnemies.end(); ++itLowest)
	{
		if (*itLowest == deadEnemy)
		{
			//if top enemy dead, forget about them shooting
			if (deadEnemy->enemyOnTop == nullptr ||
				deadEnemy->enemyOnTop->health <= 0)
			{
				*itLowest = nullptr;
			}
			else
			{
				*itLowest = deadEnemy->enemyOnTop;
			}
			break;
		}
	}

}

void ModuleGame::EnterMenu()
{
	currentScoreText->Enable();
	currentScoreValue->Enable();

	currentHealthText->Enable();
	currentHealthValue->Enable();

}

void ModuleGame::LeaveMenu()
{
	currentScoreText->Disable();
	currentScoreValue->Disable();

	currentHealthText->Disable();
	currentHealthValue->Disable();
}

void ModuleGame::HealthChanged(int newValue)
{
	currentHealthValue->SetText(std::to_string(newValue).c_str(),
		App->renderer->renderer);
}