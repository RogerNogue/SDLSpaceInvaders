#include "ModuleMainMenu.h"

//sdl includes
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <SDL.h>
#include <SDL_image.h>
#elif defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif

//////////Module Main Menu//////////

ModuleMainMenu::ModuleMainMenu()
{

}

ModuleMainMenu::~ModuleMainMenu()
{

}

bool ModuleMainMenu::Init()
{
	return true;
}

update_status ModuleMainMenu::Update()
{
	return UPDATE_CONTINUE;
}


bool ModuleMainMenu::CleanUp()
{
	return true;
}


//////////Menu Text class//////////

MenuText::MenuText(int x, int y, int h, int w, char* text)
{
	this->text = text;
	textRect = new SDL_Rect;
	textRect->x = x; textRect->y = y;
	textRect->w = w; textRect->h = h;
}

MenuText::~MenuText()
{
	SAFE_RELEASE(textRect);
}

SDL_Rect* MenuText::GetRect()const
{
	return textRect;
}

void MenuText::SetRect(int x, int y, int h, int w)
{

}

std::string MenuText::GetText()const
{
	return text;
}

void MenuText::SetText(const char* text)
{

}