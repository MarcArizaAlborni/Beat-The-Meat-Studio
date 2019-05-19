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

enum STATEP2 {

	backwardstateP2,
	forwardstateP2,
	idlestateP2,
	crouchstateP2,

};
struct InputP2 {
	// Poseu aqui un nou bool per algun input que no he posat.

	bool Right_active;//A_active
	bool Left_active; //D_active
	bool Up_active; //W_active
	bool Down_active; //S_active
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

	SDL_Rect healthP2;
	SDL_Rect shadowP2;
	SDL_Texture* graphicsP2 = nullptr;
	//test
	Animation* currentP2_animation = nullptr;
	int font_score = -1;
	char score_text[10];
	uint score = 0;
	STATEP2 currentstateP2;
	Animation idleP2;
	Animation forwardP2;
	Animation backwardP2;
	Animation crouchP2;
	Animation NjumpP2;
	Animation FjumpP2;
	Animation BjumpP2;
	iPoint positionP2;
	InputP2 inputplayerP2;
	  
	void OnCollision(Collider* c1, Collider* c2);
	//Player2 Test collider
	Collider* playerP2_collider = nullptr;
	Collider* attackP2_collider = nullptr;
	Collider* blockP2_collider = nullptr;

};



#endif