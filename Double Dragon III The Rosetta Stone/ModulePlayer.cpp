#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	position.x = 100;
	position.y = 216;
	speed = 1;

	int n = 20+2+2;

	// Right & Down
	/*right_down.frames.push_back({ 8, 0, 26, 64 });
	right_down.frames.push_back({ 48, 0, 26, 64 });
	right_down.frames.push_back({ 80, 0, 26, 64 });
	right_down.frames.push_back({ 113, 0, 26, 64 });
	right_down.speed = 0.1f;*/
	right_down.frames.push_back({ 33-n, 0, 70, 64 });
	right_down.frames.push_back({ 108-n, 0, 70, 64 });
	right_down.frames.push_back({ 173-n, 0, 70, 64 });
	right_down.frames.push_back({ 242-n, 0, 70, 64 });
	right_down.speed = 0.1f;
	
	// Up
	/*up.frames.push_back({ 152, 0, 26, 64 });
	up.frames.push_back({ 184, 0, 26, 64 });
	up.frames.push_back({ 216, 0, 26, 64 });
	up.frames.push_back({ 248, 0, 26, 64 });
	up.speed = 0.1f;*/
	up.frames.push_back({ 305-n, 0, 70, 64 });
	up.frames.push_back({ 362-n, 0, 70, 64 });
	up.frames.push_back({ 414-n, 0, 70, 64 });
	up.frames.push_back({ 462-n, 0, 70, 64 });
	up.speed = 0.1f;

	// Jump
	jump = { 422 - n, 79, 64, 64 };

	// Punch
	/*punch.frames.push_back({ 8-12, 0, 26+12, 64 });
	punch.frames.push_back({ 8-12, 79, 26+12, 64 });
	punch.frames.push_back({ 40, 79, 39, 64 });
	punch.frames.push_back({ 8-12, 79, 26+12, 64 });
	punch.frames.push_back({ 8-12, 0, 26+12, 64 });
	punch.speed = 0.1f;*/
	punch.frames.push_back({ 33-n, 0, 70, 64 });
	punch.frames.push_back({ 33-n, 79, 70, 64 });
	punch.frames.push_back({ 101-n, 79, 70, 64 });
	punch.frames.push_back({ 33-n, 79, 70, 64 });
	punch.frames.push_back({ 33-n, 0, 70, 64 });
	punch.speed = 0.1f;

	// Kick
	/*kick.frames.push_back({ 8, 0, 26, 64 });
	kick.frames.push_back({ 88, 81, 24, 64 });
	kick.frames.push_back({ 120, 81, 38, 64 });
	kick.frames.push_back({ 88, 81, 24, 64 });
	kick.frames.push_back({ 8, 0, 26, 64 });
	kick.speed = 0.1f;*/
	kick.frames.push_back({ 33 - n, 0, 70, 64 });
	kick.frames.push_back({ 176-n, 81, 70, 64 });
	kick.frames.push_back({ 241-n, 81, 70, 64 });
	kick.frames.push_back({ 176-n, 81, 70, 64 });
	kick.frames.push_back({ 33 - n, 0, 70, 64 });
	kick.speed = 0.1f;

	//Kick jump
	kick_jump = { 487 - n, 79, 70, 64 };
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("Genesis 32X SCD - Double Dragon III The Rosetta Stone - Billy & Jimmy2.png"); // arcade version

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status ModulePlayer::Update()
{
	SDL_Rect billy = right_down.frames[0];
	static int currentAttack = 0;
	static bool flip = false; // When the character goes left is true
	//static bool isJumping = false;

	if (!isAttacking(currentAttack))
	{

		// Horizontal
		if (!isJumping) 
		{
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				position.x += speed;
				billy = right_down.GetCurrentFrame();
				flip = false;
			}
			else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				position.x -= speed;
				billy = right_down.GetCurrentFrame();
				flip = true;
			}
		}

		// Vertical and jump
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || isJumping)
		{
			Jump(position.x, position.y, isJumping);
			billy = jump;
		}
		else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			position.y -= speed;
			billy = up.GetCurrentFrame();
		}
		else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			position.y += speed;
			billy = right_down.GetCurrentFrame();
		}
	}
	else
	{
		billy = getAttack(currentAttack);
	}

	App->renderer->Blit(graphics, position.x + speed, position.y - billy.h, &(billy), 1.0f, flip);
	return UPDATE_CONTINUE;
}

//------------------------------------------------------------------
bool ModulePlayer::isAttacking(int& currentAttack)
{
	if (currentAttack != NULL)
	{
		if (punch.AnimationFinished())
		{
			currentAttack = 0;
			return false;
		}
		if (kick.AnimationFinished())
		{
			currentAttack = 0;
			return false;
		}
		return true;
	}
	else
	{
		if (App->input->GetKey(SDL_SCANCODE_COMMA) == KEY_DOWN)
		{
			currentAttack = SDL_SCANCODE_COMMA;
		}
		else if (App->input->GetKey(SDL_SCANCODE_PERIOD) == KEY_DOWN)
		{
			currentAttack = SDL_SCANCODE_PERIOD;
		}
		return false;
	}
		
}

//-------------------------------------------------------------------
SDL_Rect& ModulePlayer::getAttack(const int& attack)
{
	switch (attack)
	{
	case SDL_SCANCODE_COMMA: //Punch
		if (isJumping)
		{
			Jump(position.x, position.y, isJumping);
			return jump;
		}
		return punch.GetCurrentFrame();
		break;

	case SDL_SCANCODE_PERIOD: //Kick
		if (isJumping)
		{
			Jump(position.x, position.y, isJumping);
			return kick_jump;
		}
		return kick.GetCurrentFrame();
		break;
	}
}

//--------------------------------------------------------------------
void ModulePlayer::Jump(int& x, int& y, bool& isJumping)
{
	static int y_ini = -1;
	float aceleration = 0.3f;
	static float speed = 5;
	static bool jumpDirection[] = {false, false}; //right, left

	if (y_ini == -1)// Init
	{
		y_ini = y;
		--y;
		isJumping = true;
		speed = 5;
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			jumpDirection[0] = true;
		}
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			jumpDirection[1] = true;
		}
	}
	else if (y_ini <= y) 
	{
		y = y_ini;
		y_ini = -1;
		isJumping = false;
		jumpDirection[0] = false;
		jumpDirection[1] = false;
	}
	else
	{
		speed -= aceleration;
		y -= speed;

		if (jumpDirection[0])
			x += 2;
		else if(jumpDirection[1])
			x -= 2;
	}
}