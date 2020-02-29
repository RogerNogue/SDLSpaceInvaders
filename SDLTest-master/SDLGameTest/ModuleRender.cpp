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

bool ModuleRender::Init()
{
	//SDL inits
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		//std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow(
		"Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
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

	space_ship_surface = IMG_Load(
		"Assets/Player/spaceship.png");
	if (!space_ship_surface)
	{
		//std::cout << "IMG_Load Error: " << SDL_GetError() << std::endl;
		return false;
	}

	texture = SDL_CreateTextureFromSurface(
		renderer, space_ship_surface);
	if (!texture)
	{
		//std::cout << "IMG_LoadTexture Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

update_status ModuleRender::PostUpdate()
{
	SDL_Rect texture_rect;
	texture_rect.x = 0;   // the x coordinate
	texture_rect.y = 0;   // the y coordinate
	texture_rect.w = 64;  // the width of the texture
	texture_rect.h = 64;  // the height of the texture

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, nullptr, &texture_rect);
	SDL_RenderPresent(renderer);
	return UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp()
{
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(space_ship_surface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return true;
}
