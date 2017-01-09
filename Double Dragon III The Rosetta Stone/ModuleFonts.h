#ifndef __MODULEFONTS_H__
#define __MODULEFONTS_H__

#include "Globals.h"
#include "Module.h"
#include "Point.h"

#include <iostream>
#include <string>

using namespace std;

struct SDL_Texture;

class ModuleFonts : public Module
{
public:
	ModuleFonts(bool start_enabled = true);
	~ModuleFonts();

	bool Start();
	bool CleanUp();

	void DrawFace(iPoint pos);
	void DrawLine(const string& words, int line, iPoint pos);
	SDL_Rect* getRect(const char c, int line);

public:
	SDL_Texture* graphics = nullptr;
	SDL_Rect* face = new SDL_Rect({168, 40, 23, 23});

	string normal_letters = " 0123456789abcdefghijklmnopqrstuvwxyz?!·#$%&'()*+,_./";
	string golden_letters = " 0123456789timecns:/*-+";
	string big_numbers = "0123456789";

	//int posY[6] = {0, 8, 16, 24, };
	int width[6] = { 8, 8, 8, 8, 16, 16};
	int height[6] = {8, 8, 8, 15, 24, 24};
};

#endif