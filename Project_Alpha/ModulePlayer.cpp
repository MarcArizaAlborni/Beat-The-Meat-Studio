#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "Animation.h"
#include "ModuleFonts.h"
#include "ModuleCollision.h"
#include "ModuleSceneRyu.h"
#include "ModulePlayerII.h"
#include <stdio.h>
#include <iostream>



// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA


using namespace std;
void deleteCollider(Collider* coll) {
	if (coll != nullptr) { coll->to_delete = true; };
}

ModulePlayer::ModulePlayer()
{
	graphicsP1 = NULL;
	currentP1_animation = NULL;



	score = 0;

	healthP1.x = 100;
	healthP1.y = 400;
	healthP1.w = 200;
	healthP1.h = 20;

	{ //BASIC MOVEMENTS ANIMATIONS

		//Idle animation (arcade sprite sheet)
		idleP1.PushBack({ 28, 27, 105, 100 });
		idleP1.PushBack({ 133, 27, 100, 100 });
		idleP1.PushBack({ 233, 27, 100, 100 });
		idleP1.speed = 0.08f;

		//Walk FORWARD Animation
		forwardP1.PushBack({ 699, 127, 97, 84 });
		forwardP1.PushBack({ 232, 127, 90, 84 });
		forwardP1.PushBack({ 322, 127, 100, 84 });
		forwardP1.PushBack({ 422, 127, 100, 84 });
		forwardP1.PushBack({ 522, 127, 88, 84 });
		forwardP1.PushBack({ 609, 127, 90, 84 });
		forwardP1.PushBack({ 132, 127, 100, 84 });
		forwardP1.PushBack({ 29, 127, 105, 84 });
		forwardP1.loop = true;
		forwardP1.speed = 0.1f;

		//Walk backwards animation
		backwardP1.PushBack({ 694, 211, 101, 101 });
		backwardP1.PushBack({ 609, 211, 85, 101 });
		backwardP1.PushBack({ 522, 211, 87, 101 });
		backwardP1.PushBack({ 232, 211, 91, 101 });
		backwardP1.PushBack({ 322, 211, 105, 101 });
		backwardP1.PushBack({ 427, 211, 95, 101 });
		backwardP1.PushBack({ 132, 211, 100, 101 });
		backwardP1.PushBack({ 29, 211, 104, 101 });
		backwardP1.loop = true;
		backwardP1.speed = 0.1f;

		//Crouch Animation
		crouchP1.PushBack({ 427, 323, 99, 94 });
		crouchP1.PushBack({ 526, 323, 89, 94 });
		crouchP1.PushBack({ 615, 323, 93, 94 });
		crouchP1.speed = 0.5f;
		crouchP1.loop = false;

		//Neutral Jump Animation
		NjumpP1.PushBack({ 28, 525, 97, 128 });
		NjumpP1.PushBack({ 125, 525, 85, 128 });
		NjumpP1.PushBack({ 210, 525, 83, 128 });
		NjumpP1.PushBack({ 293, 525, 86, 128 });
		NjumpP1.PushBack({ 210, 525, 83, 128 });
		NjumpP1.PushBack({ 125, 525, 85, 128 });
		NjumpP1.PushBack({ 28, 525, 97, 128 });
		NjumpP1.speed = 0.1f;
		NjumpP1.loop = false;

		//Forward Jump Animation
		FjumpP1.PushBack({ 28, 525, 97, 128 });
		FjumpP1.PushBack({ 125, 525, 85, 128 });
		FjumpP1.PushBack({ 210, 525, 83, 128 });
		FjumpP1.PushBack({ 293, 525, 86, 128 });
		FjumpP1.PushBack({ 379, 525, 90, 128 });
		FjumpP1.PushBack({ 469, 525, 98, 128 });
		FjumpP1.PushBack({ 567, 525, 119, 128 });
		FjumpP1.PushBack({ 686, 525, 96, 128 });
		FjumpP1.PushBack({ 379, 525, 90, 128 });
		FjumpP1.PushBack({ 293, 525, 86, 128 });
		FjumpP1.speed = 0.17f;
		FjumpP1.loop = false;

		//Backward Jump Animation
		BjumpP1.PushBack({ 28, 525, 97, 128 });
		BjumpP1.PushBack({ 125, 525, 85, 128 });
		BjumpP1.PushBack({ 210, 525, 83, 128 });
		BjumpP1.PushBack({ 293, 525, 86, 128 });
		BjumpP1.PushBack({ 210, 525, 83, 128 });
		BjumpP1.PushBack({ 125, 525, 85, 128 });
		BjumpP1.PushBack({ 28, 525, 97, 128 });
		BjumpP1.speed = 0.17f;
		BjumpP1.loop = false;

		//Standing Turn Animation
		SturnP1.PushBack({ 36, 418, 89, 105 });
		SturnP1.PushBack({ 125, 418, 103, 105 });
		SturnP1.PushBack({ 228, 418, 97, 105 });

		//Crouch Turn Animation
		CturnP1.PushBack({ 622, 451, 82, 71 });
		CturnP1.PushBack({ 516, 451, 106, 71 });
		CturnP1.PushBack({ 428, 451, 88, 71 });

		//Standing Block Animation
		SblockP1.PushBack({ 730, 2169, 100, 96 });
		SblockP1.PushBack({ 630, 2169, 100, 96 });
		
		//Crouch Block Animation
		CblockP1.PushBack({ 730, 2100, 100, 63 });
		CblockP1.PushBack({ 630, 2100, 100, 63 });

	    //Standing Damage 
		SdamageP1.PushBack({ 730, 2169, 100, 96 });
		SdamageP1.PushBack({ 630, 2169, 100, 96 });
		SdamageP1.loop = false;
		SdamageP1.speed = 0.05;

		//Standing Damage Low Attack
		SdamagelowP1.PushBack({});

		//Crouch Damage
		CdamageP1.PushBack({});

		//Electric Thunder Damage
		ETdamgeP1.PushBack({});

		//Recovery
		RecoveryP1.PushBack({});

	}

	{ //ATTACKS ANIMATIONS
		
	  //Standing FAR LP
	  SFLP_P1.PushBack({28, 658, 104, 105});
	  SFLP_P1.PushBack({132, 658, 143, 105});
	  SFLP_P1.PushBack({275, 658, 123, 105});
	  SFLP_P1.speed = 0.2f;	
	  SFLP_P1.loop = false;

	  //Standing CLOSE LP
	  SCLP_P1.PushBack({});

	  //Crouch LP
	  CLP_P1.PushBack({610, 709, 109, 56 });
	  CLP_P1.PushBack({727, 715, 154, 50 });
	  CLP_P1.PushBack({890, 713, 142, 52 });
	  CLP_P1.speed = 0.2f;
	  CLP_P1.loop = false;

	  //Jumping LP
	  JLP_P1.PushBack({});
	   
	  //Standing FAR MP
	  SFMP_P1.PushBack({31, 765, 88, 104 }); 
	  SFMP_P1.PushBack({134, 788, 120, 108 });
	  SFMP_P1.PushBack({264, 799, 130, 97 });
	  SFMP_P1.PushBack({403, 803, 103, 93});
	  SFMP_P1.speed = 0.2f;
	 
	  //Standing CLOSE MP
	  SCMP_P1.PushBack({ 610, 792, 82, 64 });
	  SCMP_P1.PushBack({ 703, 794, 140, 62 });
	  SCMP_P1.PushBack({ 851, 790, 147, 66 });
	  SCMP_P1.PushBack({ 1005, 786, 140, 70 });
	  SCMP_P1.PushBack({ 851, 790, 147, 66 });
	  SCMP_P1.PushBack({ 703, 794, 140, 62 });
	  SCMP_P1.PushBack({ 610, 792, 82, 64 });
	  SCMP_P1.speed = 0.2f;

	  //Crouch MP

	  //Jump MP

	  //Standing FAR HP
	  SFHP_P1.PushBack({ 27, 929, 107, 95 });
	  SFHP_P1.PushBack({ 140, 926, 128, 98 });
	  SFHP_P1.PushBack({ 140, 926, 128, 98 });
	  SFHP_P1.PushBack({ 275, 906, 99, 118 });
	  SFHP_P1.PushBack({ 275, 906, 99, 118 });
	  SFHP_P1.PushBack({ 275, 906, 99, 118 });
	  SFHP_P1.PushBack({ 275, 906, 99, 118 });
	  SFHP_P1.PushBack({ 275, 906, 99, 118 });
	  SFHP_P1.PushBack({ 140, 926, 128, 98 });
	  SFHP_P1.PushBack({ 140, 926, 128, 98 });
	  SFHP_P1.PushBack({ 140, 926, 128, 98 });
	  SFHP_P1.PushBack({ 140, 926, 128, 98 });
	  SFHP_P1.PushBack({ 140, 926, 128, 98 });
	  SFHP_P1.PushBack({ 140, 926, 128, 98 });
	  SFHP_P1.PushBack({ 140, 926, 128, 98 });
	  SFHP_P1.PushBack({ 27, 929, 107, 95 });
	  SFHP_P1.PushBack({ 27, 929, 107, 95 });
	  SFHP_P1.PushBack({ 27, 929, 107, 95 });
	  SFHP_P1.PushBack({ 27, 929, 107, 95 });
	  SFHP_P1.speed = 0.2f;

	  //Standing CLOSE HP

	  //Crouch HP
	  CHP_P1.PushBack({ 612, 895, 84, 58 });
	  CHP_P1.PushBack({ 710, 898, 96, 55 });
	  CHP_P1.PushBack({ 710, 898, 96, 55 });
	  CHP_P1.PushBack({ 815, 869, 166, 84 });
	  CHP_P1.PushBack({ 815, 869, 166, 84 });
	  CHP_P1.PushBack({ 710, 898, 96, 55 });
	  CHP_P1.PushBack({ 710, 898, 96, 55 });
	  CHP_P1.PushBack({ 710, 898, 96, 55 });
	  CHP_P1.PushBack({ 710, 898, 96, 55 });
	  CHP_P1.PushBack({ 710, 898, 96, 55 });
	  CHP_P1.PushBack({ 612, 895, 84, 58 });
	  CHP_P1.PushBack({ 612, 895, 84, 58 });
	  CHP_P1.PushBack({ 612, 895, 84, 58 });
	  CHP_P1.speed = 0.2f;

	  //Jump HP

	  //Standing FAR LK
	  SFLK_P1.PushBack({ 33, 1028, 81, 96 });
	  SFLK_P1.PushBack({ 124, 1031, 97, 94 });
	  SFLK_P1.PushBack({ 230, 1032, 137, 93 });
	  SFLK_P1.PushBack({ 230, 1032, 137, 93 });
	  SFLK_P1.PushBack({ 124, 1031, 97, 94 });
	  SFLK_P1.PushBack({ 33, 1028, 81, 96 });
	  SFLK_P1.speed = 0.2f;

	  //Standing CLOSE LK

	  //Crouch LK
	  CLK_P1.PushBack({ 610, 980, 74, 78 }); 
	  CLK_P1.PushBack({ 702, 978, 74, 78 });
	  CLK_P1.PushBack({ 790, 972, 139, 68 });
	  CLK_P1.PushBack({ 702, 978, 74, 78 });
	  CLK_P1.PushBack({ 610, 980, 74, 78 });
	  CLK_P1.speed = 0.2f;

	  //Jump LK

	  //Standing FAR MK
	  SFMK_P1.PushBack({28, 1135, 92, 85 });
	  SFMK_P1.PushBack({ 129, 1135, 101, 85 });
	  SFMK_P1.PushBack({ 236, 1135, 124, 85 }); 
	  SFMK_P1.PushBack({ 236, 1135, 124, 85 });
	  SFMK_P1.PushBack({ 129, 1135, 101, 85 });
	  SFMK_P1.PushBack({ 28, 1135, 92, 85 });
	  SFMK_P1.speed = 0.2f;

	  //Standing CLOSE MK

	  //Crouch MK
	  CMK_P1.PushBack({ 610, 980, 74, 78 });
	  CMK_P1.PushBack({ 702, 978, 74, 78 });
	  CMK_P1.PushBack({ 790, 972, 139, 68 });
	  CMK_P1.PushBack({ 790, 972, 139, 68 });
	  CMK_P1.PushBack({ 702, 978, 74, 78 });
	  CMK_P1.PushBack({ 610, 980, 74, 78 });

	  //Jump MK

	  //Standing FAR HK
	  SFHK_P1.PushBack({ 34, 1263, 90, 85 });
	  SFHK_P1.PushBack({ 143, 1263, 163, 85 });
	  SFHK_P1.PushBack({ 316, 1249, 122, 99 });
	  SFHK_P1.PushBack({ 445, 1221, 88, 127 });
	  SFHK_P1.PushBack({ 536, 1250, 138, 98 });
	  SFHK_P1.PushBack({ 686, 1279, 103, 69 });
	  SFHK_P1.speed = 0.2f;

	  //Standing CLOSE HK

	  //Crouch HK
	  CHK_P1.PushBack({610, 1078, 72, 80 });
	  CHK_P1.PushBack({698, 1083, 91, 76 });
	  CHK_P1.PushBack({ 799, 1090, 161, 69 });
	  CHK_P1.PushBack({ 799, 1090, 161, 69 });
	  CHK_P1.PushBack({ 698, 1083, 91, 76 });
	  CHK_P1.PushBack({ 698, 1083, 91, 76 });
	  CHK_P1.PushBack({ 698, 1083, 91, 76 });
	  CHK_P1.PushBack({ 698, 1083, 91, 76 });
	  CHK_P1.PushBack({ 610, 1078, 72, 80 });
	  CHK_P1.PushBack({ 610, 1078, 72, 80 });
	  CHK_P1.PushBack({ 610, 1078, 72, 80 });
	  CHK_P1.PushBack({ 610, 1078, 72, 80 });
	  CHK_P1.speed = 0.2f;

	  //Jump HK


	  //Headbut
	  Headbut_P1.PushBack({});

	  //Throw
	  Throw_P1.PushBack({ 27, 2141, 89, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 214, 2141, 76, 104 });
	  Throw_P1.PushBack({ 214, 2141, 76, 104 });
	  Throw_P1.PushBack({ 301, 2141, 93, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 301, 2141, 93, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 301, 2141, 93, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 301, 2141, 93, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 301, 2141, 93, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 301, 2141, 93, 104 });
	  Throw_P1.PushBack({ 123, 2141, 82, 104 });
	  Throw_P1.PushBack({ 27, 2141, 89, 104 });
	  Throw_P1.speed = 0.1f;
	
	  //Electric Thunder 
	  Ethunder_P1.PushBack({ 27, 1871, 93, 75 });
	  Ethunder_P1.PushBack({ 130, 1874, 86, 72 });
	  Ethunder_P1.PushBack({ 27, 1871, 93, 75 });
	  Ethunder_P1.PushBack({ 130, 1874, 86, 72 });
	  Ethunder_P1.PushBack({ 27, 1871, 93, 75 });
	  Ethunder_P1.PushBack({ 130, 1874, 86, 72 });
	  Ethunder_P1.PushBack({ 228, 1866, 136, 79 });
	  Ethunder_P1.PushBack({ 375, 1883, 85, 63 });
	  Ethunder_P1.PushBack({ 228, 1866, 136, 79 });
	  Ethunder_P1.PushBack({ 228, 1866, 136, 79 });
	  Ethunder_P1.PushBack({ 228, 1866, 136, 79 });
	  Ethunder_P1.PushBack({ 228, 1866, 136, 79 });
	  Ethunder_P1.PushBack({ 375, 1883, 85, 63 });
	  Ethunder_P1.PushBack({ 375, 1883, 85, 63 });
	  Ethunder_P1.PushBack({ 228, 1866, 136, 79 });
	  Ethunder_P1.PushBack({ 228, 1866, 136, 79 });
	  Ethunder_P1.PushBack({ 228, 1866, 136, 79 });
	  Ethunder_P1.PushBack({ 375, 1883, 85, 63 });
	  Ethunder_P1.PushBack({ 375, 1883, 85, 63 });
	  Ethunder_P1.PushBack({ 27, 1871, 93, 75 });
	  Ethunder_P1.PushBack({ 130, 1874, 86, 72 });
	  Ethunder_P1.PushBack({ 27, 1871, 93, 75 });
	  Ethunder_P1.speed = 0.3f;



	  //Rolling Attack
	  RollingP1.PushBack({});

	}
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	graphicsP1 = App->textures->Load("Sprites/BlankaP1.png"); // JA TE LA FOTO BONA
	currentstateP1 = idlestateP1;
	combo[0] = ' ';
	*startC = combo[0];
	*finishC = combo[0];

	//Player 2 stest collider
	playerP1_collider = App->collision->AddCollider({ positionP1.x , positionP1.y - 100, 60, 93 }, COLLIDER_PLAYER, App->player);
	attackP1_collider = nullptr;
	return true;
}


