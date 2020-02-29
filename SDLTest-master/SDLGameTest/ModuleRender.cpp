#include "ModuleRender.h"

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

	

	if (!AddTexture("Assets/Aestroids/aestroid_brown.png"))
	{
		//std::cout << "Load texture Error: " << SDL_GetError() << std::endl;
		return false;
	}
	/*
	if (!AddTexture("Assets/Background/background.jpg"))
	{
		//std::cout << "Load texture Error: " << SDL_GetError() << std::endl;
		return false;
	}*/
	return true;
}

update_status ModuleRender::PostUpdate()
{
	SDL_Rect texture_rect;
	texture_rect.x = 0;   // the x coordinate
	texture_rect.y = 0;   // the y coordinate
	texture_rect.w = 64;  // the width of the texture
	texture_rect.h = 64;  // the height of the texture

	SDL_Rect texture_rect2;
	texture_rect2.x = 0;   // the x coordinate
	texture_rect2.y = 0;   // the y coordinate
	texture_rect2.w = 512;  // the width of the texture
	texture_rect2.h = 512;  // the height of the texture

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, vecTextures[0], nullptr, &texture_rect2);
	SDL_RenderCopy(renderer, vecTextures[1], nullptr, &texture_rect);
	/*for (auto texture : vecTextures)
	{
		SDL_RenderCopy(renderer, texture, nullptr, &texture_rect2);
	}*/
	//SDL_RenderCopy(renderer, texture, nullptr, &texture_rect);
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
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return true;
}
