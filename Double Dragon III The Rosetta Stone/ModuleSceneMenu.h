#ifndef __MODULESCENEMENU_H__
#define __MODULESCENEMENU_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneMenu : public Module
{
public:
	ModuleSceneMenu(bool start_enabled = true);
	~ModuleSceneMenu();

	bool Start();
	update_status Update();
	bool  CleanUp();

	SDL_Texture* graphics = nullptr;
	SDL_Rect title;
	SDL_Rect background;
};

#endif