bool ModulePlayer::CleanUp()
{
	LOG("Unloading Player");

	App->textures->Unload(graphicsP1);
	return true;
}

update_status ModulePlayer::PreUpdate() {
	time = SDL_GetTicks() / 20;
	//MOVE BACKWARD
	//inputplayerP1.A_active = App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT;
	//MOVE FORWARD
	//inputplayerP1.D_active = App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT;
	//CROUCH
	//inputplayerP1.S_active = App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT;
	//JUMP
//	inputplayerP1.W_active = App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTX) <= -10000;
	/* inputplayerP1.right_active = SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTX) >= 10000;
	 inputplayerP1.down_active = SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) >= 10000;
	 inputplayerP1.up_active = SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) <= -10000;
	 inputplayerP1.down_active = SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) <= -10000;*/
	 App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_1] == KEY_DOWN;
	 App->input->game_pad[SDL_CONTROLLER_BUTTON_B][GAME_PAD_1] == KEY_DOWN;
     App->input->game_pad[SDL_CONTROLLER_BUTTON_X][GAME_PAD_1] == KEY_DOWN;
	 inputplayerP1.D_active = App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)|| SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTX) >= 10000;
	 inputplayerP1.A_active = App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_LEFT)|| SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTX) <= -10000;
	 inputplayerP1.S_active = App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_DOWN) || SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) >= 10000;
	 inputplayerP1.W_active = App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT || SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_DPAD_UP) || SDL_GameControllerGetAxis(App->input->controller_player_1, SDL_CONTROLLER_AXIS_LEFTY) <= -10000;
	 inputplayerP1.U_active = App->input->keyboard[SDL_SCANCODE_U] == KEY_DOWN || SDL_GameControllerGetButton(App->input->controller_player_1, SDL_CONTROLLER_BUTTON_X);
	 inputplayerP1.X_active = App->input->keyboard[SDL_SCANCODE_X] == KEY_DOWN;
	 inputplayerP1.C_active = App->input->keyboard[SDL_SCANCODE_C] == KEY_DOWN;
	 inputplayerP1.V_active = App->input->keyboard[SDL_SCANCODE_V] == KEY_DOWN;
	 inputplayerP1.N_active = App->input->keyboard[SDL_SCANCODE_N] == KEY_DOWN;

	 {
		 bool thundertick = 0;
		 //BASIC MOVEMENTS

		 //IDLE STATE
		 if (currentstateP1 == idlestateP1) {
			 comboInput(' ');

			 if (inputplayerP1.A_active) {
				 currentstateP1 = backwardstateP1;
				
				 LOG("IDLE TO BACK");
			 }
			 if (inputplayerP1.D_active) {
				 currentstateP1 = forwardstateP1;
				 LOG("IDLE TO forward");
			 }
			 if (inputplayerP1.S_active) {
				 currentstateP1 = crouchstateP1;
				 LOG("IDLE to CROUCH");
			 }
			 if (inputplayerP1.W_active) {
				
				 jumping = true;
				 currentstateP1 = NjumpstateP1;
				 jumpstart = time;
				 jumpTimer = 0;
				 LOG("IDLE to JUMP");
			 }
			 if (inputplayerP1.U_active) {
				 currentstateP1 = standingfarLPP1;
				 attackP1_collider = App->collision->AddCollider({ positionP1.x - App->render->camera.x + 55, positionP1.y - 80 - App->render->camera.y * 2, 50, 15 }, COLLIDER_PLAYER_ATTACK, App->player);
				 LOG("IDLE to LP");
			 }
			 if (inputplayerP1.C_active) {

				 currentstateP1 = HPP1;
				 LOG("IDLE to HEAVY PUNCH");

			 }
		 }
		 //BACKWARDS STATE
		 if (currentstateP1 == backwardstateP1) {
			 comboInput('n');
			 comboInput('m');
			 if (!inputplayerP1.A_active) {
				 currentstateP1 = idlestateP1;
				
				 LOG("BACK to IDLE");
			 }
			 if (inputplayerP1.S_active) {
				 
				 currentstateP1 = crouchstateP1;
				
				 LOG("BACK to CROUCH");
			 }
			 if (inputplayerP1.W_active) {
				 
				 jumping = true;
				 currentstateP1 = BjumpstateP1;
				 jumpstart = time;
				 jumpTimer = 0;
				 LOG("IDLE to CROUCH");
			 }
			 if (inputplayerP1.U_active) {
				
				 currentstateP1 = standingfarLPP1;
				 attackP1_collider= App->collision->AddCollider({ positionP1.x - App->render->camera.x + 55, positionP1.y - 80 - App->render->camera.y * 2, 50, 15 }, COLLIDER_PLAYER_ATTACK, App->player);
				 LOG("BACK to LP");
			 }

			 if (inputplayerP1.C_active) {

				 currentstateP1 = throwP1; // AQUI FALTA LA CONDICIO D'ESTAR APROP AMB ELS COLIDER
			 }

			 if (inputplayerP1.N_active) {

				 currentstateP1 = throwP1; //AQUI FALTA CONDICIO D'ESTAR APROP AMB ELS COLIDERS
			 }

		 }
		 //FORWARD STATE
		 if (currentstateP1 == forwardstateP1) {
			 comboInput('d');
			 if (!inputplayerP1.D_active) {
				 //blockP1_collider->to_delete = true;
				 currentstateP1 = idlestateP1;
				
				 LOG("FOR to IDLE");
			 }
			 if (inputplayerP1.A_active) {
				 currentstateP1 = backwardstateP1;

				 LOG("FOR to BACK");
			 }
			 if (inputplayerP1.S_active) {
				
				 currentstateP1 = crouchstateP1;
				 LOG("FOR to CROUCH");
			 }
			 if (inputplayerP1.W_active){
				
				 jumping = true;
				 currentstateP1 = FjumpstateP1;
				 jumpstart = time;
				 jumpTimer = 0;
				 LOG("FOR to CROUCH");
			 }
			 if (inputplayerP1.U_active) {
				
				 currentstateP1 = standingfarLPP1;
				 attackP1_collider = App->collision->AddCollider({ positionP1.x - App->render->camera.x + 55, positionP1.y - 80 - App->render->camera.y * 2, 50, 15 }, COLLIDER_PLAYER_ATTACK, App->player);
				 LOG("FOR to LP");
			 }

			 if (inputplayerP1.C_active) {

				 currentstateP1 = throwP1; // AQUI FALTA LA CONDICIO D'ESTAR APROP AMB ELS COLIDER
			 }

			 if (inputplayerP1.N_active) {

				 currentstateP1 = throwP1; //AQUI FALTA CONDICIO D'ESTAR APROP AMB ELS COLIDERS
			 }
		 }
		 //CROUCH STATE
		 if (currentstateP1 == crouchstateP1) {
			 comboInput('s');
			 if (!inputplayerP1.S_active) {
				 crouchP1.Reset();
				 currentstateP1 = idlestateP1;
				 
				 LOG("CROUCH to IDLE");
			 }
			 if (inputplayerP1.U_active) {
				 currentstateP1 = crouchLPP1;
				 LOG("CROUCH to LP");
				 
			 }
			 if (inputplayerP1.A_active) {
				 crouchBlockingP1 = true;
			 }
			 if (!inputplayerP1.A_active ) {
				 crouchBlockingP1 = false;
			 }
		 }
		 //JUMP STATE
		 if (jumping == true) {
			 comboInput('w');
			 if (positionP1.y >= groundLevel + 5) {
				 positionP1.y = groundLevel;
				 currentstateP1 = idlestateP1;
				 NjumpP1.Reset();
				 FjumpP1.Reset();
				 BjumpP1.Reset();
				 jumping = false;
				 jumpTimer = 0;

			 }
		 }
		 //ATTACKS
		 //STANDING FAR LP
		 if (currentstateP1 == standingfarLPP1) {

			
			
			 if (currentP1_animation->Finished()&& !inputplayerP1.U_active) {
				
				 currentstateP1 = idlestateP1;
				 alreadyHit = false;
				 SFLP_P1.Reset();
				 
				 LOG("LP to IDLE");

				
			 }

			  if ( currentP1_animation->Finished()&&inputplayerP1.U_active) {


				 currentstateP1 = thunder1P1;
				 alreadyHit = false;
				 Ethunder_P1.Reset();
				 SFLP_P1.Reset();
				 thundertick = 1;
				 LOG("LP to Thunder1");
				 
				 
			 }
			if (currentP1_animation->Finished()&&inputplayerP1.U_active&&thundertick==1){

				 currentstateP1 =thunder2P1;
				 alreadyHit = false;
				 SFLP_P1.Reset();
				 Ethunder_P1.Reset();
				 LOG("Thunder1 to Thunder2");


			 }
		 }

		 if (currentstateP1 == thunder1P1) {

			 if (currentP1_animation->Finished()&&!inputplayerP1.U_active) {  ////////////////// AQUI ESTA EL PROBLEMA
				 alreadyHit = false;

				 currentstateP1 = idlestateP1;
				 SFLP_P1.Reset();
				 Ethunder_P1.Reset();
				 LOG("Thunder 1 to IDLE");
			 }

			/* if (currentP1_animation->Finished() && inputplayerP1.U_active) {

				 currentstateP1 = idlestateP1;

			  }*/

			 //else if (currentP1_animation->Finished() ) {
			 //    alreadyHit = false;
				// Ethunder_P1.Reset();
				// SFLP_P1.Reset();
				//// currentstateP1 = thunder2P1;
				// LOG("Thunder 1 to Thunder 2");

			 //}

		 }

		 if (currentstateP1 == thunder2P1) {
		 

			 if (currentP1_animation->Finished()&& !inputplayerP1.U_active) {
				 currentstateP1 = idlestateP1;
				 Ethunder_P1.Reset();
				 SFLP_P1.Reset();
				 LOG("GOING BACK TO IDLE ");
			 }
		 }

		 if (currentstateP1 == HPP1) {

			 if (currentP1_animation->Finished() && !inputplayerP1.C_active){

				 currentstateP1 = idlestateP1;

			 }
			
	
		 }

		 if (currentstateP1 == throwP1) {

			 if (currentP1_animation->Finished())
			 {
				 Throw_P1.Reset();
				 
				 currentstateP1 = idlestateP1;

			 }

		 }

		 //CROUCH LP
		 if (currentstateP1 == crouchLPP1) {
			 if (currentP1_animation->Finished() && !inputplayerP1.U_active && inputplayerP1.S_active) {
				 currentstateP1 = crouchstateP1;
				 alreadyHit = false;
				 CLP_P1.Reset();
				 LOG("LP to CROUCH");
			 }
			 if (currentP1_animation->Finished() && !inputplayerP1.U_active && !inputplayerP1.S_active) {
				 currentstateP1 =idlestateP1;
				 alreadyHit = false;
				 CLP_P1.Reset();
				 LOG("LP CROUCHED to IDLE");
			 }
		 }
		 if (currentstateP1 == SdamagedP1) {
			 if (currentP1_animation->Finished()) {
				 currentstateP1 = idlestateP1;
				 SdamageP1.Reset();
			 }
		 }
		return UPDATE_CONTINUE;
	}
}

