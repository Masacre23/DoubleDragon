#ifndef __MODULESCENEINI_H__
#define __MODULESCENEINI_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;

enum iniState {
	SEGA,
	FLYING,
	BLACK
//	INIT_PAGE,
};


class ModuleSceneIni : public Module
{
public:
	ModuleSceneIni(bool start_enabled = true);
	~ModuleSceneIni();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	iniState currentState = SEGA;
	SDL_Texture* sega = nullptr;
	SDL_Texture* flying = nullptr;

	SDL_Rect flyingRect;
	Animation segaAnimation;
};
#endif //__MODULESCENE_H__