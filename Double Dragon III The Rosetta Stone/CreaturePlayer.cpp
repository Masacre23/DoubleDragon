#include "Globals.h"
#include "Application.h"
#include "CreaturePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "src\pugixml.hpp"
#include "CreatureEnemy.h"
#include "EntityManager.h"
#include "ModuleWindow.h"
#include "ModuleAudio.h"

CreaturePlayer::CreaturePlayer(creature_type playertype, bool start_enabled) : EntityCreature(playertype, start_enabled)
{
	// Sounds
	punchSound = App->audio->LoadFx("player_punch.wav");
	kickSound = App->audio->LoadFx("player_kick.wav");

	// Controls
	if (playertype == PLAYER1)
	{
		for(int i = 0; i < 7; ++i)
		controlsplayer[i] = controlsplayer1[i];
	}
	else
	{
		for (int i = 0; i < 7; ++i)
			controlsplayer[i] = controlsplayer2[i];
	}

	// Textures
	position.x = 120;
	position.y = 216;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data.xml");
	pugi::xml_node config = doc.document_element();
	pugi::xml_node entities = config.child("entities");
	pugi::xml_node player;
	if(playertype == PLAYER1)
		player = entities.child("player1");	
	else
		player = entities.child("player2");

	// Rotate kick jump
	pugi::xml_node rotate_kick_jumpXML = player.child("rotate_kick_jump");
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

	// Butting
	pugi::xml_node buttingXML = player.child("head_butt");
	head_butt =
	{
		buttingXML.attribute("x").as_int(),
		buttingXML.attribute("y").as_int(),
		buttingXML.attribute("w").as_int(),
		buttingXML.attribute("h").as_int()
	};

}

CreaturePlayer::~CreaturePlayer()
{}

// Load assets
bool CreaturePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("Genesis 32X SCD - Double Dragon III The Rosetta Stone - Billy & Jimmy2.png");

	creature_state = IDLE;

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

	//static SDL_Rect billy = right_down.frames[0];
	//static bool flip = false; // When the character goes left is true
	newSpeed = getSpeed();
	//static int counter = 0;
	//static int damageReaction = 0;

	if (life <= 0)
	{
		Die();
	}

	switch (creature_state)
	{
	case ATTACKING:
		if (!isAttacking())
			break;
		billy = getAttack();
		break;
	case JUMPING:
		Jump();
		if (isAttacking())
		{
			billy = getAttack();
			break;
		}
		if (falling)
			billy = fall.frames[0];
		else
			billy = jump;
		break;
	case DAMAGED:
		++counter;
		if (counter < 30)
		{
			switch (damage_reaction)
			{
			case 0:
				billy = damaged;
				break;
			case 1:
				billy = damaged2;
				break;
			case 2:
				counter = 0;
				if (fall.AnimationFinished())
				{
					creature_state = IDLE;
					invulnerability = true;
					damage_reaction = rand() % 3;
					billy = right_down.GetCurrentFrame();
				}
				else
					billy = fall.GetCurrentFrame();
				break;
			}
		}
		else
		{
			creature_state = IDLE;
			counter = 0;
			invulnerability = true;
			damage_reaction = rand() % 3;
		}
		break;
	case DEAD:
		if (fall.AnimationHalf())
		{
			break;
		}
		billy = fall.GetCurrentFrame();
		break;
	case IDLE:
		billy = right_down.frames[right_down.current_frame];
	default:
		if (isAttacking())
		{
			creature_state = ATTACKING;
			break;
		}
		if (isJumping())
		{
			Jump();
			break;
		}
		if (App->input->GetKey(controlsplayer[3]) == KEY_REPEAT)
		{
			flip = false;
			if (!creatureCollider->collisionArray[collider_type::WALL_RIGHT])
				position.x += newSpeed;
			billy = right_down.GetCurrentFrame();
		}
		else if (App->input->GetKey(controlsplayer[1]) == KEY_REPEAT)
		{
			flip = true;
			if (position.x > -App->renderer->camera.x / SCREEN_SIZE - 25) //25 is number of pixels
			{
				if (!creatureCollider->collisionArray[collider_type::WALL_LEFT])
					position.x -= newSpeed;
			}
			billy = right_down.GetCurrentFrame();
		}

		if (App->input->GetKey(controlsplayer[0]) == KEY_REPEAT)
		{
			if (!creatureCollider->collisionArray[collider_type::WALL_UP])
				position.y -= speed;
			billy = up.GetCurrentFrame();
		}
		else if (App->input->GetKey(controlsplayer[2]) == KEY_REPEAT)
		{
			if (!creatureCollider->collisionArray[collider_type::WALL_DOWN])
				position.y += speed;
			billy = right_down.GetCurrentFrame();
		}
		break;
	}
	
	UpdateCamera();

	creatureCollider->SetPos(position.x + 25, position.y - 64);
	static bool b = false;
	if (invulnerability)
	{
		++counter;
		if (counter >= 60) // 1 seconds
		{
			invulnerability = false;
			counter = 0;
		}
		if (counter % (5) == 0) // 0.25 seconds
			b = !b;

		if(b)
			App->renderer->Blit(graphics, position.x + speed, position.y - billy.h, &(billy), 1.0f, flip);
	}
	else
		App->renderer->Blit(graphics, position.x + speed, position.y - billy.h, &(billy), 1.0f, flip);
	return UPDATE_CONTINUE;
}

