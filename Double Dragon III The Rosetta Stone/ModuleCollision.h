#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#include<list>
#include "Module.h"

//struct SDL_Rect;


enum collider_type
{
	PLAYER = 0,
	ENEMY,
	EXIT,
	WALL_UP,
	WALL_DOWN,
	WALL_RIGHT,
	WALL_LEFT,
};
struct Collider
{
	SDL_Rect rect = { 0,0,0,0 };
	bool colliding = false;
	bool to_delete = false;

	collider_type type;
	/*bool collisionMatrix[4][4] = {
		{false, false, false}, //Player
		{false, false, false}, //Enemy
		{false, false, false}, //Wall
		{false, false, false} //Exit
	};*/
	bool collisionArray[6] = {false, false, false, false, false, false}; //Player, enemy, wall, exit

	Collider(SDL_Rect rectangle) : // expand this call if you need to
		rect(rectangle)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();

	bool CleanUp();

	Collider* AddCollider(const SDL_Rect& rect, const collider_type& type);
	void DebugDraw();

private:

	std::list<Collider*> colliders;
	bool debug = false;
};

#endif // __ModuleCollision_H__