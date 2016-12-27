#include "Globals.h"
#include "Application.h"
#include "CreaturePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "src\pugixml.hpp"

CreaturePlayer::CreaturePlayer(bool start_enabled) : EntityCreature(PLAYER1, start_enabled)
{
	position.x = 120;
	position.y = 216;
	speed = 1;
	//int n = 20+2+2;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data.xml");
	pugi::xml_node config = doc.document_element();
	pugi::xml_node entities = config.child("entities");
	pugi::xml_node player1 = entities.child("player1");	


	// Rotate kick jump
	pugi::xml_node rotate_kick_jumpXML = player1.child("rotate_kick_jump");
	rotate_kick_jump.frames.push_back(
	{
		rotate_kick_jumpXML.child("frame1").attribute("x").as_int(),
		rotate_kick_jumpXML.child("frame1").attribute("y").as_int(),
		rotate_kick_jumpXML.child("frame1").attribute("w").as_int(),
		rotate_kick_jumpXML.child("frame1").attribute("h").as_int()
	});
	rotate_kick_jump.frames.push_back(
	{
		rotate_kick_jumpXML.child("frame2").attribute("x").as_int(),
		rotate_kick_jumpXML.child("frame2").attribute("y").as_int(),
		rotate_kick_jumpXML.child("frame2").attribute("w").as_int(),
		rotate_kick_jumpXML.child("frame2").attribute("h").as_int()
	});
	rotate_kick_jump.frames.push_back(
	{
		rotate_kick_jumpXML.child("frame3").attribute("x").as_int(),
		rotate_kick_jumpXML.child("frame3").attribute("y").as_int(),
		rotate_kick_jumpXML.child("frame3").attribute("w").as_int(),
		rotate_kick_jumpXML.child("frame3").attribute("h").as_int()
	});
	rotate_kick_jump.frames.push_back(
	{
		rotate_kick_jumpXML.child("frame4").attribute("x").as_int(),
		rotate_kick_jumpXML.child("frame4").attribute("y").as_int(),
		rotate_kick_jumpXML.child("frame4").attribute("w").as_int(),
		rotate_kick_jumpXML.child("frame4").attribute("h").as_int()
	});

	rotate_kick_jump.speed = rotate_kick_jumpXML.attribute("speed").as_float();
}

CreaturePlayer::~CreaturePlayer()
{}

// Load assets
bool CreaturePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("Genesis 32X SCD - Double Dragon III The Rosetta Stone - Billy & Jimmy2.png");

	playerState = IDLE;

	return true;
}

// Unload assets
bool CreaturePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status CreaturePlayer::Update()
{
	UpdateProfundity();
	SDL_Rect billy = right_down.frames[0];
	static bool flip = false; // When the character goes left is true

	switch (playerState)
	{
	//case IDLE:
		
		//break;
	case ATTACKING:
		if (!isAttacking())
			break;
		billy = getAttack();
		break;
	case JUMPING:
		isJumping();
		if (isAttacking())
		{
			billy = getAttack();
			break;
		}
		billy = jump;
		break;
	default:
		if (isAttacking())
		{
			playerState = ATTACKING;
			break;
		}
		if (isJumping())
			break;

		int newSpeed = getSpeed();
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			flip = false;
			//newSpeed = getSpeed();
			position.x += newSpeed;
			billy = right_down.GetCurrentFrame();
		}
		else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			flip = true;
			//newSpeed = getSpeed();
			position.x -= newSpeed;
			billy = right_down.GetCurrentFrame();
		}

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			if (!creatureCollider->collisionMatrix[0][2])//Player-Wall
				position.y -= speed;
			billy = up.GetCurrentFrame();
		}
		else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			position.y += speed;
			billy = right_down.GetCurrentFrame();
		}
		break;
	}

	creatureCollider->SetPos(position.x, position.y - 64);

	App->renderer->Blit(graphics, position.x + speed, position.y - billy.h, &(billy), 1.0f, flip);
	return UPDATE_CONTINUE;
}

/**************************************************************/
int CreaturePlayer::getSpeed()
{
	static bool running = false;
	static int time = 0;
	static int maxTime = 60;
	if (running)
	{
		time = 0;
		return 2 * speed;
	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		if (!time)
		{
			++time;
			return speed;
		}

		if (time < maxTime)
		{
			running = true;
		}else
			time = 0;
	}
	if(time != 0)
		++time;
	return speed;
}

//------------------------------------------------------------------
bool CreaturePlayer::isAttacking()
{
	if (currentAttack != NULL)
	{
		if (punch.AnimationFinished())
		{
			currentAttack = 0;
			playerState = IDLE;
			return false;
		}
		if (kick.AnimationFinished())
		{
			currentAttack = 0;
			playerState = IDLE;
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
SDL_Rect& CreaturePlayer::getAttack()
{
	switch (currentAttack)
	{
	case SDL_SCANCODE_COMMA: //Punch
		if (playerState == JUMPING)
			return jump;
		return punch.GetCurrentFrame();
		break;

	case SDL_SCANCODE_PERIOD: //Kick
		if (playerState == JUMPING)
			return kick_jump;
		return kick.GetCurrentFrame();
		break;
	}
}

//--------------------------------------------------------------------
bool CreaturePlayer::isJumping()
{
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || playerState == JUMPING)
	{
		playerState = JUMPING;
		Jump(position.x, position.y);
		//billy = jump;
		return true;
	}
	return false;
}
//--------------------------------------------------------------------
void CreaturePlayer::Jump(int& x, int& y)
{
	static int y_ini = -1;
	float aceleration = 0.3f;
	static float jumpspeed = 5;
	static bool jumpDirection[] = {false, false}; //right, left

	if (y_ini == -1)// Init
	{
		y_ini = y;
		--y;
		//isJumping = true;
		jumpspeed = 5;
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
		//isJumping = false;
		playerState = IDLE;
		jumpDirection[0] = false;
		jumpDirection[1] = false;
		currentAttack = 0;
	}
	else
	{
		jumpspeed -= aceleration;
		y -= jumpspeed;

		if (jumpDirection[0])
			x += 2;
		else if(jumpDirection[1])
			x -= 2;
	}
}


/*****************************************/
int CreaturePlayer::getCollision() //Return the type of collision (enemy attack, a wall,...)
{
	int ret;

	//for
	//creatureCollider

	return ret;
}