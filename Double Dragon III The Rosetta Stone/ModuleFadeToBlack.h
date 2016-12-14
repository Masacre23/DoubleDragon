#ifndef __MODULEFADETOBLACK_H__
#define __MODULEFADETOBLACK_H__

#include "Module.h"
#include "Globals.h"

class ModuleFadeToBlack : public Module
{
public:
	ModuleFadeToBlack(bool start_enabled = true);
	~ModuleFadeToBlack();

	bool Start();
	update_status Update();
	void FadeToBlack(Module* module_on, Module* module_off = nullptr, float time = 1.0f);
	bool isFading() const;

private:

	Uint32 start_time = 0;
	Uint32 total_time = 0;
	bool fading_in = true;
	Module* module_on = nullptr;
	Module* module_off = nullptr;
};

#endif // __MODULEFADETOBLACK_H__