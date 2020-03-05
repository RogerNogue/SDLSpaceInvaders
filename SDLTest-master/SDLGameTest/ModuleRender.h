#ifndef _MODULERENDER_
#define _MODULERENDER_
#include "Module.h"
#include <vector>

//fwd declarations
class SDL_Renderer;
class SDL_Texture;
class SDL_Surface;
class SDL_Window;
class SDL_Rect;

enum TextureMap
{
	BACKGROUND = 0,
	PLAYERSHIP,
	ENEMYSHIP,
	ENEMYSHIPHURT,
	PLAYER_PROJECTILE,
	ENEMY_PROJECTILE,
	OBSTACLE_HEALTHY,
	OBSTACLE_HURT
};

class ModuleRender final:
	public Module
{
public://methods
	ModuleRender();
	~ModuleRender();

	bool Init() override;

	update_status PostUpdate() override;

	bool CleanUp() override;

private://methods
	bool AddTexture(const char* file);

private://variables
	//TODO(Roger):once the game is done, set vector size to amount of sprites
	std::vector<SDL_Texture*> vecTextures;
	SDL_Renderer* renderer = nullptr;
	SDL_Window* window = nullptr;
	SDL_Rect* backgroundRect = nullptr;
};

//class that contains info about a text
class MenuText final
{
public:
	MenuText(int x, int y, int w, int h, const char* text);

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

#endif 
