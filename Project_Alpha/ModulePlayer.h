#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Globals.h"
#include "ModuleParticles.h"

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
	standingfarMPP1,
	standingfarHPP1, 
	standingfarLKP1,
	standingfarMKP1,
	standingfarHKP1,
	//Close Attacks
	standingcloseLPP1,
	standingcloseMPP1,
	standingcloseHPP1,
	standingcloseLKP1,
	standingcloseMKP1,
	standingcloseHKP1,
	//Crouch Attacks
	crouchLPP1,
	crouchMPP1,
	crouchHPP1,
	crouchLKP1,
	crouchMKP1,
	crouchHKP1,
	//Jumping attacks
	jumpLPP1,
	jumpMPP1,
	NjumpHPP1,
	DjumpHPP1,
	jumpLKP1,
	jumpMKP1,
	jumpHKP1,
	//Standing damaged
	SdamagedLP1,
	SdamagedMP1,
	SdamagedHP1,
	
	SdamagedP1,
	SblockstunP1,

	//COMBO
	thunder1P1,
	thunder2P1,
	throwP1,
	HeadbuttP1,
	rollingattackP1LIGHT,
	rollingattackP1MEDIUM,
	rollingattackP1HEAVY,
	dashforwardP1,
	dashBackwardP1,
	rollingreboundP1

};
struct InputP1 {
	// Poseu aqui un nou bool per algun input que no he posat.

	bool A_active; //Move Left
	bool D_active; //Move Right
	bool W_active; //Jump
	bool S_active; //Crouch

	bool U_active; //Light Punch LP
	bool I_active; //Medium Punch MP
	bool O_active; //Hard Punch Hp

	bool J_active; //Light Kick LK
	bool K_active; //Medium Kick MK
	bool L_active; //Hard Kick HK
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
	bool CalldelAtackP1 = false;
	bool delAtackP1 = false;
	Uint8 alphakaP1 = 255;
	int extradisP1 = 40;
	int speedP1 = 3;
	float camxP1, camyP1;
	int groundLevelP1 = 205;
	bool neutralJumpP1 = false;
	bool forwardJumpP1 = false;
	bool backwardJumpP1 = false;
	int maxHeightP1 = 120;
	bool closeP1 = false;
	bool SblockingP1 = false;
	bool CblockingP1 = false;
	bool airkickP1 = true;
	bool alreadyHitP1 = false;
	bool flipP1 = false;
	float yvelP1 = 12.5f;
	float gravityP1 = 0.72f;
	uint timeP1 = 0;
	uint jumpTimerP1 = 0;
	uint jumpstartP1;
	bool jumpingP1 = false;
	char comboP1[100];
	char* startCP1 = new char();
	char* finishCP1 = new char();
	SDL_Rect healthP1;
	SDL_Rect shadowP1;
	SDL_Texture* graphicsP1 = nullptr;
	//test
	Animation* currentP1_animation = nullptr;
	int thundertickP1 = 0;
	
	int font_scoreP1 = -1;
	char score_textP1[10];
	uint scoreP1 = 0;
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
	Animation SdamageLP1;    //Standing Damage L
	Animation SdamageMP1;    //Standing Damage M
	Animation SdamageHP1;    //Standing Damage H
	Animation SdamagelowLP1; //Standing Damage Low Attack Light
	Animation SdamagelowMP1; //Standing Damage Low Attack Medium
	Animation SdamagelowHP1; //Standing Damage Low Attacl Hard
	Animation CdamageLP1;    //Crouch Damage L
	Animation CdamageMP1;    //Crouch Damage M
	Animation CdamageHP1;    //Crouch Damage H
	Animation ETdamgeP1;     //Electric Thunder Damage
	Animation JdamageP1;     //Jumping Damage
	Animation DeathP1;
	Animation Victory1P1;
	Animation Victory2P1;

	//Attack Animations
	Animation SFLP_P1;       //Standing FAR LP (light punch) 
	Animation SCLP_P1;       //Standing CLOSE LP 
	Animation CLP_P1;        //Crouch LP
	Animation JLP_P1;        //Jumping LP

	Animation SFMP_P1;       //Standing FAR MP (medium punch) 
	Animation SCMP_P1;       //Standing CLOSE MP 
	Animation CMP_P1;        //Crouch MP
	Animation JMP_P1;        //Jumping MP

	Animation SFHP_P1;       //Standing FAR HP (hard punch) 
	Animation SCHP_P1;       //Standing CLOSE HP 
	Animation CHP_P1;        //Crouch HP
	Animation JHPFB_P1;      //Jumping HP F and B
	Animation JHPN_P1;       //Jumping HP Neutral

	Animation SFLK_P1;       //Standing FAR LK (light kick) 
	Animation SCLK_P1;       //Standing CLOSE LK
	Animation CLK_P1;        //Crouch LK
	Animation JLK_P1;        //Jumping LK

	Animation SFMK_P1;       //Standing FAR MK (medium kick) 
	Animation SCMK_P1;       //Standing CLOSE MK
	Animation CMK_P1;        //Crouch MK
	Animation JMK_P1;        //Jumping MK

	Animation SFHK_P1;       //Standing FAR HK (hard kick) 
	Animation SCHK_P1;       //Standing CLOSE HK
	Animation CHK_P1;        //Crouch HK
	Animation JHK_P1;        //Jumping HK

	Animation Headbut_P1;    //Heatbut
	Animation Throw_P1;      //Throw
	Animation Ethunder_P1;   //Electric Thunder 
	Animation RollingP1;     //Rolling Attack (Light)
	Animation RollingRebP1;  //Rolling Rebot

	iPoint positionP1;
	InputP1 inputplayerP1;

	void OnCollision(Collider* c1, Collider* c2);
	//Player2 Test collider
	Collider* playerP1_collider = nullptr;
	Collider* attackP1_collider = nullptr;
	Collider* blockP1_collider = nullptr;

	uint windup = 0;

	int attackstarttime = 0;

	bool attackActive = false;
	void attackTime( uint windUp, int x, int y, ATTACK_TYPE attackTtype);
		
		
	void comboInputP1(char comboInput);
	bool comboActiveP1();
	
	int startcomboP1 = 0;
	int endcomboP1 = 0;
};






#endif