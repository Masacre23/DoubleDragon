#ifndef __ENTITYEXIT_H__
#define __ENTITYEXIT_H__

#include "ModuleEntity.h"
#include "ModuleCollision.h"

class EntityExit : public ModuleEntity
{
public:
	EntityExit(const SDL_Rect* rect, bool start_enabled = true);
	~EntityExit();

	void NextRoom() const;

public:
	Collider* collider;
};

#endif