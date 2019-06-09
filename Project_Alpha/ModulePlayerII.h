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
	//Basic Movements
	backwardstateP2,
	forwardstateP2,
	idlestateP2,
	crouchstateP2,
	NjumpstateP2,
	FjumpstateP2,
	BjumpstateP2,

	//Attack
	standingfarLPP2,
	standingfarMPP2,
	standingfarHPP2,
	crouchLPP2,
	jumpLPP2,

};
struct InputP2 {
	// Poseu aqui un nou bool per algun input que no he posat.

	bool Right_active;//A_active
	bool Left_active; //D_active
	bool Up_active; //W_active
	bool Down_active; //S_active

	bool Num7_active; //Light Punch LP
	bool Num8_active; //Medium Punch MP
	bool Num9_active; //Hard Punch Hp

	bool Num4_active; //Light Kick LK
	bool Num5_active; //Medium Kick MK
	bool Num6_active; //Hard Kick HK

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
	int speedII = 3;
	Uint8 alphakaII = 255;
	int groundLevelII = 205;
	int maxHeightII = 120;
	bool airkickII = true;
	bool alreadyHit2 = false;
	float yvel2 = 12.0f;
	float gravity2 = 0.7f;
	uint time2 = 0;
	uint jumpTimer2 = 0;
	uint jumpstart2;
	bool jumping2 = false;
	SDL_Rect healthP2;
	SDL_Rect shadowP2;
	SDL_Texture* graphicsP2 = nullptr;
	//test
	Animation* currentP2_animation = nullptr;
	int font_score = -1;
	char score_text[10];
	uint score = 0;
	STATEP2 currentstateP2;

	//Basic Movements Animations
	Animation idleP2;        //Idle
	Animation forwardP2;     //Move Forward
	Animation backwardP2;    //Move Backward
	Animation crouchP2;      //Crouch
	Animation NjumpP2;	     //Neutral Jump
	Animation FjumpP2;       //Forward Jump
	Animation BjumpP2;       //Backward Jump
	Animation SturnP2;       //Standing Turn
	Animation CturnP2;       //Crouch Turn
	Animation SblockP2;      //Standing Block
	Animation CblockP2;      //Crouch Block
	Animation SdamageP2;     //Standing Damage 
	Animation SdamagelowP2;  //Standing Damage Low Attack
	Animation CdamageP2;     //Crouch Damage
	Animation ETdamgeP2;     //Electric Thunder Damage
	Animation RecoveryP2;    //Recovery After Damage

	//Attack Animations
	Animation SLFP_P2;        //Standing LP (light punch) 
	Animation SFMP_P2;
	Animation SFHP_P2;
	Animation CLP_P2;        //Crouch LP
	Animation SLCP_P2;       //Standing CLOSE LP 
	Animation JLP_P2;        //Jumping LP
	Animation Ethunder_P2;   //Electric Thunder 
	Animation RollingP2;     //Rolling Attack

	iPoint positionP2;
	InputP2 inputplayerP2;
	  
	void OnCollision(Collider* c1, Collider* c2);
	//Player2 Test collider
	Collider* playerP2_collider = nullptr;
	Collider* attackP2_collider = nullptr;
	Collider* blockP2_collider = nullptr;

};





#endif