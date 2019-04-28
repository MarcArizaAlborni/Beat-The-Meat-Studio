#pragma once
#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
//#include "ModuleCollision.h"

struct SDL_Texture;
struct Collider;

enum STATE2 {

	backwardstate2,
	forwardstate2,
	idlestate2,
	crouchstate2,
	punchlight2,
	kicklight2,
	jumpstate2,
	hadoukenstate2,
	punchcrouch2,
	punchjump2,
	kickjump2,
	kickcrouch2,
	jumpforward2,
	jumpbackward2,
	damagedstate2,
	crouched2,
	jumpbackwardkick2,
	jumpbackwardpunch2,
	jumpforwardkick2,
	jumpforwardpunch2,
	jumpkickstate2,
	jumppunchstate2,
	jumpfalling2



};
struct InputP2 {
	// Poseu aqui un nou bool per algun input que no he posat.

	bool Right_active;//A_active
	bool Left_active; //D_active
	bool Up_active; //W_active
	bool Down_active; //S_active
	bool Punch2_active; //I_active
	bool Kick2_active; //K_active
	bool Special2_active; //R_active
};

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2();
	~ModulePlayer2();

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
	STATE2 currentstate;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation lightPunch;
	Animation lightKick;
	Animation jump;
	Animation hadouken2;
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


	iPoint position;
	InputP2 inputplayer2;
	  
	void OnCollision(Collider* c1, Collider* c2);

	//Player2 Test collider
	Collider* player2_collider = nullptr;
	Mix_Chunk* LP;
	Mix_Chunk* LK;
	Mix_Chunk* Hadoken_Sound;


};



#endif