/**************************************************************/
int CreaturePlayer::getSpeed()
{
	//static bool walking = false;
	//static int time = 0;
	//static int maxTime = 24; 

	if (running)
	{
		if (App->input->GetKey(controlsplayer[3]) == KEY_UP || App->input->GetKey(controlsplayer[1]) == KEY_UP)
		{
			running = false;
			return speed;
		}
		return speed * 2;
	}
	if (App->input->GetKey(controlsplayer[3]) == KEY_DOWN || App->input->GetKey(controlsplayer[1]) == KEY_DOWN)
	{
		if (walking && time < maxTime)
		{
			running = true;
			walking = false;
			time = 0;
			return speed * 2;
		}
		else
		{
			walking = true;
			time = 0;
		}
	}
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
			creature_state = IDLE;
			return false;
		}
		if (kick.AnimationFinished())
		{
			currentAttack = 0;
			creature_state = IDLE;
			return false;
		}

		if (rotate_kick_jump.AnimationFinished())
		{
			currentAttack = 0;
			creature_state = IDLE;
			return false;
		}

		return true;
	}
	else
	{
		if (App->input->GetKey(controlsplayer[4]) == KEY_DOWN)
		{
			currentAttack = controlsplayer[4];
			if (running)
				isButting = true;
		}
		else if (App->input->GetKey(controlsplayer[5]) == KEY_DOWN)
		{
			currentAttack = controlsplayer[5];
			//if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
				//currentAttack = 1; //Rotate kick jump
		}
		return false;
	}
		
}

//-------------------------------------------------------------------
SDL_Rect& CreaturePlayer::getAttack()
{
	switch (currentAttack)
	{
	case 1: //Rotate kick jump
		/*if (rotate_kick_jump.AnimationHalf())
			position.y += 5;
		else
			position.y -= 5;*/
		return rotate_kick_jump.GetCurrentFrame();
		break;

	case SDL_SCANCODE_N: //Punch
	case SDL_SCANCODE_KP_2:
		if (creature_state == JUMPING)
			return jump;
		if (isButting)
		{
			HeadButt();
			doDamage();
			return head_butt;
		}
		if (punch.AnimationHalf())
			doDamage();
		return punch.GetCurrentFrame();
		break;

	case SDL_SCANCODE_M: //Kick
	case SDL_SCANCODE_KP_3:
		if (creature_state == JUMPING)
		{
			doDamage();
			return kick_jump;
		}
		if (kick.AnimationHalf())
			doDamage();
		return kick.GetCurrentFrame();
		break;
	}
}

