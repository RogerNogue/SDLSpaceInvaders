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

//other includes
#include <iostream>

Application::Application()
{
	renderer = new ModuleRender();
	appModules.push_back(renderer);
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
	SDL_Event e;
	SDL_PollEvent(&e);
	switch (e.type) {
	case SDL_QUIT:
		return UPDATE_STOP;
		break;
	case SDL_MOUSEBUTTONDOWN:
		break;
	case SDL_KEYDOWN:
		break;
	case SDL_USEREVENT:
		break;
	default:
		break;
	}

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