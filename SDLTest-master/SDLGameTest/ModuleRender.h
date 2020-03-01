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
	PLAYER_PROJECTILE,
	ENEMYP_ROJECTILE
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

#endif 
