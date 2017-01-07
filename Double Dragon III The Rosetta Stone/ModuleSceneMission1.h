#ifndef __MODULESCENEMISSION1_H__
#define __MODULESCENEMISSION1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;
class EntityExit;

class ModuleSceneMission1 : public Module
{
public:
	ModuleSceneMission1(bool start_enabled = true);
	~ModuleSceneMission1();

	bool Start();
	update_status Update();
	bool  CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect background;

	CreaturePlayer* player;
	EntityExit* exit;
	int num_waves = 0;
	bool new_wave = false;
};

#endif