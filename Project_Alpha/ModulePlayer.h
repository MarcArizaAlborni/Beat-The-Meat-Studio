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

enum STATEP1 {

	backwardstateP1,
	forwardstateP1,
	idlestateP1,
	crouchstateP1,
	NjumpstateP1,
	FjumpstateP1,
	BjumpstateP1,

};
struct InputP1 {
	// Poseu aqui un nou bool per algun input que no he posat.

	bool A_active;
	bool D_active;
	bool W_active;
	bool S_active;

	bool left_active;
	bool right_active;
	bool up_active;
	bool down_active;
	bool Z_active;
	bool X_active;
	bool C_active;
	bool V_active;
	

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
	int speed = 3;
	Uint8 alphaka = 255;
	int groundLevel = 205;
	int maxHeight = 120;
	bool airkick = true;
	bool alreadyHit = false;
	float yvel = 12.0f;
	float gravity = 0.7f;
	uint time = 0;
	uint jumpTimer = 0;
	uint jumpstart;
	bool jumping = false;
	SDL_Rect healthP1;
	SDL_Rect shadowP1;
	SDL_Texture* graphicsP1 = nullptr;
	//test
	Animation* currentP1_animation = nullptr;
	int font_score = -1;
	char score_text[10];
	uint score = 0;
	STATEP1 currentstateP1;
	Animation idleP1;
	Animation forwardP1;
	Animation backwardP1;
	Animation crouchP1;
	Animation NjumpP1;
	Animation FjumpP1;
	Animation BjumpP1;
	iPoint positionP1;
	InputP1 inputplayerP1;

	void OnCollision(Collider* c1, Collider* c2);
	//Player2 Test collider
	Collider* playerP1_collider = nullptr;
	Collider* attackP1_collider = nullptr;
	Collider* blockP1_collider = nullptr;

};



#endif