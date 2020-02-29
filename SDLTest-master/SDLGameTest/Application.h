#ifndef _APPLICATION_
#define _APPLICATION_

#include "Globals.h"
#include "Module.h"
#include <vector>

//fwd declarations of modules
class ModuleRender;
class ModuleInput;

class SDL_Renderer;
class SDL_Texture;
class SDL_Surface;
class SDL_Window;


class Application final
{
public://methods
	Application();				//Constructor

	~Application();				//Destructor

	bool Init();				//App data initialization

	update_status Update();		//App update

	bool CleanUp();				//App cleanup

public://variables


private://methods

private://variables
	//std::vector<Module*> appModules;	//array of app modules

	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Surface* space_ship_surface = nullptr;
	SDL_Window* window = nullptr;

};


#endif // !_APPLICATION
