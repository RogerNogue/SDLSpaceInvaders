#ifndef _MODULERENDER_
#define _MODULERENDER_
#include "Module.h"

//fwd declarations
class SDL_Renderer;
class SDL_Texture;
class SDL_Surface;
class SDL_Window;

class ModuleRender final:
	public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init() override;

	update_status PostUpdate() override;

	bool CleanUp() override;

private://variables
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Surface* space_ship_surface = nullptr;
	SDL_Window* window = nullptr;
};

#endif 