//--------------------------------------------------------------------
bool CreaturePlayer::isJumping()
{
	if (App->input->GetKey(controlsplayer[6]) == KEY_DOWN || creature_state == JUMPING)
	{
		creature_state = JUMPING;
		return true;
	}
	return false;
}
//--------------------------------------------------------------------
void CreaturePlayer::Jump()
{
	//static int y_ini = -1;
	float aceleration = 0.3f;
	//static float jump_speed = 5;
	//static bool jumpDirection[] = {false, false}; //right, left

	if (y_ini == -1)// Init
	{
		y_ini = position.y;
		creature_state = JUMPING;
		position.y -= 1;
		jump_speed = 5;
		if (App->input->GetKey(controlsplayer[3]) == KEY_REPEAT)
		{
			jumpDirection[0] = true;
		}
		if (App->input->GetKey(controlsplayer[1]) == KEY_REPEAT)
		{
			jumpDirection[1] = true;
		}
	}
	else if (y_ini <= position.y) 
	{
		position.y = y_ini;
		y_ini = -1;
		creature_state = IDLE;
		jumpDirection[0] = false;
		jumpDirection[1] = false;
		currentAttack = 0;
		if (falling)
		{
			damage_reaction = 2;
			creature_state = DAMAGED;
			falling = false;
			fall.GetCurrentFrame();
		}
	}
	else
	{
		jump_speed -= aceleration;
		position.y -= jump_speed;

		if (jumpDirection[0])
		{
			if(falling)
				position.x -= 2;
			else
				position.x += 2;
		}
		else if (jumpDirection[1])
		{
			if(falling)
				position.x += 2;
			else
				position.x -= 2;
		}
	}
}
/*****************************************/
void CreaturePlayer::HeadButt()
{
	//static bool isButting = false;
	//static int y_ini = -1;
	float aceleration = 0.5f;
	//static float jump_speed = 5;
	//static bool jumpDirection[] = { false, false }; //right, left
	running = false;
	if (y_ini == -1)
	{
		y_ini = position.y;
		--position.y;
		jump_speed = 5;
		running = false;
		isButting = true;
		if (App->input->GetKey(controlsplayer[3]) == KEY_REPEAT)
		{
			jumpDirection[0] = true;
		}
		if (App->input->GetKey(controlsplayer[1]) == KEY_REPEAT)
		{
			jumpDirection[1] = true;
		}

	}else if (y_ini <= position.y)
	{
		creature_state = IDLE;
		isButting = false;
		running = false;
		jumpDirection[0] = false;
		jumpDirection[1] = false;
		currentAttack = 0;
		position.y = y_ini;
		y_ini = -1;
	}
	else
	{
		jump_speed -= aceleration;
		position.y -= jump_speed;

		if (jumpDirection[0])
			position.x += 3;
		else if (jumpDirection[1])
			position.x -= 3;
	}

}

/*****************************************/
void CreaturePlayer::doDamage()
{
	//if (creatureCollider->collisionMatrix[0][1])
	bool activateSound = false;
	if (creatureCollider->collisionArray[1])
	{
		for (list<ModuleEntity*>::iterator it = App->entityManager->entities.begin(); it != App->entityManager->entities.end(); ++it)
		{
			if ((*it)->type == enemy && (*it)->position.DistanceTo(position) < 20)
			{
				CreatureEnemy* e = (CreatureEnemy*)(*it);
				if (e->creature_state != DEAD && e->creature_state != DAMAGED && ((flip && position.x > e->position.x) || (flip == false && position.x < e->position.x)))
				{
					e->creature_state = DAMAGED;
					e->life -= damageAttack;
					activateSound = true;
				}
			}
		}
	}

	if (activateSound)
	{
		switch (currentAttack)
		{
		case SDL_SCANCODE_N: //Punch
		case SDL_SCANCODE_KP_2:
			App->audio->PlayFx(punchSound);
			break;

		case SDL_SCANCODE_M: // Kick
		case SDL_SCANCODE_KP_3:
			App->audio->PlayFx(kickSound);
			break;
		}
	}
}

/**************************************/
void CreaturePlayer::UpdateCamera()
{
	/*std::string tmp = "PLAYER: " + std::to_string(position.x);
	char tab1[1024];
	strcpy(tab1, tmp.c_str());
	LOG(tab1);

	tmp = "CAMERA: " + std::to_string(App->renderer->camera.x);
	char tab2[1024];
	strcpy(tab2, tmp.c_str());
	LOG(tab2);*/

	if (position.x*SCREEN_SIZE + App->renderer->camera.x > 3*SCREEN_WIDTH/ SCREEN_SIZE)
	{
		App->renderer->camera.x -= speed * SCREEN_SIZE;
		App->window->center_window_x += speed;
	}

	if (position.x*SCREEN_SIZE + App->renderer->camera.x < SCREEN_WIDTH / (10*SCREEN_SIZE))
	{
		App->renderer->camera.x += speed * SCREEN_SIZE;
		App->window->center_window_x -= speed;
	}
}