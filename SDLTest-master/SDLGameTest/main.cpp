

#include <iostream>
#include "Application.h"
#include "Globals.h"

//SDL inclusion for main re definition error fixing
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <SDL.h>
#include <SDL_image.h>
#elif defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = nullptr;

int main(int, char **) 
{
	main_states gameState = MAIN_CREATION;
	while (gameState != MAIN_EXIT)
	{
		switch (gameState)
		{
			case MAIN_CREATION:
			{
				//destructor not ever necessary since variable lasts the whole execution
				App = new Application();
				gameState = MAIN_START;
				break;
			}
			case MAIN_START:
			{
				if (!App->Init())
				{
					std::cout << "Application init error" << std::endl;
					gameState = MAIN_EXIT;
				}
				else
				{
					gameState = MAIN_UPDATE;
				}
				break;
			}
			case MAIN_UPDATE:
			{
				update_status updateStatus;
				updateStatus = App->Update();
				if (updateStatus == UPDATE_ERROR)
				{
					std::cout << "Application init error" << std::endl;
					gameState = MAIN_EXIT;
				}
				else if (updateStatus == UPDATE_STOP)
				{
					std::cout << "Application stopped correctly" << std::endl;
					gameState = MAIN_FINISH;
				}
				break;
			}
			case MAIN_FINISH:
			{
				std::cout << "Application CleanUp" << std::endl;
				if (!App->CleanUp())
				{
					std::cout << "Application Cleanup had errors" << std::endl;
				}
				gameState = MAIN_EXIT;
				break;
			}
		}
	}
	return 0;
  
}
