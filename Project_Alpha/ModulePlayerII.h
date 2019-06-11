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
	standingfarLKP2,
	standingfarMKP2,
	standingfarHKP2,
	//Close Attacks
	standingcloseLPP2,
	standingcloseMPP2,
	standingcloseHPP2,
	standingcloseLKP2,
	standingcloseMKP2,
	standingcloseHKP2,
	//Crouch Attacks
	crouchLPP2,
	crouchMPP2,
	crouchHPP2,
	crouchLKP2,
	crouchMKP2,
	crouchHKP2,
	//Jumping attacks
	jumpLPP2,
	jumpMPP2,
	NjumpHPP2,
	DjumpHPP2,
	jumpLKP2,
	jumpMKP2,
	jumpHKP2,
	//Standing damaged
	SdamagedLP2,
	SdamagedMP2,
	SdamagedHP2,

	SdamagedP2,
	SblockstunP2,
	CblockstunP2,
	//COMBO
	thunder1P2,
	thunder2P2,
	throwP2,
	HeadbuttP2,
	rollingattackP2LIGHT,
	rollingattackP2MEDIUM,
	rollingattackP2HEAVY,
	dashforwardP2,
	dashBackwardP2,
	rollingreboundP2

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
	bool CalldelAtackP2 = false;
	bool delAtackP2 = false;
	Uint8 alphakaP2 = 255;
	int extradisP2 = 60;
	int speedP2 = 3;
	float camxP2, camyP2;
	int groundLevelP2 = 205;
	bool neutralJumpP2 = false;
	bool forwardJumpP2 = false;
	bool backwardJumpP2 = false;
	int maxHeightP2 = 120;
	bool closeP2 = false;
	bool SblockingP2 = false;
	bool CblockingP2 = false;
	bool airkickP2 = true;
	bool alreadyHitP2 = false;
	bool flipP2 = false;
	float yvelP2 = 12.5f;
	float gravityP2 = 0.72f;
	uint timeP2 = 0;
	uint jumpTimerP2 = 0;
	uint jumpstartP2;
	bool jumpingP2 = false;
	char comboP2[100];
	char* startCP2 = new char();
	char* finishCP2 = new char();
	SDL_Rect healthP2;
	SDL_Rect shadowP2;
	SDL_Texture* graphicsP2 = nullptr;
	//test
	Animation* currentP2_animation = nullptr;
	int thundertickP2 = 0;

	int font_scoreP2 = -1;
	char score_textP2[10];
	uint scoreP2 = 0;
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
	Animation SdamageLP2;    //Standing Damage L
	Animation SdamageMP2;    //Standing Damage M
	Animation SdamageHP2;    //Standing Damage H
	Animation SdamagelowLP2; //Standing Damage Low Attack Light
	Animation SdamagelowMP2; //Standing Damage Low Attack Medium
	Animation SdamagelowHP2; //Standing Damage Low Attacl Hard
	Animation CdamageP2;     //Crouch Damage
	Animation ETdamgeP2;     //Electric Thunder Damage
	Animation RecoveryP2;    //Recovery After Damage

	//Attack Animations
	Animation SFLP_P2;       //Standing FAR LP (light punch) 
	Animation SCLP_P2;       //Standing CLOSE LP 
	Animation CLP_P2;        //Crouch LP
	Animation JLP_P2;        //Jumping LP

	Animation SFMP_P2;       //Standing FAR MP (medium punch) 
	Animation SCMP_P2;       //Standing CLOSE MP 
	Animation CMP_P2;        //Crouch MP
	Animation JMP_P2;        //Jumping MP

	Animation SFHP_P2;       //Standing FAR HP (hard punch) 
	Animation SCHP_P2;       //Standing CLOSE HP 
	Animation CHP_P2;        //Crouch HP
	Animation JHPFB_P2;      //Jumping HP F and B
	Animation JHPN_P2;       //Jumping HP Neutral

	Animation SFLK_P2;       //Standing FAR LK (light kick) 
	Animation SCLK_P2;       //Standing CLOSE LK
	Animation CLK_P2;        //Crouch LK
	Animation JLK_P2;        //Jumping LK

	Animation SFMK_P2;       //Standing FAR MK (medium kick) 
	Animation SCMK_P2;       //Standing CLOSE MK
	Animation CMK_P2;        //Crouch MK
	Animation JMK_P2;        //Jumping MK

	Animation SFHK_P2;       //Standing FAR HK (hard kick) 
	Animation SCHK_P2;       //Standing CLOSE HK
	Animation CHK_P2;        //Crouch HK
	Animation JHK_P2;        //Jumping HK

	Animation Headbut_P2;    //Heatbut
	Animation Throw_P2;      //Throw
	Animation Ethunder_P2;   //Electric Thunder 
	Animation RollingP2;     //Rolling Attack (Light)
	Animation RollingRebP2;  //Rolling Rebot

	iPoint positionP2;
	InputP2 inputplayerP2;
	  
	void OnCollision(Collider* c1, Collider* c2);
	//Player2 Test collider
	Collider* playerP2_collider = nullptr;
	Collider* attackP2_collider = nullptr;
	Collider* blockP2_collider = nullptr;

	void comboInputP2(char comboInput);
	bool comboActiveP2();

	int startcomboP2 = 0;
	int endcomboP2 = 0;
	
	//Effects

	Mix_Chunk* L_attack_sound_P2;
	Mix_Chunk* M_attack_sound_P2;
	Mix_Chunk* H_attack_sound_P2;
	Mix_Chunk* L_hit_sound_P2;
	Mix_Chunk* M_hit_sound_P2;
	Mix_Chunk* H_hit_sound_P2;
	Mix_Chunk* Block_sound_P2;
	Mix_Chunk* Terra_sound_P2;

};





#endif