update_status ModulePlayer::Update() {

	switch (currentstateP1)
	{

	case idlestateP1:
		playerP1_collider->rect.h = 93;
		currentP1_animation = &idleP1;
		//LOG("IDLE ANIMATION ACTIVE");
		break;

	case backwardstateP1:
		playerP1_collider->rect.h = 93;

		currentP1_animation = &backwardP1;
		positionP1.x -= speed;
		LOG("BACK ANIMATION ACTIVE");
		break;

	case forwardstateP1:

		currentP1_animation = &forwardP1;

		positionP1.x += speed;
		LOG("FORWARD ANIMATION ACTIVE");
		break;

	case crouchstateP1:
		currentP1_animation = &crouchP1;
		playerP1_collider->rect.h = 65;
		playerP1_collider->SetPos(positionP1.x - App->render->camera.x * 2, positionP1.y - 68 - App->render->camera.y * 2);

		LOG("CROUCHED ANIMATION ACTIVE");
		break;

	case NjumpstateP1:
		currentP1_animation = &NjumpP1;
		positionP1.y = groundLevel - (yvel*jumpTimer) + (0.5*(gravity) * (jumpTimer*jumpTimer)); //MRUA
		LOG(" NEUTRAL JUMP ANIMATION ACTIVE");
		break;

	case FjumpstateP1:
		if (!flipP1) { currentP1_animation = &FjumpP1; }
		else { currentP1_animation = &BjumpP1; }
		positionP1.x += speed;
		positionP1.y = groundLevel - (yvel*jumpTimer) + (0.5*(gravity) * (jumpTimer*jumpTimer)); //MRUA
		LOG(" FORWARD JUMP ANIMATION ACTIVE");
		break;

	case BjumpstateP1:
		if (!flipP1) { currentP1_animation = &BjumpP1; }
		else { currentP1_animation = &FjumpP1; }
		positionP1.x -= speed;
		positionP1.y = groundLevel - (yvel*jumpTimer) + (0.5*(gravity) * (jumpTimer*jumpTimer)); //MRUA
		LOG(" BACKWARD JUMP ANIMATION ACTIVE");
		break;

	case standingfarLPP1:
		currentP1_animation = &SFLP_P1;         //&SFLP_P1
		LOG("LP ANIMATION ACTIVE");
		break;

	case thunder1P1:
		currentP1_animation = &SFLP_P1;
		LOG("THUNDER 1 ANIMATION ACTIVE");
		
		break;

	case thunder2P1:
		currentP1_animation = &Ethunder_P1;
		LOG("THUNDER 2 ANIMATION ACTIVE");
		break;

	case throwP1:
		currentP1_animation = &Throw_P1;
		
		LOG("THROW ANIMATION ACTIVE");
		break;

	case crouchLPP1:
		currentP1_animation = &CLP_P1;
		LOG("CROUCH LP ANIMATION ACTIVE");
		break;
	
	case SdamagedP1:
		currentP1_animation = &SdamageP1;
	}

	if ( currentstateP1 != crouchstateP1) {
		playerP1_collider->SetPos(positionP1.x  - App->render->camera.x *2  , positionP1.y - 93 - App->render->camera.y * 2);
	}

	SDL_Rect r = currentP1_animation->GetCurrentFrame();
	//SHADOW
	shadowP1 = {796,27,100,20};
	
	//Jumping boolean

	if (jumping) {
		jumpTimer = time - jumpstart;
		playerP1_collider->SetPos(positionP1.x - App->render->camera.x * 2, positionP1.y - 80 - App->render->camera.y * 2);
	}
	//Flip of the players when they change sides
	if (playerP1_collider->rect.x < App->player2->playerP2_collider->rect.x ) {
		flipP1 = false;

		App->render->Blit(graphicsP1, positionP1.x - 10, groundLevel-15, &shadowP1, 1.0f, true,SDL_FLIP_NONE);
		App->render->Blit(graphicsP1, positionP1.x, positionP1.y - r.h, &r, 1.0f, true, SDL_FLIP_NONE);
	}
	else {
		flipP1 = true;
		if (blockP1_collider == nullptr) {
			blockP1_collider = App->collision->AddCollider({ positionP1.x - App->render->camera.x , positionP1.y - 80 - App->render->camera.y * 2, 7, 30 }, COLLIDER_PLAYER_BLOCK, App->player);
		}
		App->render->Blit(graphicsP1, positionP1.x +7, groundLevel -15, &shadowP1, 1.0f, true, SDL_FLIP_HORIZONTAL);
		App->render->Blit(graphicsP1, positionP1.x, positionP1.y - r.h, &r, 1.0f, true, SDL_FLIP_HORIZONTAL);
	}

	if (positionP1.x <= (App->render->camera.x ))
	{
		positionP1.x = (App->render->camera.x );
	}
	if (positionP1.x >= (App->render->camera.x) + SCREEN_WIDTH -100)
	{
		positionP1.x = (App->render->camera.x) +SCREEN_WIDTH -100;
	}






	return UPDATE_CONTINUE;
}

