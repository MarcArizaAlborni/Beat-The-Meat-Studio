#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
//#include "ModuleCollision.h"

struct SDL_Texture;
struct Collider;

enum STATE {

	backwardstate,
	forwardstate,
	idlestate,
	crouchstate,
	punchlight,
	kicklight,
	jumpstate,
	hadoukenstate,
	punchcrouch,
	punchjump,
	kickjump,
	kickcrouch,
	jumpforward,
	jumpbackward,
	damagedstate,
	crouched,
	jumpbackwardkick,
	jumpbackwardpunch,
	jumpforwardkick,
	jumpforwardpunch,
	jumpkickstate,
	jumppunchstate,
	jumpfalling,
	croucheddamaged



};
struct InputP1 {
	// Poseu aqui un nou bool per algun input que no he posat.

	bool A_active;
	bool D_active;
	bool W_active;
	bool S_active;
	bool Punch1_active;
	bool Kick1_active;
	bool Special1_active;
};

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	update_status PreUpdate();

public:

	SDL_Rect health;
	SDL_Texture* graphics = nullptr;
	Animation * current_animation = nullptr;
	int font_score = -1;
	char score_text[10];
	uint score = 0;
	STATE currentstate;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation lightPunch;
	Animation lightKick;
	Animation jump;
	Animation hadouken;
	Animation crouchpunch;
	Animation crouchkick;
	Animation jumppunch;
	Animation jumpkick;
	Animation damaged;
	Animation forwardjump;
	Animation backwardjump;
	Animation crouch;
	Animation jumpbackkick;
	Animation jumpbackpunch;
	Animation jumpfrontkick;
	Animation jumpfrontpunch;
	Animation croucheddamaged;
	
	
	iPoint position;
	InputP1 inputplayer1;
	Collider* player_collider = nullptr;
	void OnCollision(Collider* c1, Collider* c2);
	Mix_Chunk* LightDamage_Sound;;
	Mix_Chunk* Hadoken_Sound;

	//test attacks
	Collider* attack_collider = nullptr;

};



#endif