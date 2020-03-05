#ifndef _MODULEMAINMENU_
#define _MODULEMAINMENU_

#include "Module.h"
#include <string>

class SDL_Rect;

//class that contains info about a text
class MenuText final
{
public:
	MenuText(int x, int y, int w, int h, char* text);

	~MenuText();

	SDL_Rect* GetRect()const;

	void SetRect(int x, int y, int h, int w);

	std::string GetText()const;

	void SetText(const char* text);

public://variables
	bool highlighted = false;

private://variables
	SDL_Rect* textRect = nullptr;
	std::string text = nullptr;

};

class ModuleMainMenu final:
	public Module
{
public:
	ModuleMainMenu();

	~ModuleMainMenu();

	bool Init()override;

	update_status Update() override;

	bool CleanUp()override;

public://variables
	MenuText playButton;
};

#endif