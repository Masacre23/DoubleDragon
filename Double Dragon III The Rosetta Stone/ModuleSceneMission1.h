#ifndef __MODULESCENEMISSION1_H__
#define __MODULESCENEMISSION1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneMission1 : public Module
{
public:
	ModuleSceneMission1(bool start_enabled = true);
	~ModuleSceneMission1();

	bool Start();
	update_status Update();
	bool  CleanUp();

	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
};

#endif