//TODO 7.4: Detect collision with a wall. If so, go back to intro screen.
void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_PLAYER2_ATTACK) {
		if (!SblockingP1) {
			currentstateP1 = SdamagedP1;
		}
		else {
			//currentstateP1 = ;
		}

	}

}

bool ModulePlayer::comboActive() {

	//Input button combination for special attack	
	int i = 0;
	int j = startcombo;
	int done = 0; //If done = 3. Special attack = true 

	while (i < 100) {
		switch (done) {
		case 0:
			if (combo[j] == 'c')//punch
				done++;
			break;
		case 1:
			if (combo[j] == 'd')//forward
				done++;
			break;
		case 2:
			if (combo[j] == 'n' && 'm') // enredere
				done++;
			break;
		case 3:
			if (combo[j] == 's') //down
				return true;
		default:
			//Special attack is false
			return false;
		}

		if (j > 0)
			j--;
		else
			j = 99;
		i++;
	}

	return false;
}


void ModulePlayer::comboInput(char comboInput) {
	combo[*finishC] = comboInput; //We add the newInput to the last inputs array

	if (*finishC < 99) //We change last pointer's position 
		(*finishC)++;
	else
		*finishC = 0;

	//We change first pointer's position 
	if (*startC == *startC && *startC < 99)
		(*startC)++;
	else if (*startC == *finishC && *startC >= 99)
		* startC = 0;
}