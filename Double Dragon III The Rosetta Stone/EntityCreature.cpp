#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "src\pugixml.hpp"
#include "EntityCreature.h"
#include "SDL/include/SDL.h"
#include "src\pugixml.hpp"

#include "EntityManager.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"

EntityCreature::EntityCreature(creature_type type, bool start_enabled) : ModuleEntity(start_enabled)
{
	// Sounds
	deathSound = App->audio->LoadFx("resources/death.wav");

	// Textures
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("resources/data.xml");
	pugi::xml_node config = doc.document_element();
	pugi::xml_node entities = config.child("entities");
	pugi::xml_node creature;
	
	switch (type)
	{
	case PLAYER1:
		creature = entities.child("player1");
		creatureCollider = App->collision->AddCollider({ (int) position.x, (int) position.y - 64, 25, 64 }, (collider_type)PLAYER);
		break;
	case PLAYER2:
		creature = entities.child("player2");
		creatureCollider = App->collision->AddCollider({ (int)position.x, (int)position.y - 64, 25, 64 }, (collider_type)PLAYER);
		break;
	case ENEMY1:
		creature = entities.child("enemy1");
		creatureCollider = App->collision->AddCollider({ (int) position.x, (int) position.y - 64, 25, 64 }, (collider_type)ENEMY);
		break;
	case ENEMY2:
		creature = entities.child("enemy2");
		creatureCollider = App->collision->AddCollider({ (int) position.x, (int) position.y - 64, 25, 64 }, (collider_type)ENEMY);
		break;
	case BOSS:
		creature = entities.child("boss");
		creatureCollider = App->collision->AddCollider({ (int) position.x, (int) position.y - 64, 25, 64 }, (collider_type)ENEMY);
		break;
	}

	speed = creature.attribute("speed").as_int();
	damageAttack = creature.attribute("damage").as_int();
	life = creature.attribute("life").as_int();

	// Right & Down
	pugi::xml_node right_downXML = creature.child("right_down");
	right_down.frames.push_back(
	{
		right_downXML.child("frame1").attribute("x").as_int(),
		right_downXML.child("frame1").attribute("y").as_int(),
		right_downXML.child("frame1").attribute("w").as_int(),
		right_downXML.child("frame1").attribute("h").as_int()
	});
	right_down.frames.push_back(
	{
		right_downXML.child("frame2").attribute("x").as_int(),
		right_downXML.child("frame2").attribute("y").as_int(),
		right_downXML.child("frame2").attribute("w").as_int(),
		right_downXML.child("frame2").attribute("h").as_int()
	});
	right_down.frames.push_back(
	{
		right_downXML.child("frame3").attribute("x").as_int(),
		right_downXML.child("frame3").attribute("y").as_int(),
		right_downXML.child("frame3").attribute("w").as_int(),
		right_downXML.child("frame3").attribute("h").as_int()
	});
	right_down.frames.push_back(
	{
		right_downXML.child("frame4").attribute("x").as_int(),
		right_downXML.child("frame4").attribute("y").as_int(),
		right_downXML.child("frame4").attribute("w").as_int(),
		right_downXML.child("frame4").attribute("h").as_int()
	});

	right_down.speed = right_downXML.attribute("speed").as_float();

	// Up
	pugi::xml_node upXML = creature.child("up");
	up.frames.push_back(
	{
		upXML.child("frame1").attribute("x").as_int(),
		upXML.child("frame1").attribute("y").as_int(),
		upXML.child("frame1").attribute("w").as_int(),
		upXML.child("frame1").attribute("h").as_int()
	});
	up.frames.push_back(
	{
		upXML.child("frame2").attribute("x").as_int(),
		upXML.child("frame2").attribute("y").as_int(),
		upXML.child("frame2").attribute("w").as_int(),
		upXML.child("frame2").attribute("h").as_int()
	});
	up.frames.push_back(
	{
		upXML.child("frame3").attribute("x").as_int(),
		upXML.child("frame3").attribute("y").as_int(),
		upXML.child("frame3").attribute("w").as_int(),
		upXML.child("frame3").attribute("h").as_int()
	});
	up.frames.push_back(
	{
		upXML.child("frame4").attribute("x").as_int(),
		upXML.child("frame4").attribute("y").as_int(),
		upXML.child("frame4").attribute("w").as_int(),
		upXML.child("frame4").attribute("h").as_int()
	});

	up.speed = upXML.attribute("speed").as_float();

	// Jump
	pugi::xml_node jumpXML = creature.child("jump");
	jump =
	{
		jumpXML.attribute("x").as_int(),
		jumpXML.attribute("y").as_int(),
		jumpXML.attribute("w").as_int(),
		jumpXML.attribute("h").as_int()
	};

	// Punch
	pugi::xml_node punchXML = creature.child("punch");
	punch.frames.push_back(
	{
		punchXML.child("frame1").attribute("x").as_int(),
		punchXML.child("frame1").attribute("y").as_int(),
		punchXML.child("frame1").attribute("w").as_int(),
		punchXML.child("frame1").attribute("h").as_int()
	});
	punch.frames.push_back(
	{
		punchXML.child("frame2").attribute("x").as_int(),
		punchXML.child("frame2").attribute("y").as_int(),
		punchXML.child("frame2").attribute("w").as_int(),
		punchXML.child("frame2").attribute("h").as_int()
	});
	punch.frames.push_back(
	{
		punchXML.child("frame3").attribute("x").as_int(),
		punchXML.child("frame3").attribute("y").as_int(),
		punchXML.child("frame3").attribute("w").as_int(),
		punchXML.child("frame3").attribute("h").as_int()
	});
	punch.frames.push_back(
	{
		punchXML.child("frame4").attribute("x").as_int(),
		punchXML.child("frame4").attribute("y").as_int(),
		punchXML.child("frame4").attribute("w").as_int(),
		punchXML.child("frame4").attribute("h").as_int()
	});
	punch.frames.push_back(
	{
		punchXML.child("frame5").attribute("x").as_int(),
		punchXML.child("frame5").attribute("y").as_int(),
		punchXML.child("frame5").attribute("w").as_int(),
		punchXML.child("frame5").attribute("h").as_int()
	});

	punch.speed = punchXML.attribute("speed").as_float();

	// Kick
	pugi::xml_node kickXML = creature.child("kick");
	kick.frames.push_back(
	{
		kickXML.child("frame1").attribute("x").as_int(),
		kickXML.child("frame1").attribute("y").as_int(),
		kickXML.child("frame1").attribute("w").as_int(),
		kickXML.child("frame1").attribute("h").as_int()
	});
	kick.frames.push_back(
	{
		kickXML.child("frame2").attribute("x").as_int(),
		kickXML.child("frame2").attribute("y").as_int(),
		kickXML.child("frame2").attribute("w").as_int(),
		kickXML.child("frame2").attribute("h").as_int()
	});
	kick.frames.push_back(
	{
		kickXML.child("frame3").attribute("x").as_int(),
		kickXML.child("frame3").attribute("y").as_int(),
		kickXML.child("frame3").attribute("w").as_int(),
		kickXML.child("frame3").attribute("h").as_int()
	});
	kick.frames.push_back(
	{
		kickXML.child("frame4").attribute("x").as_int(),
		kickXML.child("frame4").attribute("y").as_int(),
		kickXML.child("frame4").attribute("w").as_int(),
		kickXML.child("frame4").attribute("h").as_int()
	});
	kick.frames.push_back(
	{
		kickXML.child("frame5").attribute("x").as_int(),
		kickXML.child("frame5").attribute("y").as_int(),
		kickXML.child("frame5").attribute("w").as_int(),
		kickXML.child("frame5").attribute("h").as_int()
	});

	kick.speed = kickXML.attribute("speed").as_float();

	// Kick jump
	pugi::xml_node kick_jumpXML = creature.child("kick_jump");
	kick_jump =
	{
		kick_jumpXML.attribute("x").as_int(),
		kick_jumpXML.attribute("y").as_int(),
		kick_jumpXML.attribute("w").as_int(),
		kick_jumpXML.attribute("h").as_int()
	};

	// Damaged
	pugi::xml_node damagedXML = creature.child("damaged");
	damaged =
	{
		damagedXML.attribute("x").as_int(),
		damagedXML.attribute("y").as_int(),
		damagedXML.attribute("w").as_int(),
		damagedXML.attribute("h").as_int()
	};

	// Damaged2
	pugi::xml_node damaged2XML = creature.child("damaged2");
	damaged2 =
	{
		damaged2XML.attribute("x").as_int(),
		damaged2XML.attribute("y").as_int(),
		damaged2XML.attribute("w").as_int(),
		damaged2XML.attribute("h").as_int()
	};

	// Fall
	pugi::xml_node fallXML = creature.child("fall");
	fall.frames.push_back(
	{
		fallXML.child("frame1").attribute("x").as_int(),
		fallXML.child("frame1").attribute("y").as_int(),
		fallXML.child("frame1").attribute("w").as_int(),
		fallXML.child("frame1").attribute("h").as_int()
	});
	fall.frames.push_back(
	{
		fallXML.child("frame2").attribute("x").as_int(),
		fallXML.child("frame2").attribute("y").as_int(),
		fallXML.child("frame2").attribute("w").as_int(),
		fallXML.child("frame2").attribute("h").as_int()
	});
	fall.frames.push_back(
	{
		fallXML.child("frame3").attribute("x").as_int(),
		fallXML.child("frame3").attribute("y").as_int(),
		fallXML.child("frame3").attribute("w").as_int(),
		fallXML.child("frame3").attribute("h").as_int()
	});

	fall.speed = fallXML.attribute("speed").as_float();
}

EntityCreature::~EntityCreature()
{}

/*********************************************************/
void EntityCreature::Die()
{
	if(deathSound != NULL)
		App->audio->PlayFx(deathSound);

	deathSound = NULL;

	creature_state = DEAD;
	creatureCollider->SetPos(-100, 0);

	if (App->time > 10 * 60 && type == Types::player) //10 seconds
		App->time = 10 * 60;
}