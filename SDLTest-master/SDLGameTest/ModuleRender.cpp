#include "ModuleRender.h"
#include "Application.h"
#include "ModuleGame.h"
#include "ModuleGameLoop.h"
#include "ModuleCollisions.h"
#include "SDL_ttf.h"

#include<iostream>

//sdl includes
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <SDL.h>
#include <SDL_image.h>
#elif defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif

SDL_Texture* fontTexture;
SDL_Rect* fontRect;

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
	//TODO(Roger): check if tempSurface has to be released
	SDL_Surface* tempSurface = IMG_Load(file);
	if (tempSurface == nullptr)
	{
		return false;
	}
	//then we make a texture
	//all textures get cleaned at CleanUp Function
	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(
		renderer, tempSurface);
	
	//free surface
	SDL_FreeSurface(tempSurface);

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

	if (!AddTexture("Assets/Enemy/enemy_hurt.png"))
	{
		//std::cout << "Load texture Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if (!AddTexture("Assets/Player/bullet.png"))
	{
		//std::cout << "Load texture Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if (!AddTexture("Assets/Enemy/bullet_enemy.png"))
	{
		//std::cout << "Load texture Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if (!AddTexture("Assets/Aestroids/aestroid_dark.png"))
	{
		//std::cout << "Load texture Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if (!AddTexture("Assets/Aestroids/aestroid_gray.png"))
	{
		//std::cout << "Load texture Error: " << SDL_GetError() << std::endl;
		return false;
	}

	//test fonts 
	if (TTF_Init() < 0)
	{
		//TODO(Roger): error init ttf
	}
	TTF_Font* font = TTF_OpenFont("Assets/Fonts/OpenSans.ttf", 24);
	std::cout << TTF_GetError() << std::endl;
	SDL_Color white = { 255, 255, 255 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "Test Fonts", white);
	fontTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	fontRect = new SDL_Rect;
	fontRect->x = 0;
	fontRect->y = 0;
	fontRect->w = SCREEN_WIDTH;
	fontRect->h = SCREEN_HEIGHT/2;

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

	//render projectiles
	for (auto proj : App->gameLoop->collisions->listProjectiles)
	{
		if (proj->IsFromPlayer())
		{
			SDL_RenderCopy(renderer, vecTextures[PLAYER_PROJECTILE], nullptr,
				proj->projectileRect);
		}
		else
		{
			SDL_RenderCopy(renderer, vecTextures[ENEMY_PROJECTILE], nullptr,
				proj->projectileRect);
		}
		
	}

	//render entities
	//render player
	SDL_RenderCopy(	renderer, vecTextures[PLAYERSHIP], nullptr, 
					App->gameLoop->game->gameEntities[0]->entityRect);

	//render enemies
	for (int i = 1; i < App->gameLoop->game->gameEntities.size(); ++i)
	{
		//check if enemy is healthy or not
		if (App->gameLoop->game->gameEntities[i]->health == ENEMY_HEALTHPOINTS)
		{
			SDL_RenderCopy(renderer, vecTextures[ENEMYSHIP], nullptr,
				App->gameLoop->game->gameEntities[i]->entityRect);
		}
		else
		{
			SDL_RenderCopy(renderer, vecTextures[ENEMYSHIPHURT], nullptr,
				App->gameLoop->game->gameEntities[i]->entityRect);
		}
	}

	//render asteroids
	for (auto obstacles : App->gameLoop->game->obstacles)
	{
		//check its health
		if (obstacles->health == OBSTACLES_HEALTHPOINTS)
		{
			SDL_RenderCopy(renderer, vecTextures[OBSTACLE_HEALTHY], nullptr,
				obstacles->entityRect);
		}
		else
		{
			SDL_RenderCopy(renderer, vecTextures[OBSTACLE_HURT], nullptr,
				obstacles->entityRect);
		}
	}
	for (auto text : texts)
	{
		if (text->IsEnabled())
		{
			SDL_RenderCopy(renderer, text->fontTexture, nullptr,
				text->GetRect());
		}
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
	//clean the texts
	for (auto text : texts)
	{
		text->~MenuText();
	}
	texts.clear();
	SAFE_RELEASE(backgroundRect);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return true;
}

bool ModuleRender::AddTextToRender(MenuText* menuText)
{
	bool containsElement = false;
	for (auto elem : texts)
	{
		if (elem == menuText)
		{
			//element already there, we just leave
			containsElement = true;
			return false;
		}
	}
	//add all the info for the menuText
	menuText->font = TTF_OpenFont("Assets/Fonts/OpenSans.ttf", 24);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(
		menuText->font, menuText->GetText().c_str(), menuText->textColor);
	menuText->fontTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);

	texts.push_back(menuText);
}
bool ModuleRender::RemoveTextToRender(MenuText* menuText)
{
	for (auto itList = texts.begin(); itList != texts.end(); ++itList)
	{
		if ((*itList) == menuText)
		{
			//element found, we erase it
			texts.erase(itList);
			return true;
		}
	}
}


//////////Menu Text class//////////

MenuText::MenuText(int x, int y, int h, int w, const char* text)
{
	this->text = text;
	textRect = new SDL_Rect;
	textRect->x = x; textRect->y = y;
	textRect->w = w; textRect->h = h;
}

MenuText::~MenuText()
{
	SDL_DestroyTexture(fontTexture);
	//SAFE_RELEASE(fontTexture);
	//SAFE_RELEASE(font);
	SAFE_RELEASE(textRect);
}

SDL_Rect* MenuText::GetRect()const
{
	return textRect;
}

void MenuText::SetRect(int x, int y, int h, int w)
{
	textRect->x = x;
	textRect->y = y;
	textRect->h = h;
	textRect->w = w;
}

std::string MenuText::GetText()const
{
	return text;
}

void MenuText::SetText(const char* text, SDL_Renderer* renderer)
{
	this->text = text;
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(
		font, this->text.c_str(), textColor);
	fontTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);
}