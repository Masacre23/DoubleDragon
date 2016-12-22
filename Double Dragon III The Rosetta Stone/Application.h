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
class ModulePlayer;
class ModuleSceneMenu;
class ModuleSceneMission1;

//class ModuleEntity;
class EntityManager;

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
	//ModulePlayer* player;
	//ModuleEntity* entity;

	ModuleSceneMenu* scene_menu;
	ModuleSceneMission1* scene_mission1;

	EntityManager* entityManager;
//private:

	std::list<Module*> modules;

};

extern Application* App;

#endif // __APPLICATION_CPP__