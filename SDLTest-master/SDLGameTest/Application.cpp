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
#include "ModuleEntity.h"

//other includes
#include <iostream>

Application::Application()
{
	renderer = new ModuleRender();
	appModules.push_back(renderer);

	input = new ModuleInput();
	appModules.push_back(input);

	entity = new ModuleEntity();
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