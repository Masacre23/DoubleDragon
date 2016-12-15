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
	direction = true; //right is true

	// idle right
	idle_right = { 8, 0, 26, 63 };
	// idle left
	idle_left = { 942, 0, 26, 64 };
	// Right & Down
	right_down.frames.push_back({ 8, 0, 26, 64 });
	right_down.frames.push_back({ 48, 0, 26, 64 });
	right_down.frames.push_back({ 80, 0, 26, 64 });
	right_down.frames.push_back({ 113, 0, 26, 64 });
	right_down.speed = 0.1f;

	// Left & Down
	left_down.frames.push_back({ 942, 0, 26, 64 });
	left_down.frames.push_back({ 903, 0, 26, 64 });
	left_down.frames.push_back({ 871, 0, 26, 64 });
	left_down.frames.push_back({ 838, 0, 26, 64 });
	left_down.speed = 0.1f;
	
	// Up right
	up_right.frames.push_back({ 152, 0, 26, 63 });
	up_right.frames.push_back({ 184, 0, 26, 63 });
	up_right.frames.push_back({ 216, 0, 26, 63 });
	up_right.frames.push_back({ 248, 0, 26, 63 });
	up_right.speed = 0.1f;

	// Up left
	up_left.frames.push_back({ 803, 0, 26, 63 });
	up_left.frames.push_back({ 771, 0, 26, 63 });
	up_left.frames.push_back({ 739, 0, 26, 63 });
	up_left.frames.push_back({ 707, 0, 26, 63 });
	up_left.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("Genesis 32X SCD - Double Dragon III The Rosetta Stone - Billy & Jimmy.png"); // arcade version

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
	//SDL_Rect billy = idle.GetCurrentFrame();
	SDL_Rect billy;
	if (direction)
		billy = idle_right;
	else
		billy = idle_left;
	// Horizontal
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		position.x += speed;
		billy = right_down.GetCurrentFrame();
		direction = true;
	}
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		position.x -= speed;
		billy = left_down.GetCurrentFrame();
		direction = false;
	}

	// Vertical
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		position.y -= speed;
		if(direction)
			billy = up_right.GetCurrentFrame();
		else
			billy = up_left.GetCurrentFrame();
	}
	else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		position.y += speed;
		if(direction)
			billy = right_down.GetCurrentFrame();
		else
			billy = left_down.GetCurrentFrame();
	}

	App->renderer->Blit(graphics, position.x + speed, position.y - billy.h, &(billy), 1.0f);
	return UPDATE_CONTINUE;
}