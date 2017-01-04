#ifndef __MODULEWINDOW_H__
#define __MODULEWINDOW_H__

#include "Module.h"

struct SDL_Window;
struct SDL_Surface;

class ModuleWindow : public Module
{
public:

	ModuleWindow();

	// Destructor
	virtual ~ModuleWindow();

	// Called before quitting
	bool Init();

	// Called before quitting
	bool CleanUp();

	void setCenter(int x);
public:
	//The window we'll be rendering to
	SDL_Window* window = nullptr;

	//The surface contained by the window
	SDL_Surface* screen_surface = nullptr;

	//When we move the camera this variable must change
	int center_window_x = SCREEN_WIDTH / 2;
};

#endif // __MODULEWINDOW_H__