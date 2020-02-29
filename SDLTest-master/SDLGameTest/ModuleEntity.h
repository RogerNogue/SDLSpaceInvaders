#ifndef _MODULEPLAYER_
#define _MODULEPLAYER_


#include "Module.h"
#include <vector>

//fwd declarations

class SDL_Rect;

class Entity final
{
public:
	Entity(bool isPlayer);
	Entity(int x, int y, int w, int h, bool isPlayer);

	~Entity();

	inline void SetRect(int x, int y, int w, int h);

	inline bool IsPlayer() const { return isPlayer; }

public:
	SDL_Rect* entityRect = nullptr;

private:
	bool isPlayer;
};

class ModuleEntity final:
	public Module
{
public:
	ModuleEntity();

	~ModuleEntity();

	bool Init() override;

	bool CleanUp() override;

	update_status Update() override;

public:
	//first position is for the player
	std::vector<Entity*> gameEntities =
		std::vector<Entity*>(NUM_ENEMIES + 1);
	
};

#endif // !_MODULEPLAYER_