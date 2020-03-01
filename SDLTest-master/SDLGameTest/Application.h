#ifndef _APPLICATION_
#define _APPLICATION_

#include "Globals.h"
#include "Module.h"
#include <vector>

//fwd declarations of modules
class ModuleRender;
class ModuleInput;
class ModuleCollisions;
class ModuleEntity;

class Application final
{
public://methods
	Application();				//Constructor

	~Application();				//Destructor

	bool Init();				//App data initialization

	update_status Update();		//App update

	bool CleanUp();				//App cleanup

public://variables
	ModuleInput* input = nullptr;
	ModuleRender* renderer = nullptr;
	ModuleCollisions* collisions = nullptr;
	ModuleEntity* entity = nullptr;

private://methods

private://variables
	std::vector<Module*> appModules;	//array of app modules

	

};

//should be the only singleton
extern Application* App;


#endif // !_APPLICATION
