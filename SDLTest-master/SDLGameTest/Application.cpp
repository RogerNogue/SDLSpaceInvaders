#include "Application.h"

//SDL includes
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <SDL.h>
#include <SDL_image.h>
#elif defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif

//modules
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleGame.h"

//other includes
#include <iostream>

Application::Application()
{
	renderer = new ModuleRender();
	appModules.push_back(renderer);

	input = new ModuleInput();
	appModules.push_back(input);

	//I like collisions being before entity so that entitiy update comes after collisions
	collisions = new ModuleCollisions();
	appModules.push_back(collisions);

	entity = new ModuleGame();
	appModules.push_back(entity);

}

Application::~Application()
{

}

bool Application::Init()
{
	//init all the modules
	for (auto mod : appModules)
	{
		mod->Init();
	}
	return true;
}

update_status Application::Update()
{
	//get start of frame timer
	unsigned startTime = SDL_GetTicks();

	//update all the modules
	update_status modUpdateStatus;
	//PreUpdates
	for (auto mod : appModules)
	{
		modUpdateStatus = mod->PreUpdate();
		if (modUpdateStatus != UPDATE_CONTINUE)
		{
			return modUpdateStatus;
		}
	}
	//Updates
	for (auto mod : appModules)
	{
		modUpdateStatus = mod->Update();
		if (modUpdateStatus != UPDATE_CONTINUE)
		{
			return modUpdateStatus;
		}
	}
	//PostUpdates
	for (auto mod : appModules)
	{
		modUpdateStatus = mod->PostUpdate();
		if (modUpdateStatus != UPDATE_CONTINUE)
		{
			return modUpdateStatus;
		}
	}

	//get end of frame timer
	unsigned endTime = SDL_GetTicks();
	unsigned timeResult = endTime - startTime;

	//60 fps enforcement
	if (timeResult < 16)
	{
		SDL_Delay(16 - timeResult);
	}

}

bool Application::CleanUp()
{
	//Cleanup of all the modules
	for (auto mod : appModules)
	{
		if (!mod->CleanUp())
		{
			return false;
		}
	}
	return true;
}