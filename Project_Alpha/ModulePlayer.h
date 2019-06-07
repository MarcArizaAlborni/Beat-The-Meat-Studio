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
	//Basic Movements
	backwardstateP1,
	forwardstateP1,
	idlestateP1,
	crouchstateP1,
	NjumpstateP1,
	FjumpstateP1,
	BjumpstateP1,

	//Attack
	standingfarLPP1,
	crouchLPP1,
	jumpLPP1,


};
struct InputP1 {
	// Poseu aqui un nou bool per algun input que no he posat.

	bool A_active; //Move Left
	bool D_active; //Move Right
	bool W_active; //Jump
	bool S_active; //Crouch

	bool U_active; //Light Punch LP
	bool X_active; //Medium Punch MP
	bool C_active; //Hard Punch Hp

	bool V_active; //Light Kick LK
	bool B_active; //Medium Kick MK
	bool N_active; //Hard Kick HK
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
	bool crouchBlocking = false;
	bool airkick = true;
	bool alreadyHit = false;
	bool flipP1 = false;
	float yvel = 12.0f;
	float gravity = 0.7f;
	uint time = 0;
	uint jumpTimer = 0;
	uint jumpstart;
	bool jumping = false;
	char combo[100];
	char* startC = new char();
	char* finishC = new char();
	SDL_Rect healthP1;
	SDL_Rect shadowP1;
	SDL_Texture* graphicsP1 = nullptr;
	//test
	Animation* currentP1_animation = nullptr;
	int font_score = -1;
	char score_text[10];
	uint score = 0;
	STATEP1 currentstateP1;

	//Basic Movements Animations
	Animation idleP1;        //Idle
	Animation forwardP1;     //Move Forward
	Animation backwardP1;    //Move Backward
	Animation crouchP1;      //Crouch
	Animation NjumpP1;	     //Neutral Jump
	Animation FjumpP1;       //Forward Jump
	Animation BjumpP1;       //Backward Jump
	Animation SturnP1;       //Standing Turn
	Animation CturnP1;       //Crouch Turn
	Animation SblockP1;      //Standing Block
	Animation CblockP1;      //Crouch Block
	Animation SdamageP1;     //Standing Damage 
	Animation SdamagelowP1;  //Standing Damage Low Attack
	Animation CdamageP1;     //Crouch Damage
	Animation ETdamgeP1;     //Electric Thunder Damage
	Animation RecoveryP1;    //Recovery After Damage

	//Attack Animations
	Animation SLFP_P1;       //Standing FAR LP (light punch) 
	Animation SLCP_P1;       //Standing CLOSE LP 
	Animation CLP_P1;        //Crouch LP
	Animation JLP_P1;        //Jumping LP
	Animation Ethunder_P1;   //Electric Thunder 
	Animation RollingP1;     //Rolling Attack

	iPoint positionP1;
	InputP1 inputplayerP1;

	void OnCollision(Collider* c1, Collider* c2);
	//Player2 Test collider
	Collider* playerP1_collider = nullptr;
	Collider* attackP1_collider = nullptr;
	Collider* blockP1_collider = nullptr;



	void comboInput(char comboInput);
	bool comboActive();
	
	int startcombo= 0;
	int endcombo = 0;
};



#endif