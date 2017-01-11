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
	void Respawn();
	void Reset();
	void InsertPlayer2();

public:
	SDL_Texture* graphics = nullptr;
	SDL_Texture* gameoverTexture = nullptr;
	SDL_Rect ground;
	SDL_Rect background;

	CreaturePlayer* player, *player2;
	EntityExit* exit;
	int num_waves = 0;
	bool new_wave = false;
	bool player2created = false;
};

#endif