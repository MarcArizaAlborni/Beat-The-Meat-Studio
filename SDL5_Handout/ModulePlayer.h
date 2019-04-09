#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
//#include "ModuleCollision.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation * current_animation = nullptr;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation lightPunch;
	Animation lightKick;
	Animation jump;
	Animation hadouken;
	iPoint position;
	Collider * player_collider = nullptr;
	void OnCollision(Collider* c1, Collider* c2);

};

#endif