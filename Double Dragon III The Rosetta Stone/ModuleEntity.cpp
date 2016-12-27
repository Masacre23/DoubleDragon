#include "ModuleEntity.h"

ModuleEntity::ModuleEntity(bool start_enabled) : Module(start_enabled)
{}

ModuleEntity::~ModuleEntity()
{}

void ModuleEntity::UpdateProfundity()
{
	profundity = position.y / 5;
}