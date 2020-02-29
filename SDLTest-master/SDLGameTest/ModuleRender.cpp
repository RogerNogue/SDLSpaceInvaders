#include "ModuleRender.h"
#include "Application.h"
#include "ModuleEntity.h"

//sdl includes
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <SDL.h>
#include <SDL_image.h>
#elif defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif

ModuleRender::ModuleRender()
	:Module()
{

}

ModuleRender::~ModuleRender()
{

}

//for cache safety reasons, lets not inline this funcation
bool ModuleRender::AddTexture(const char* file)
{
	//first we make a surface
	//local pointer to surface
	//SDL_Surface* tempSurface = IMG_Load(file);
	SDL_Surface* tempSurface = IMG_Load(file);

	//then we make a texture
	//all textures get cleaned at CleanUp Function
	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(
		renderer, tempSurface);
	if (tempTexture != nullptr)
	{
		vecTextures.push_back(tempTexture);
		return true;
	}
	
	else return false;
}

bool ModuleRender::Init()
{
	//SDL inits
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		//std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow(
		"Space Invaders Roger!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		//std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	renderer = SDL_CreateRenderer(
		window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		SDL_DestroyWindow(window);
		//std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}
	
	if (!AddTexture("Assets/Background/background.jpg"))
	{
		//std::cout << "Load texture Error: " << SDL_GetError() << std::endl;
		return false;
	}
	
	if (!AddTexture("Assets/Player/spaceship.png"))
	{
		//std::cout << "Load texture Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if (!AddTexture("Assets/Enemy/spaceship_enemy_red.png"))
	{
		//std::cout << "Load texture Error: " << SDL_GetError() << std::endl;
		return false;
	}

	//initialize background rect, its deleted in the cleanup
	backgroundRect = new SDL_Rect;
	backgroundRect->x = 0;
	backgroundRect->y = 0;
	backgroundRect->w = SCREEN_WIDTH;
	backgroundRect->h = SCREEN_HEIGHT;
	return true;
}

update_status ModuleRender::PostUpdate()
{
	SDL_RenderClear(renderer);

	//render background
	SDL_RenderCopy(renderer, vecTextures[BACKGROUND], nullptr, backgroundRect);

	//iterates over all the entites and draws them
	//since first element is player, we old school iterate over it
	//render player
	SDL_RenderCopy(	renderer, vecTextures[PLAYERSHIP], nullptr, 
					App->entity->gameEntities[0]->entityRect);

	//render enemies
	for (int i = 1; i < NUM_ENEMIES + 1; ++i)
	{
		SDL_RenderCopy(renderer, vecTextures[ENEMYSHIP], nullptr, 
			App->entity->gameEntities[i]->entityRect);
	}
	
	SDL_RenderPresent(renderer);
	return UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp()
{
	//clean the textures
	for (auto texture : vecTextures)
	{
		SDL_DestroyTexture(texture);
	}
	vecTextures.clear();
	delete backgroundRect;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return true;
}
