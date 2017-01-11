#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class CreaturePlayer;
class ModuleSceneMenu;
class ModuleSceneMission1;
class ModuleCollision;

class EntityManager;
class ModuleFonts;
class ModuleSceneIni;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModuleCollision* collision;

	ModuleSceneIni* scene_ini;
	ModuleSceneMenu* scene_menu;
	ModuleSceneMission1* scene_mission1;

	EntityManager* entityManager;
	ModuleFonts* fonts;
//private:
	int coins = 15;
	int time = 150 * 60;
	int numplayers = 1;
	std::list<Module*> modules;

};

extern Application* App;

#endif // __APPLICATION_CPP__