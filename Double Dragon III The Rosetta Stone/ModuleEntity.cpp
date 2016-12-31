#include "ModuleEntity.h"
#include <string>

ModuleEntity::ModuleEntity(bool start_enabled) : Module(start_enabled)
{}

ModuleEntity::~ModuleEntity()
{}

void ModuleEntity::UpdateProfundity()
{
	//profundity = position.y * -1;
	int p[22] = {21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	//profundity = -(int)position. y + 224;

	profundity = position.y;

	if (type == player)
	{
		std::string tmp = "PLAYER: " + std::to_string(position.y);
		char tab2[1024];
		strcpy(tab2, tmp.c_str());
		LOG(tab2);
	}

	if (type == enemy)
	{
		std::string tmp = "ENEMY:  " + std::to_string(position.y);
		char tab2[1024];
		strcpy(tab2, tmp.c_str());
		LOG(tab2);
	}
	
}