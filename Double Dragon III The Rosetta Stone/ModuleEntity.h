#ifndef __MODULEENTITY_H__
#define __MODULEENTITY_H__

#include <list>
#include "Globals.h"
#include "Module.h"
#include "Point.h"

enum Types
{
	enemy,
	player,
	exits
};


class ModuleEntity : public Module
{
public:
	ModuleEntity(bool start_enabled = true);
	~ModuleEntity();

	void UpdateProfundity();

public:
	fPoint position;
	float profundity = 0;
	Types type;
};

#endif