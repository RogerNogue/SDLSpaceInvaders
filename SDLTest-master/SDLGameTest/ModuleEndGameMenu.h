#ifndef _MODULEENDGAMEMENU_
#define _MODULEENDGAMEMENU_

class MenuText;

#include "Module.h"
class ModuleEndGameMenu final:
	public Module
{
public:
	ModuleEndGameMenu();

	~ModuleEndGameMenu();

	bool Init()override;

	update_status Update() override;

	bool CleanUp()override;

	void EnterMenu();

	void LeaveMenu();

private:
	MenuText* gameEndedText = nullptr;

	MenuText* scoreText = nullptr;
	MenuText* scoreValue = nullptr;

	MenuText* topScoreText = nullptr;
	MenuText* topScoreValue = nullptr;

	MenuText* continueText = nullptr;

};

#endif