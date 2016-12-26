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


EntityCreature::EntityCreature(creature_type type, bool start_enabled) : ModuleEntity(start_enabled)
{
	position.x = 100;
	position.y = 216;
	speed = 1;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data.xml");
	pugi::xml_node config = doc.document_element();
	pugi::xml_node entities = config.child("entities");
	pugi::xml_node creature;

	switch (type)
	{
	case PLAYER:
		creature = entities.child("player1");
		creatureCollider = App->collision->AddCollider({ position.x, position.y - 64, 70, 64 }, (collider_type)PLAYER);
		break;
	case ENEMY1:
		creature = entities.child("enemy1");
		creatureCollider = App->collision->AddCollider({ position.x, position.y - 64, 70, 64 }, (collider_type)ENEMY);
		break;
	case ENEMY2:
		creature = entities.child("enemy2");
		creatureCollider = App->collision->AddCollider({ position.x, position.y - 64, 70, 64 }, (collider_type)ENEMY);
		break;
	case BOSS:
		creature = entities.child("boss");
		creatureCollider = App->collision->AddCollider({ position.x, position.y - 64, 70, 64 }, (collider_type)ENEMY);
		break;
	}

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

}

EntityCreature::~EntityCreature()
{}