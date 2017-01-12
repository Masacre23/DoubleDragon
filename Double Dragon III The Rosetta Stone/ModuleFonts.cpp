#include "ModuleFonts.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

using namespace std;

ModuleFonts::ModuleFonts(bool start_enabled) : Module(start_enabled)
{}

ModuleFonts::~ModuleFonts()
{}

bool ModuleFonts::Start()
{
	bool ret = true;

	LOG("Loading fonts");

	graphics = App->textures->Load("resources/fonts.png");

	return ret;
}

bool ModuleFonts::CleanUp()
{
	
	LOG("Unloading fonts");

	App->textures->Unload(graphics);

	return true;
}
/*******************************************************/
void ModuleFonts::DrawFace(iPoint pos, int face)
{
	if(!face)
		App->renderer->Blit(graphics, pos.x, pos.y, faceJimmy);
	else
		App->renderer->Blit(graphics, pos.x, pos.y, faceBilly);
}

/*******************************************************/
void ModuleFonts::DrawLine(const string& words, int line, iPoint pos)
{
	int w = width[line];
	int h = height[line];
	for (int i = 0; i < words.size(); ++i)
	{
		App->renderer->Blit(graphics, pos.x + w * i, pos.y + h * line, getRect(words[i], line));
	}
}

/******************************************************/
SDL_Rect* ModuleFonts::getRect(const char c, int line)
{
	SDL_Rect* ret = new SDL_Rect();

	int w = width[line];
	int h = height[line];

	switch (line)
	{
	case 0:
	case 1:
	case 2:
		for (int i = 0; i < normal_letters.size(); ++i)
		{
			if (normal_letters[i] == c)
			{
				*ret = { w*i, h * line, w, h };
				break;
			}
		}
		break;
	case 3:
		for (int i = 0; i < golden_letters.size(); ++i)
		{
			if (golden_letters[i] == c)
			{
				*ret = { w*i, height[line-1] * line, w, h };
				break;
			}
		}
		break;
	case 4:
	case 5:
		for (int i = 0; i < big_numbers.size(); ++i)
		{
			if (big_numbers[i] == c)
			{
				if(line == 4)
					*ret = { w*i, height[line - 2] * (line-1) + height[line - 1], w, h };
				else
					*ret = { w*i, height[line - 3] * (line - 2) + height[line - 2] + height[line - 1], w, h };
				break;
			}
		}
		break;
	}
	
	return ret;
}